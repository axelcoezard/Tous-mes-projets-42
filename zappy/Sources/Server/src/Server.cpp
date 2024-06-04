#include "Server.hpp"
#include <iostream>

#include "Commands/GraphicCommand.hpp"
#include "Commands/EquipeCommand.hpp"
#include "Commands/AvanceCommand.hpp"
#include "Commands/DroiteCommand.hpp"
#include "Commands/GaucheCommand.hpp"
#include "Commands/VoirCommand.hpp"
#include "Commands/InventaireCommand.hpp"
#include "Commands/PrendCommand.hpp"
#include "Commands/PoseCommand.hpp"
#include "Commands/ExpulseCommand.hpp"
#include "Commands/BroadcastCommand.hpp"
#include "Commands/IncantationCommand.hpp"
#include "Commands/ForkCommand.hpp"
#include "Commands/ConnectNbrCommand.hpp"

void Server::Initialize(int argc, char **argv)
{
	GameProperties gameProperties;
	gameProperties.mapWidth = 25;
	gameProperties.mapHeight = 25;
	gameProperties.tickRate = TICK_RATE;

	if (!HasValidArguments(argc, argv))
	{
		std::cout	<< "Usage: ./server -p <port> -x <width> -y <height> -n <team> [<team>] [<team>] ... -c <nb> -t <t>\n"
					<< "\t-p port number\n\t-x world width\n\t-y world height\n\t-n team_name_1 team_name_2 ...\n"
					<< "\t-c number of clients authorized at the beginning of the game\n"
					<< "\t-t time unit divider (the greater t is, the faster the game will go)\n"
					<< "\t--debug to enable debug mode and see logs\n";
		exit(1);
	}


	m_TickRate = TICK_RATE; // default tickrate
	m_MaxClientsPerTeamAtBeginning = 10; // default max clients

	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-p")
			m_Port = std::stoi(argv[i + 1]);
		else if (std::string(argv[i]) == "-x")
			gameProperties.mapWidth = std::stoi(argv[i + 1]) * 3;
		else if (std::string(argv[i]) == "-y")
			gameProperties.mapHeight = std::stoi(argv[i + 1]) * 3;
		else if (std::string(argv[i]) == "-c")
			m_MaxClientsPerTeamAtBeginning = std::stoi(argv[i + 1]);
		else if (std::string(argv[i]) == "-t")
			m_TickRate = std::stoi(argv[i + 1]);
		else if (std::string(argv[i]) == "--debug")
			m_DebugMode = true;
	}

	if (m_TickRate < 1 || m_TickRate > 1000)
		throw std::runtime_error("Invalid tick rate. Must be between 1 and 1000");

	if (m_Port < 0 || m_Port > 65535)
		throw std::runtime_error("Invalid port number.");

	if (gameProperties.mapWidth < 10 * 3 || gameProperties.mapHeight < 10 * 3)
		throw std::runtime_error("Invalid map size. Must be at least 10x10.");

	if (m_MaxClientsPerTeamAtBeginning < 1 || m_MaxClientsPerTeamAtBeginning > MAX_CLIENTS)
		throw std::runtime_error("Invalid number of max clients per team at beginning. Must be between 1 and " + std::to_string(MAX_CLIENTS) + ".");

	m_CommandManager.On("graphic", new GraphicCommand(), 0);
	m_CommandManager.On("equipe", new EquipeCommand(), 0);
	m_CommandManager.On("avance", new AvanceCommand(), 7);
	m_CommandManager.On("droite", new DroiteCommand(), 7);
	m_CommandManager.On("gauche", new GaucheCommand(), 7);
	m_CommandManager.On("voir", new VoirCommand(), 7);
	m_CommandManager.On("inventaire", new InventaireCommand(), 1);
	m_CommandManager.On("prend", new PrendCommand(), 7);
	m_CommandManager.On("pose", new PoseCommand(), 7);
	m_CommandManager.On("expulse", new ExpulseCommand(), 7);
	m_CommandManager.On("broadcast", new BroadcastCommand(), 7);
	m_CommandManager.On("incantation", new IncantationCommand(), 300);
	m_CommandManager.On("fork", new ForkCommand(), 42);
	m_CommandManager.On("connect_nbr", new ConnectNbrCommand(), 0);

	gameProperties.tickRate = m_TickRate;

	m_Clock = Clock();
	m_Game = new Game(gameProperties);
	m_Game->SetDebugMode(m_DebugMode);
	m_Game->SetMaxClientsPerTeamAtBeginning(m_MaxClientsPerTeamAtBeginning);

	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-n")
		{
			for (int j = i + 1; j < argc; j++)
			{
				if (argv[j][0] == '-')
					break;
				m_Game->AddTeam(argv[j]);
			}
			break;
		}
	}
	m_Game->Initialize();
}

