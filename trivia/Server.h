#pragma once
#include "Communicator.h"
#include <WinSock2.h>
#include <Windows.h>
#include "pch.h"
#include "IDatabase.h"
#include "RequestHandlerFactory.h"
class Server
{
private:
	Communicator* m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
public:
	Server(IDatabase* data);
	~Server();
	void run();
};

