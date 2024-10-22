#include "Client.hpp"
#include "Utils.hpp"
#include "Console.hpp"
#include <sys/time.h>
#include <random>

#include "Network/Socket.hpp"

//#include "Threads/SocketThread.hpp"
//#include "Threads/GoapThread.hpp"

#include "Pathfinding.hpp"
#include "WorldState.hpp"

#define STATE_IS_SEEING_FOOD		"is_seeing_food"
#define STATE_IS_SEEING_ORE			"is_seeing_ore"

#define STATE_IS_WALKING_ON_FOOD 	"is_walking_on_food"
#define STATE_IS_WALKING_ON_ORE		"is_walking_on_ore"

#define STATE_HAS_ENOUGH_FOOD		"has_enough_food"
#define STATE_HAS_ENOUGH_ORE		"has_enough_ore"

#define STATE_HAS_ENOUGH_PLAYER		"has_enough_player"
#define STATE_WAITING_FOR_PLAYER	"waiting_for_player"
#define STATE_ARE_PLAYER_READY		"are_player_ready"

#define STATE_CAN_JOIN_PLAYER		"can_join_player"
#define STATE_WAIT_FOR_RESPONSE		"wait_for_response"
#define STATE_JOINING_PLAYER		"joining_player"

#define STATE_IS_FORKING				"is_forking"


#define STATE_START_RITUAL			"incantation_en_cours"

#define STATE_IDLE 					"ne_fait_rien"

#define STATE_IS_TEAM_FULL			"is_team_full"


#define MINIMUM_FOOD		30 * 126

Client::Client()
{
	m_id = std::to_string(getpid());

	std::memset((void *)&m_GlobalContext, 0, sizeof(m_GlobalContext));
	m_GlobalContext.commandsRemaining = 10;
	m_GlobalContext.width = -1;
	m_GlobalContext.height = -1;

	m_WorldState = new WorldState();
}

Client::~Client()
{
	delete m_GlobalContext.m_Server;
}

void Client::Initialize(int argc, char **argv)
{
	if (argc < 5)
		throw std::runtime_error("Usage: ./client -n <team> -p <port> [-h <hostname>]\n\t-n team_name\n\t-p port\n\t-h name of the host, by default it'll be localhost\n");


	m_GlobalContext.m_Hostname = "127.0.0.1";

	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-p")
			m_GlobalContext.m_Port = std::atoi(argv[i + 1]);
		else if (std::string(argv[i]) == "-n")
			m_GlobalContext.m_Team = argv[i + 1];
		else if (std::string(argv[i]) == "-h")
			m_GlobalContext.m_Hostname = argv[i + 1];
	}

	m_GlobalContext.appRunning = true;

	m_GoapStates = {
		{ STATE_IS_SEEING_FOOD, false },
		{ STATE_IS_SEEING_ORE, false },
		{ STATE_IS_WALKING_ON_FOOD, false },
		{ STATE_IS_WALKING_ON_ORE, false },
		{ STATE_HAS_ENOUGH_FOOD, false },
		{ STATE_HAS_ENOUGH_ORE, false },
		{ STATE_HAS_ENOUGH_PLAYER, false },
		{ STATE_WAITING_FOR_PLAYER, false },
		{ STATE_JOINING_PLAYER, false },
		{ STATE_CAN_JOIN_PLAYER, false },
		{ STATE_START_RITUAL, false },
		{ STATE_IDLE, false },
		{ STATE_ARE_PLAYER_READY, false },
		{ STATE_WAIT_FOR_RESPONSE, false },
		{ STATE_IS_TEAM_FULL, false },
		{ STATE_IS_FORKING, false }
	};
}

