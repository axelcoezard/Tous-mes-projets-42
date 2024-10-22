#include "Client.hpp"
#include "Team.hpp"
#include "Network/Socket.hpp"
#include "Game.hpp"
#include "Map.hpp"

Client::Client(int32_t id, int32_t socketFd, Game* game)
{
	std::memset(m_Inventory, 0, sizeof(int32_t) * 7);

	m_Game = game;
	m_Id = id;
	m_SocketFd = socketFd;
	m_IsConnected = false;
	m_Level = 1;

	m_Inventory[static_cast<int>(ResourceType::Nourriture)] = 1260;

	m_hasTeam = false;
	m_isEgg = false;
}

Client::~Client()
{

}

void Client::SendMessage(const std::string& message)
{
	std::string tmp = message + "\n";

	int32_t flags = MSG_NOSIGNAL;
		#ifdef SO_NOSIGPIPE
			SetOption(SO_NOSIGPIPE, 1);
		#endif
	send(m_SocketFd, tmp.c_str(), tmp.size(), flags);

	if (m_Game->IsDebugMode())
		Console::Print("SENT", message + " pour " + std::to_string(m_SocketFd), Console::BLUE);
}

void Client::DecreaseHealth(int32_t value)
{
	m_Inventory[static_cast<int>(ResourceType::Nourriture)] -= value;
}

void Client::IncreaseHealth(int32_t value)
{
	m_Inventory[static_cast<int>(ResourceType::Nourriture)] += value;
}

void Client::MoveForward()
{
	int32_t mapWidth = m_Game->GetMap()->GetWidth();
	int32_t mapHeight = m_Game->GetMap()->GetHeight();

	m_Position[0] += m_Direction[0];
	m_Position[1] += m_Direction[1];

	if (m_Position[0] < 0)
		m_Position[0] = (m_Position[0] + mapWidth) % mapWidth;
	else if (m_Position[0] >= mapWidth)
		m_Position[0] = m_Position[0] % mapWidth;
	if (m_Position[1] < 0)
		m_Position[1] = (m_Position[1] + mapHeight) % mapHeight;
	else if (m_Position[1] >= mapHeight)
		m_Position[1] = m_Position[1] % mapHeight;
}

void Client::RotateLeft()
{
	Rotate(-90.0f);
}

void Client::RotateRight()
{
	Rotate(90.0f);
}

void Client::Rotate(float angle)
{
	double radian = angle * (M_PI / 180.0f);

	double x = m_Direction[0];
	double y = m_Direction[1];

	m_Direction[0] = (int32_t) (x * cos(radian) - y * sin(radian));
	m_Direction[1] = (int32_t) (x * sin(radian) + y * cos(radian));
}

int32_t Client::GetId()
{
	return m_Id;
}

void Client::SetType(ClientType type)
{
	m_Type = type;
}

ClientType Client::GetType()
{
	return m_Type;
}

void Client::SetTeam(Team* team)
{
	m_Team = team;
	m_hasTeam = true;
}

Team* Client::GetTeam()
{
	return m_Team;
}

bool Client::HasTeam()
{
	return m_hasTeam;
}

int32_t Client::GetPosition(int32_t index)
{
	return m_Position[index];
}

int32_t Client::GetX()
{
	return m_Position[0];
}

int32_t Client::GetY()
{
	return m_Position[1];
}

void Client::SetIsEgg(bool isEgg)
{
	m_isEgg = isEgg;
}

void Client::SetPosition(int32_t index, int32_t value)
{
	m_Position[index] = value;
}

void Client::SetX(int32_t x)
{
	m_Position[0] = x;
}

void Client::SetY(int32_t y)
{
	m_Position[1] = y;
}

int32_t Client::GetDirection(int32_t index)
{
	return m_Direction[index];
}

int32_t Client::GetDirectionX()
{
	return m_Direction[0];
}

int32_t Client::GetDirectionY()
{
	return m_Direction[1];
}

int32_t Client::GetOrientation()
{
	if (m_Direction[0] == 1 && m_Direction[1] == 0) // East
		return 1;
	if (m_Direction[0] == 0 && m_Direction[1] == 1) // South
		return 2;
	if (m_Direction[0] == -1 && m_Direction[1] == 0) // West
		return 3;
	if (m_Direction[0] == 0 && m_Direction[1] == -1) // North
		return 4;
	return 0;
}

void Client::SetDirection(int32_t index, int32_t value)
{
	m_Direction[index] = value;
}

void Client::SetDirectionX(int32_t x)
{
	m_Direction[0] = x;
}

void Client::SetDirectionY(int32_t y)
{
	m_Direction[1] = y;
}

void Client::SetResource(int32_t index, int32_t value)
{
	if (value < 0)
		value = 0;
	m_Inventory[index] = value;
}

void Client::IncreaseResource(int32_t index, int32_t value)
{
	m_Inventory[index] += value;
}

void Client::DecreaseResource(int32_t index, int32_t value)
{
	m_Inventory[index] -= value;
}

int32_t Client::GetResource(int32_t index)
{
	return m_Inventory[index];
}

bool Client::HasResource(int32_t type)
{
	return m_Inventory[type] > 0;
}

bool Client::HasResource(int32_t amount, int32_t type)
{
	return m_Inventory[type] >= amount;
}

bool Client::HasResource(int32_t amount, ResourceType type)
{
	return HasResource(amount, static_cast<int32_t>(type));
}

int32_t Client::GetLevel()
{
	return m_Level;
}

void Client::IncreaseLevel()
{
	m_Level++;
}

int32_t Client::GetHealth()
{
	return m_Inventory[static_cast<int>(ResourceType::Nourriture)];
}


void Client::SetConnected(bool value)
{
	m_IsConnected = value;
}

bool Client::IsConnected()
{
	return m_IsConnected;
}

int32_t Client::GetSocketFd()
{
	return m_SocketFd;
}
