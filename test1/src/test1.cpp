// test1.cpp: определяет точку входа для приложения.
//

#include "test1.h"
#include "Logger.h"
#include "Storage.h"
#include "ThreadGroup.h"
#include "ClientHandler.h"
#include <memory>
#include <deque>

Storage storage{
	std::make_pair("key1", "value1"),
	std::make_pair("key2", "value2"),
	std::make_pair("key3", "value3"),
};

/*
*	TODO:
*	1) MULTI-CLIENT SERVICE
*		1.1) create_thread FUNC
*	2) JSON VALIDATION
*	3) SEND RESPONSE TO CLIENT
*/

int main()
{
	Localise();
	try
	{
		//io_context actx;
		std::deque<ClientHandler> handlers;
		thread_pool tp(std::thread::hardware_concurrency());
		io_context ioctx(std::thread::hardware_concurrency());
		auto work_guard = make_work_guard(ioctx);
		tcp::endpoint tcp_endpoint(tcp::v4(), 3333);
		tcp::acceptor tcp_acceptor(ioctx, tcp_endpoint);
		tcp_acceptor.listen(tcp::acceptor::max_listen_connections);
		//tcp::socket tcp_socket(ioctx);
		//wcout << L"Программа начала приём соединения" << endl;
		//Logger::log("Программа начала приём соединения");
		tcp_acceptor.async_accept(
			[&](
			const boost::system::error_code& ec, // Result of operation.
				boost::asio::ip::tcp::socket s // On success, the newly accepted socket.
				)
			{
				if (!ec)
					handlers.push_back(ClientHandler(std::move(s)));
			});
		//Logger::log("Программа приняла соединение с адреса " + tcp_socket.remote_endpoint().address().to_string());
		//wcout << L"Соединение устано6влено" << endl;
		
		for (size_t i = 0; i < std::thread::hardware_concurrency(); i++)
		{
			post(tp, std::bind(static_cast<size_t(io_context::*)()>(&io_context::run), &ioctx));
		}
		//json request = json::parse(msg, Functions::ValidationProc);
		wcout << L"Server Started" << endl;
		Logger::log("Server Started");
		tp.join();
	}
	catch (std::runtime_error& ex)
	{
		cout << ex.what() << endl;
		Logger::error(ex.what());
	}
}