bool Server::isNumericAndPositive(const std::string& str)
{
	auto it = std::find_if(str.begin(), str.end(), [](char const &c) {
		return !std::isdigit(c);
	});

	return !str.empty() && it == str.end();
}

bool Server::HasValidArguments(int argc, char **argv)
{
	// server should be called with at least: -p <port> -x <width> -y <height> -n <team> -c <nb> -t <t>
	// -n can be followed by multiple team names

	bool hasPort = false, hasWidth = false, hasHeight = false, hasTeam = false, hasMaxClients = false, hasTickRate = false;

	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-p")
			hasPort = isNumericAndPositive(argv[i + 1]);
		else if (std::string(argv[i]) == "-x")
			hasWidth = isNumericAndPositive(argv[i + 1]);
		else if (std::string(argv[i]) == "-y")
			hasHeight = isNumericAndPositive(argv[i + 1]);
		else if (std::string(argv[i]) == "-c")
			hasMaxClients = isNumericAndPositive(argv[i + 1]);
		else if (std::string(argv[i]) == "-t")
			hasTickRate = isNumericAndPositive(argv[i + 1]);
		else if (std::string(argv[i]) == "-n")
			hasTeam = !std::string(argv[i + 1]).starts_with("-");
	}

	return hasPort && hasWidth && hasHeight && hasTeam && hasMaxClients && hasTickRate;
}

void Server::Start()
{
	m_Socket = Socket(m_Port);
	m_Socket.SetOption(SOCKET_REUSE_ADRESS, 1);

	if (!m_Socket.Bind())
		throw std::runtime_error("Failed to bind socket.");

	if (!m_Socket.Listen())
		throw std::runtime_error("Failed to listen.");

	m_ReadSet.Zero();
	m_ReadSet.Set(&m_Socket);

	Console::Log("Server listening on port " + std::to_string(m_Port));

	while (42) // LOL
	{
		m_Clock.After();

		// First, listen to clients and messages every tick
		if (ListenToClients() == SERVER_FAIL)
		{
			Console::Error("Erreur lors de l'écoute des clients : " + std::string(strerror(errno)));
			break;
		}

		// Then, check if we can tick
		if (m_Clock.GetElapsedTime() < 1.0f / (float) m_TickRate)
			continue;

		// Execute commands that are ready in the queue
		m_CommandQueue.Execute(&m_CommandManager, m_Game);

		// Tick the game
		m_Clock.Before();

		// Update the game, if a team has won, pause the server
		if (!m_Game->Update())
		{
			Console::Log("Game over.");
			break;
		}

		m_Game->IncTicks();
	}

	Stop();
}

void Server::Stop()
{
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (m_Clients[i].IsSet())
		{
			m_Clients[i].Close();
			Console::Log("Client " + std::to_string(i) + " disconnected.");
		}
	}

	m_Socket.Close();

	Console::Log("Server stopped.");
}