void Client::Start()
{
	m_GlobalContext.m_Server = new Socket(m_GlobalContext.m_Port, m_GlobalContext.m_Hostname);
	m_GlobalContext.m_Server->SetOption(SOCKET_REUSE_ADRESS, 1);

	if (!m_GlobalContext.m_Server->Connect())
		throw std::runtime_error("Failed to connect to server.");

	std::cout << "Connected to server." << std::endl;

	char buffer[1024];

	int width = -1;
	int height = -1;
	int teamSpotAvailable = -1;

	while (teamSpotAvailable == -1 || width == -1 || height == -1)
	{
		bzero(buffer, 1024);

		if (m_GlobalContext.m_Server->Receive(buffer, 1024) < 0) {
			std:: cout << "Erreur lors de la réception" << std::endl;
			exit(EXIT_FAILURE);
		}

		if (strlen(buffer) == 0)
			continue;

		std::cout << buffer;

		if (std::strncmp(buffer, "BIENVENUE", 9) == 0)
		{
			SendCommand(m_GlobalContext.m_Team);
		}
		else if (teamSpotAvailable == -1)
		{
			teamSpotAvailable = atoi(buffer);
		}
		else if (width == -1 && height == -1)
		{
			std::vector<std::string> mapSize = Utils::str_split(buffer, " ");
			width = atoi(mapSize[0].c_str());
			height = atoi(mapSize[1].c_str());
		}
	}

	if (teamSpotAvailable == -1 || width == -1 || height == -1)
		throw std::runtime_error("Failed to get map size or team spot available.");

	if (teamSpotAvailable == 0)
		throw std::runtime_error("Team is full.");

	m_GlobalContext.width = width;
	m_GlobalContext.height = height;

	std::cout << "Map size: " << width << "x" << height << std::endl;
	std::cout << "Team spot available: " << teamSpotAvailable << std::endl;

	// then start the main loop with the GOAP
	while (m_GlobalContext.appRunning)
	{
		m_GoapStates[STATE_CAN_JOIN_PLAYER] = false;
		ParseMessage();

		// update the world state
		if (!m_GoapStates[STATE_WAIT_FOR_RESPONSE] && !m_GoapStates[STATE_START_RITUAL] && !m_GoapStates[STATE_JOINING_PLAYER])
		{
			m_WorldState->ParseMap(GetMap());
			m_WorldState->ParseInventory(GetInventory());
		}

		// initialize the world state
		m_GoapStates[STATE_IS_SEEING_ORE] = m_WorldState->IsOreInSight();
		m_GoapStates[STATE_IS_WALKING_ON_ORE] =	m_WorldState->IsWalkingOnOre();
		m_GoapStates[STATE_IS_SEEING_FOOD] = m_WorldState->IsFoodInSight();
		m_GoapStates[STATE_IS_WALKING_ON_FOOD] = m_WorldState->IsWalkingOnFood();
		m_GoapStates[STATE_HAS_ENOUGH_FOOD] = m_WorldState->HasEnoughFood();
		m_GoapStates[STATE_HAS_ENOUGH_ORE] = m_WorldState->HasEnoughOre();
		m_GoapStates[STATE_ARE_PLAYER_READY] = m_WorldState->ArePlayersReady();
		m_GoapStates[STATE_IS_TEAM_FULL] = IsTeamFull();

		int nourriture = m_WorldState->GetInventory()["nourriture"];

		if (m_GoapStates[STATE_WAIT_FOR_RESPONSE])
			ReceiveCommand(false);

		if (m_GoapStates[STATE_IS_TEAM_FULL])
			m_GoapStates[STATE_IS_FORKING] = false;
		else
		{
			if (!m_GoapStates[STATE_IS_FORKING])
			{
				SendCommand("fork");
				if (ReceiveCommand().find("ok") != std::string::npos)
					m_GoapStates[STATE_IS_FORKING] = true;
			}
			else
			{
				std::stringstream ss;
				ss << "./client -p ";
				ss << m_GlobalContext.m_Port;
				ss << " -n ";
				ss << m_GlobalContext.m_Team;
				ss << " -h ";
				ss << m_GlobalContext.m_Hostname;
				ss << " &";

				char* sss = strdup(ss.str().c_str());
				system(sss);
				free(sss);
			}
		}

		if (m_GoapStates[STATE_JOINING_PLAYER])
		{
			if (m_WorldState->GetIncantationDirection() == -1)
			{
				ReceiveCommand(false);
				continue;
			}
			if (m_WorldState->GetIncantationDirection() == 0)
			{
				SendCommand("broadcast ready:" + m_id);
				ReceiveCommand();
				m_GoapStates[STATE_WAIT_FOR_RESPONSE] = true;
				m_GoapStates[STATE_START_RITUAL] = true;
				m_GoapStates[STATE_JOINING_PLAYER] = false;
			}
			else if (m_WorldState->GetIncantationDirection() == 1 || m_WorldState->GetIncantationDirection() == 2 ||m_WorldState->GetIncantationDirection() == 8)
			{
				SendCommand("avance");
				ReceiveCommand();
			}
			else if (m_WorldState->GetIncantationDirection() == 5 || m_WorldState->GetIncantationDirection() == 6 ||m_WorldState->GetIncantationDirection() == 7)
			{
				SendCommand("droite");
				ReceiveCommand();
			}
			else {
				SendCommand("gauche");
				ReceiveCommand();
			}
			m_WorldState->SetIncantationDirection(-1);
		}
		else if (m_GoapStates[STATE_START_RITUAL])
		{
			if (group.size() > 0)
			{
				for (std::string id : group)
				{
					id.erase(std::remove(id.begin(), id.end(), '\n'), id.end());
					if (m_WorldState->SlotAvailable())
					{
						SendCommand("broadcast accept:" + id + ";" + m_id);
						m_WorldState->IncNbPlayer();
					}
					else
						SendCommand("broadcast deny:" + id + ";" + m_id);
					ReceiveCommand();
				}
				group.clear();
			}
			if (m_GoapStates[STATE_WAIT_FOR_RESPONSE])
			{
				if (m_WorldState->GetResult() == -1)
				{
					ReceiveCommand(false);
					continue;
				}
				else if (m_WorldState->GetResult() == 1)
					m_WorldState->IncLevel();
				ResetStates();
				m_WorldState->SetIdMaster("");
			}
			else if (m_GoapStates[STATE_ARE_PLAYER_READY])
			{
				StartRitual();
				ResetStates();
			}
			else
			{
				if (nourriture < MINIMUM_FOOD / 2)
				{
					m_WorldState->ResetNbPlayerReady();
					LookForFood();
				}
				if (m_GoapStates[STATE_WAITING_FOR_PLAYER])
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(400));
					SendCommand("broadcast here:" + m_id);
					ReceiveCommand();
				}
				else if (!m_WorldState->SlotAvailable())
					m_GoapStates[STATE_WAITING_FOR_PLAYER] = true;
				else
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(300));
					SendCommand("broadcast incantation:" + std::to_string(m_WorldState->GetLevel()) + ";" + m_id);
					ReceiveCommand();
				}
			}
		}
		else if (m_GoapStates[STATE_HAS_ENOUGH_FOOD] && !m_GoapStates[STATE_WAIT_FOR_RESPONSE])
		{
			if (m_GoapStates[STATE_CAN_JOIN_PLAYER])
			{
				SendCommand("broadcast join:" + m_WorldState->GetIdMaster() + ";" + m_id);
				ReceiveCommand();
				m_GoapStates[STATE_WAIT_FOR_RESPONSE] = true;
			}
			else if (!m_GoapStates[STATE_HAS_ENOUGH_ORE])
			{
				if (m_GoapStates[STATE_IS_WALKING_ON_ORE])
				{
					auto map = m_WorldState->GetMap();
					SendCommand("prend " + Utils::str_split(map[0][std::floor(map[0].size() / 2)], " ")[0]);
					ReceiveCommand();
				}
				else if (m_GoapStates[STATE_IS_WALKING_ON_FOOD] && nourriture < 50 * 126)
				{
					SendCommand("prend nourriture");
					ReceiveCommand();
				}
				else if (m_GoapStates[STATE_IS_SEEING_ORE])
					Goto(m_WorldState->GetNeededOre());
				else
					Idle();
			}
			else m_GoapStates[STATE_START_RITUAL] = true;
		}
		else
			LookForFood();
	}
	std::cout << "apres while" << std::endl;

	std::cout << "Disconnected from server." << std::endl;
	delete m_GlobalContext.m_Server;
}

