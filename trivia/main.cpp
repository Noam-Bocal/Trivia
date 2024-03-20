#pragma comment (lib, "ws2_32.lib")

#include "WSAInitializer.h"
#include "Server.h"
#include "pch.h"

int main()
{
	try
	{
		IDatabase* data = new SqliteDataBase("triviadb.db");
		WSAInitializer wsaInit;
		Server myServer(data);
		myServer.run();
	}
	catch (std::exception& e)
	{
		std::cout << "Error occured: " << e.what() << std::endl;
	}
	return 0;
}

