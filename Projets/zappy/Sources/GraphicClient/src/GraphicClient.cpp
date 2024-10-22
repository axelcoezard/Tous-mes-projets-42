#include "GraphicClient.hpp"
#include "Utils.hpp"
#include <Console.hpp>

#include "Threads/OpenGLThread.hpp"
#include "Threads/SocketThread.hpp"

GraphicClient::GraphicClient()
{
	std::memset((void *)&m_GlobalContext, 0, sizeof(m_GlobalContext));
}

GraphicClient::~GraphicClient()
{
	m_GlobalContext.teams.clear();
}

void GraphicClient::Initialize(int argc, char **argv)
{
	if (argc < 3)
		throw std::runtime_error("Usage: ./graphic_client -p <port> [-h <hostname>]");

	for (int i = 1; i < argc; i++)
	{
		if (std::string(argv[i]) == "-p")
		{
			m_Port = std::stoi(argv[i + 1]);
		}
		else if (std::string(argv[i]) == "-h")
		{
			m_Hostname = argv[i + 1];
		}
	}

	m_GlobalContext.appRunning = true;
	m_GlobalContext.followedUserId = -1;
	m_GlobalContext.hasPlayers = false;
	m_GlobalContext.hasTeams = false;
	m_GlobalContext.hasMapSize = false;
	m_GlobalContext.hasTickRate = false;
	m_GlobalContext.hasWinner = false;
	m_GlobalContext.hasGameOver = false;
	m_SocketThread = new SocketThread(&m_GlobalContext, m_Hostname, m_Port);
	m_OpenGLThread = new OpenGLThread(&m_GlobalContext, 1100, 800);
}

void GraphicClient::Start()
{
	m_SocketThread->Initialize();
	m_OpenGLThread->Initialize();

	// Threads are running

	m_SocketThread->Wait();
	m_OpenGLThread->Wait();

	delete m_SocketThread;
	delete m_OpenGLThread;
}
