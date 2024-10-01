#include "TcpServer.h"
#include "functions.h"
#include "Logger.h"
#include <algorithm>

TcpServer::TcpServer(unsigned short port, size_t maxClients, size_t concurrency, int backlog)
	:	m_tp(concurrency),
	m_ioctx(concurrency),
	m_work_guard(make_work_guard(m_ioctx)),
	m_acceptor(m_ioctx, tcp::endpoint(tcp::v4(), port)),
	m_port(port),
	m_backlog(backlog),
	m_max_clients(maxClients),
	m_concurrency(concurrency)
{
	m_acceptor.set_option(socket_base::reuse_address(true));
	m_acceptor.listen(backlog);
}

void TcpServer::Run()
{
	m_acceptor.async_accept(
		[&](
			const boost::system::error_code& ec, // Result of operation.
			boost::asio::ip::tcp::socket s // On success, the newly accepted socket.
			)
		{
			if (!ec)
			{
				std::unique_lock l(m_lock);
				m_handlers.insert(ClientHandler(std::move(s)));
			}
		});
	//Logger::log("Программа приняла соединение с адреса " + tcp_socket.remote_endpoint().address().to_string());
	//wcout << L"Соединение устано6влено" << endl;

	for (size_t i = 0; i < m_concurrency; i++)
	{
		post(m_tp, std::bind(static_cast<size_t(io_context::*)()>(&io_context::run), &m_ioctx));
	}
	//json request = json::parse(msg, Functions::ValidationProc);
	Logger::log("Server Started");
	cout << "Server successfully started on port "
		<< m_port << " and interface "
		<< m_acceptor.local_endpoint().address().to_string()
		<< ".\nAccepting connections..."
		<< endl;
	cout.clear();
	m_tp.join();
}

void TcpServer::Disconnect(const ClientHandler& handler)
{
	std::unique_lock l(m_lock);
	m_handlers.erase(handler);
}

TcpServer::~TcpServer()
{
	m_ioctx.stop();
	m_acceptor.cancel();
	m_acceptor.close();
}