void Client::ParseMessage()
{
	for (Message message : m_Messages)
	{
		if (m_GoapStates[STATE_START_RITUAL])
		{
			if (message.message.find("join") != std::string::npos && message.message.find(m_id) != std::string::npos)
				group.push_back(Utils::str_split(message.message, ";")[1]);
			else if (m_GoapStates[STATE_WAIT_FOR_RESPONSE] && m_WorldState->GetResult() == -1 && message.message.find(m_WorldState->GetIdMaster()) != std::string::npos)
			{
				if (message.message.find("done") != std::string::npos)
					m_WorldState->SetResult(1);
				else if (message.message.find("failed") != std::string::npos)
					m_WorldState->SetResult(0);
				else if ((message.message.find("here") != std::string::npos || message.message.find("broadcast") != std::string::npos) && message.orientation != 0)
				{
					m_WorldState->SetIncantationDirection(message.orientation);
					m_GoapStates[STATE_JOINING_PLAYER] = true;
					m_GoapStates[STATE_START_RITUAL] = false;
					m_GoapStates[STATE_WAIT_FOR_RESPONSE] = false;
				}
			}
			else if (message.message.find("ready") != std::string::npos && message.orientation == 0 && m_GoapStates[STATE_WAITING_FOR_PLAYER])
				m_WorldState->IncNbPlayerReady();
		}
		else if (m_GoapStates[STATE_JOINING_PLAYER])
		{
			if ((message.message.find("here") != std::string::npos || message.message.find("broadcast") != std::string::npos) && message.message.find(m_WorldState->GetIdMaster()) != std::string::npos)
				m_WorldState->SetIncantationDirection(message.orientation);
		}
		else if (m_GoapStates[STATE_WAIT_FOR_RESPONSE] && message.message.find(m_id) != std::string::npos && message.message.find(m_WorldState->GetIdMaster()) != std::string::npos)
		{
			if (message.message.find("accept") != std::string::npos)
			{
				m_GoapStates[STATE_WAIT_FOR_RESPONSE] = false;
				m_GoapStates[STATE_JOINING_PLAYER] = true;
			}
			else if (message.message.find("deny") != std::string::npos)
			{
				m_GoapStates[STATE_WAIT_FOR_RESPONSE] = false;
				m_WorldState->SetIdMaster("");
				m_WorldState->SetIncantationDirection(-1);
				m_GoapStates[STATE_CAN_JOIN_PLAYER] = false;
			}
		}
		int isIncantatingAlone = m_GoapStates[STATE_START_RITUAL] && m_WorldState->GetIdMaster() == "" && m_WorldState->GetNbPlayer() == 1;
		if ((message.message.find("incantation") != std::string::npos && std::atoi(Utils::str_split(message.message, ":")[1].c_str()) == m_WorldState->GetLevel()) && ((!m_GoapStates[STATE_START_RITUAL] && !m_GoapStates[STATE_JOINING_PLAYER] && !m_GoapStates[STATE_WAIT_FOR_RESPONSE]) || isIncantatingAlone))
		{
			if (isIncantatingAlone)
			{
				for (std::string id : group)
				{
					id.erase(std::remove(id.begin(), id.end(), '\n'), id.end());
					SendCommand("broadcast deny:" + id + ";" + m_id);
					ReceiveCommand();
				}
				group.clear();
				ResetStates();
			}
			m_GoapStates[STATE_CAN_JOIN_PLAYER] = true;
			m_WorldState->SetIncantationDirection(message.orientation);
			m_WorldState->SetIdMaster(Utils::str_split(message.message, ";")[1].c_str());
		}
	}
	m_Messages.clear();
}

