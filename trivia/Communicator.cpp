#include "Communicator.h"

Communicator::Communicator(IDatabase* database) : m_handlerFactory(database)
{
	m_database = database;
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try {
		// Close all the client sockets
		for (auto& client : m_client) {
			closesocket(client.first);
		}
		m_client.clear();

		// Close the server socket
		closesocket(m_serverSocket);
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	while (true)
	{
		bindAndListen();

	}
}

void Communicator::bindAndListen()
{
	std::cout << "Starting..." << std::endl;
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(12345); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	std::cout << "binding..." << std::endl;
	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening..." << std::endl;

	while (true)
	{
	
		std::cout << "accepting clients..." << std::endl;
		SOCKET clientSocket = accept(m_serverSocket, NULL, NULL);
		if (clientSocket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__ " - accept");

		std::cout << "Client accepted" << std::endl;
		m_client[clientSocket] = new LoginRequestHandler(m_handlerFactory);
		std::thread (&Communicator::handleNewClient, this, clientSocket).detach();
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	/* Getting requests from the client */
	while (true)
	{
		/* Getting the packet from the socket. */
		std::string packet;
		try
		{
			packet = Helper::getAllTheSocket(clientSocket);
		}
		catch (const std::exception& e)
		{
			closesocket(clientSocket);
			m_client.erase(clientSocket);
			return; // End thread execution
		}

		RequestInfo info(packet);  // Analyzing the packet

		if (!m_client[clientSocket]->isRequestRelevant(info))
		{
			ErrorResponse errResponse{ "Request is not relevant." };
			Helper::sendData(clientSocket, JsonResponsePacketSerializer::serializeResponse(errResponse));
		}
		else
		{
			RequestResult result = m_client[clientSocket]->handleRequest(info);  // Passing the request to the handler.
			cout << "Data sent: " << result.response << endl;
			Helper::sendData(clientSocket, result.response);       // Sending response to the client
			IRequestHandler* temp = m_client[clientSocket];
			if (temp != result.newHandler)
			{
				m_client[clientSocket] = result.newHandler; // Moving to the next state (updating handler).
				delete temp;
			}
		}
	}
	closesocket(clientSocket);
	m_client.erase(clientSocket);
}
