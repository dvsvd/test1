// test1.cpp: определяет точку входа для приложения.
//

#include "test1.h"
#include "Logger.h"
#include "Storage.h"
#include "globals.h"
#include <memory>
#include <future>


/*
*	TODO:
*	1) MULTI-CLIENT SERVICE
*	2) JSON VALIDATION
*	3) SEND RESPONSE TO CLIENT
*/

int main()
{
	Localise();
	std::string val;
	char dummy[BUFLEN] = { 0 };
	mutable_buffer buf = buffer(dummy, BUFLEN);
	try
	{
		io_context actx;
		io_context ioctx(4);
		tcp::endpoint tcp_endpoint(tcp::v4(), 3333);
		tcp::acceptor tcp_acceptor(actx, tcp_endpoint);
		tcp::socket tcp_socket(ioctx);
		tcp_acceptor.listen(0);
		wcout << L"Программа начала приём соединения" << endl;
		Logger::log("Программа начала приём соединения");
		tcp_acceptor.accept(tcp_socket);
		Logger::log("Программа приняла соединение с адреса " + tcp_socket.remote_endpoint().address().to_string());
		wcout << L"Соединение установлено" << endl;
		string msg;
		while(true)
		{
			//TODO DEBUG
			std::future<size_t> f = tcp_socket.async_receive(buf, use_future);
			//ioctx.run();
			size_t nBytesRead = f.get();
			
		};
		json request = json::parse(msg, Functions::ValidationProc);
		
	}
	catch (std::runtime_error& ex)
	{
		cout << ex.what() << endl;
	}
}
