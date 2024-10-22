#pragma once

#include "Network/Socket.hpp"
#include "Threads/Thread.hpp"
#include "GlobalContext.hpp"

class GraphicClient
{
private:
	std::string m_Hostname = "127.0.0.1";
	int32_t m_Port;

	GlobalContext m_GlobalContext;

	Thread* m_OpenGLThread;
	Thread* m_SocketThread;

public:
	GraphicClient();
	~GraphicClient();

	void Initialize(int argc, char **argv);
	void Start();
};