int32_t Server::ListenToClients()
{
	DescriptorSet tmpSet = m_ReadSet; // Copie de l'ensemble pour select

	// Ajout d'un délai d'attente pour éviter de bloquer le thread
	struct timeval tv;
	tv.tv_sec = 0;	// Temps d'attente en secondes
	tv.tv_usec = 0; // Temps d'attente en microsecondes

	// Utilisation de select pour gérer les événements sur les sockets
	int activity = select(m_ReadSet.GetMaxFd() + 1, &tmpSet.GetSet(), nullptr, nullptr, &tv);
	if (activity == SERVER_SKIP || activity == SERVER_FAIL)
	{
		return activity;
	}

	// Vérifier si le serveur a une nouvelle connexion
	if (m_Game->GetClientsCount() < MAX_CLIENTS && tmpSet.IsSet(&m_Socket))
	{
		Socket newClientSocket;
		if (!m_Socket.Accept(&newClientSocket))
			return SERVER_SKIP;

		// Ajouter le nouveau client à l'ensemble
		for (int i = 0; i < MAX_CLIENTS; ++i)
		{
			if (!m_Clients[i].IsSet())
			{
				m_Clients[i] = newClientSocket;
				m_ReadSet.Set(&newClientSocket);
				break;
			}
		}

		Client* client = m_Game->AddPlayer(&newClientSocket);
		client->SendMessage("BIENVENUE");

		Console::Log("Connexion établie avec un client.");
	}

	// Vérifier les sockets des clients existants
	for (int i = 0; i < MAX_CLIENTS; ++i)
	{
		if (!m_Clients[i].IsSet() || !tmpSet.IsSet(&m_Clients[i]))
			continue;

		Client* client = m_Game->GetPlayerBySocket(&m_Clients[i]);
		if (client == nullptr)
			continue;

		char buffer[1024];
		std::memset(buffer, 0, 1024);
		int32_t bytesRead = m_Clients[i].Receive(buffer, 1024);

		if (bytesRead < 0)
		{
			Console::Log("Client déconnecté.");
			// Erreur ou client déconnecté, fermer la connexion
			if (client->GetType() == ClientType::GRAPHIC)
				m_Game->SetGraphicClient(nullptr);
			else
				m_Game->RemovePlayer(&m_Clients[i]);

			m_ReadSet.Clear(&m_Clients[i]);
			m_Clients[i].Close();
			m_Clients[i] = 0;
			continue;
		}

		if (Utils::str_trim(buffer, "\t\v\r\f\n").empty())
			continue;

		if (std::string(buffer).find("\n") == std::string::npos)
		{
			client->m_Buffer += std::string(buffer);
			continue;
		}

		if (client->m_Buffer.empty())
			client->m_Buffer = std::string(buffer);

		std::vector<std::string> cmd_line = Utils::str_split(client->m_Buffer, "\n");
		for (size_t j = 0; j < cmd_line.size(); ++j)
		{
			if (cmd_line[j].empty())
				continue;

			std::vector<std::string> cmd_args = Utils::str_split(cmd_line[j], " ");
			std::string cmd_name = Utils::str_trim(cmd_args[0], " \t\r\n\v\f");

			for (size_t k = 0; k < cmd_args.size(); ++k)
				cmd_args[k] = Utils::str_trim(cmd_args[k], " \t\r\n\v\f");

			if (m_DebugMode)
				Console::Print("RECEIVE", cmd_line[j] + " | par " + std::to_string(m_Clients[i].m_Instance), Console::BLUE);

			if (!client->IsConnected()){
				if (cmd_name == "GRAPHIC") {
					m_CommandManager.Call("graphic", cmd_args, m_Game, client);
				} else {
					std::vector<std::string> args = { cmd_name };
					m_CommandManager.Call("equipe", args, m_Game, client);
				}
			} else {
				if (cmd_args.size() >= 1)
					cmd_args = std::vector<std::string>(cmd_args.begin() + 1, cmd_args.end());

				CommandSummary summary;
				summary.name = cmd_name;
				summary.arguments = cmd_args;
				summary.player = client;
				summary.remainingDelay = m_CommandManager.GetDelay(cmd_name);

				if (m_CommandManager.Verify(cmd_name, cmd_args, m_Game, client))
					m_CommandQueue.Push(summary);
			}
		}
		client->m_Buffer.clear();
	}
	return SERVER_SUCCESS;
}

int32_t Server::GetPort() const
{
	return m_Port;
}

bool Server::IsDebugMode() const
{
	return m_DebugMode;
}
