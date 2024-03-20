#pragma once
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <queue>
#include "LoginRequestHandler.h"
#include "pch.h"
#include <mutex>
#include <fstream>
#include "JsonRequestPacketDeserializer.h"
#include "Helper.h"

#include "IDatabase.h"
#include "RequestHandlerFactory.h"

class Communicator
{
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_client;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
	//methods
	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);

public:
	Communicator(IDatabase* database);
	~Communicator();
	void startHandleRequests();
};

