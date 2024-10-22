#pragma once

#include <ResourceType.hpp>

class Team;
class Game;

enum class ClientType
{
	GRAPHIC,
	PLAYER
};

class Client
{
private:
	Game* m_Game;

	int32_t m_SocketFd;
	bool m_IsConnected;
	ClientType m_Type = ClientType::PLAYER;

	int32_t m_Id;
	int32_t m_Position[2] = { 0, 0 };
	int32_t m_Direction[2] = { 1, 0 };

	Team* m_Team;
	bool m_hasTeam = false;

	int32_t m_Inventory[RESSOURCES_COUNT];
	int32_t m_Level;

	int32_t m_isEgg = false;

public:
	std::string m_Buffer;

public:
	Client(int32_t id, int32_t socketFd, Game* game);
	~Client();

	void SendMessage(const std::string& message);

	void DecreaseHealth(int32_t value);
	void IncreaseHealth(int32_t value);

	void MoveForward();
	void RotateLeft();
	void RotateRight();

private:
	void Rotate(float angle);

public:
	int32_t GetId();

	void SetType(ClientType type);
	ClientType GetType();

	void SetTeam(Team* team);
	Team* GetTeam();

	int32_t GetPosition(int32_t index);
	int32_t GetX();
	int32_t GetY();

	void SetIsEgg(bool isEgg);

	void SetPosition(int32_t index, int32_t value);
	void SetX(int32_t x);
	void SetY(int32_t y);

	int32_t GetDirection(int32_t index);
	int32_t GetDirectionX();
	int32_t GetDirectionY();
	int32_t GetOrientation();

	void SetDirection(int32_t index, int32_t value);
	void SetDirectionX(int32_t x);
	void SetDirectionY(int32_t y);

	void SetResource(int32_t index, int32_t value);
	void IncreaseResource(int32_t index, int32_t value);
	void DecreaseResource(int32_t index, int32_t value);

	int32_t GetResource(int32_t index);
	bool HasResource(int32_t type);
	bool HasResource(int32_t amount, ResourceType type);
	bool HasResource(int32_t amount, int32_t type);

	int32_t GetLevel();
	void IncreaseLevel();

	int32_t GetHealth();

	int32_t GetSocketFd();

	void SetConnected(bool value);
	bool IsConnected();

	bool HasTeam();
};
