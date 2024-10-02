// test1.cpp: определяет точку входа для приложения.
//

#include "test1.h"
#include "Logger.h"
#include "Storage.h"
#include "TcpServer.h"
#include "ClientHandler.h"
#include <utility>

Storage storage{
	std::make_pair("key1", "value1"),
	std::make_pair("key2", "value2"),
	std::make_pair("key3", "value3"),
};

/*
*	TODO:
*	2) JSON VALIDATION
*	3) SEND RESPONSE TO CLIENT
*	ADDITIONAL:
*	4) NETWORK ERRORS TRY-CATCH
*/

int main()
{
	Localise();
	try
	{
		std::shared_ptr<TcpServer> Serv = TcpServer::Create(3333, 25, std::thread::hardware_concurrency());
		Serv->Run();
	}
	catch (std::exception& ex)
	{
		std::cerr << ex.what() << endl;
		Logger::error(ex.what());
		return 1;
	}
}