bool Client::CanSendCommand()
{
	return m_GlobalContext.commandsRemaining > 0;
}

void Client::LookForFood()
{
	if (m_GoapStates[STATE_IS_WALKING_ON_FOOD])
	{
		SendCommand("prend nourriture");
		ReceiveCommand();
	}
	else if (m_GoapStates[STATE_IS_SEEING_FOOD])
		Goto("nourriture");
	else
		Idle();
}

bool Client::SendCommand(std::string command)
{
	if (!CanSendCommand())
		return false;

	// send command
	std::string commandWithNewline = command + "\n";
	const char *commandToSend = commandWithNewline.c_str();
	int32_t count = m_GlobalContext.m_Server->Send(commandToSend, strlen(commandToSend));
	Console::Log("Sent command: " + command + " (" + std::to_string(count) + " bytes)");

	// add command to already sent commands
	m_GlobalContext.commandsRemaining--;
	return count > 0;
}

std::string Client::ReceiveCommand(bool wait_for_response)
{
	(void) wait_for_response;

	char buffer[1024];
	bzero(buffer, 1024);

	int result = m_GlobalContext.m_Server->Receive(buffer, 1024);
	if (result <= 0)
	{
		std::cout << "Erreur lors de la réception" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::string res = "";
	std::string response(buffer);
	for (std::string s : Utils::str_split(response, "\n"))
	{
		if (s.find("mort") != std::string::npos)
		{
			m_GlobalContext.appRunning = false;
			m_GlobalContext.m_Server->Disconnect();
			m_GlobalContext.m_Server->Close();
			exit(0);
		}
		else if (s.find("message") != std::string::npos)
		{
			std::string message = s.substr(8);
			int orientation = std::atoi(message.substr(0, 1).c_str());
			message = message.substr(2);
			m_Messages.push_back({ orientation, message });
		}
		else if (res.size() == 0)
			res = s;
	}
	if (res.size() == 0)
	{
		if (wait_for_response)
			return ReceiveCommand(wait_for_response);
		else
			return "";
	}

	m_GlobalContext.commandsRemaining++;
	Console::Log("Received response : " + response);
	return response;
}

bool Client::StartRitual()
{
	SendCommand("incantation");
	std::string response = ReceiveCommand();
	if (response.find("elevation en cours") == std::string::npos)
	{
		SendCommand("broadcast failed:" + m_id);
		ReceiveCommand();
		return false;
	}
	response = ReceiveCommand();
	SendCommand("broadcast done:" + m_id);
	ReceiveCommand();
	m_WorldState->IncLevel();
	return true;
}

std::string Client::GetInventory()
{
	SendCommand("inventaire");
	std::string response = ReceiveCommand();
	return response;
}

std::string Client::GetMap()
{
	SendCommand("voir");
	std::string response = ReceiveCommand();
	return response;
}

unsigned int hash3(unsigned int h1, unsigned int h2, unsigned int h3)
{
    return ((h1 * 2654435789U) + h2) * 2654435789U + h3;
}

void Client::Idle()
{
	std::random_device random;
	std::mt19937 generator(random());
	std::uniform_int_distribution<> distribution(1, 100);

	uint32_t rand = distribution(generator);
	if (rand < 33) SendCommand("avance"); 		// avance: 30% chance
	else if (rand < 66)	SendCommand("gauche"); // gauche: 30% chance
	else SendCommand("droite");					// droite: 30% chance
	ReceiveCommand();
}

void Client::Goto(std::string target)
{
	Pathfinding *path = m_WorldState->FindPath(target);
	for (std::string direction : path->GetMovement())
	{
		SendCommand(direction);
		ReceiveCommand();
	}
}

void Client::Goto(std::vector<std::string> target)
{
	Pathfinding *path = m_WorldState->FindPath(target);
	for (std::string direction : path->GetMovement())
	{
		SendCommand(direction);
		ReceiveCommand();
	}
}

void Client::ResetStates()
{
	m_GoapStates[STATE_START_RITUAL] = false;
	m_GoapStates[STATE_WAITING_FOR_PLAYER] = false;
	m_GoapStates[STATE_JOINING_PLAYER] = false;
	m_GoapStates[STATE_CAN_JOIN_PLAYER] = false;
	m_GoapStates[STATE_ARE_PLAYER_READY] = false;
	m_GoapStates[STATE_WAIT_FOR_RESPONSE] = false;
	m_GoapStates[STATE_IDLE] = false;

	m_WorldState->ResetNbPlayer();
	m_WorldState->ResetNbPlayerReady();
	m_WorldState->SetIncantationDirection(-1);
	m_WorldState->SetIdMaster("");
	m_WorldState->SetResult(-1);
}

bool Client::IsTeamFull()
{
	SendCommand("connect_nbr");
	std::string response = ReceiveCommand();
	int teamSpotAvailable = atoi(response.c_str());
	return teamSpotAvailable == 0;
}
