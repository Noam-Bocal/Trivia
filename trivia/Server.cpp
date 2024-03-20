#include "Server.h"


Server::Server(IDatabase* data) : m_database(data), m_communicator(new Communicator(data)), m_handlerFactory(data)
{
    
}

Server::~Server()
{
}

void Server::run()
{
    std::cout << "Starting server..." << std::endl;

    WSAInitializer wsaInit;
 
    // Create a communicator and start handling requests
   
    std::thread threadHandleRequests(&Communicator::startHandleRequests, m_communicator);

    // Wait for console input
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "EXIT") {
            break;
        }
    }

    // Cleanup
    threadHandleRequests.detach();
    delete m_communicator;

}
