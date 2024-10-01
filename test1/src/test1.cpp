// test1.cpp: определяет точку входа для приложения.
//

#include "test1.h"
#include "Logger.h"
#include "Storage.h"
#include "TcpServer.h"
#include "ClientHandler.h"
#include <memory>

Storage storage{
	std::make_pair("key1", "value1"),
	std::make_pair("key2", "value2"),
	std::make_pair("key3", "value3"),
};

/*
*	TODO:
*	1) MULTI-CLIENT SERVICE
*		1.1) переделать дек в сет
*		1.2) постить из клиентхэндлера запрос на собственное удаление
*	2) JSON VALIDATION
*	3) SEND RESPONSE TO CLIENT
*/

int main()
{
	Localise();
	try
	{
		TcpServer Serv(3333, 25, std::thread::hardware_concurrency());
		Serv.Run();
	}
	catch (std::exception& ex)
	{
		cout << ex.what() << endl;
		Logger::error(ex.what());
	}
}
