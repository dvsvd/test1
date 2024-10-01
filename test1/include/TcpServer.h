#pragma once
#include "CommonIncludes.h"
#include "ClientHandler.h"
#include <thread>
#include <unordered_set>
#include <shared_mutex>

using std::string;
using std::wstring;
using std::cout;
using std::wcout;
using std::endl;

class TcpServer
{
public:
	TcpServer(unsigned short port = 3030, size_t maxClients = 25,
		size_t concurrency = 1,
		int backlog = tcp::acceptor::max_listen_connections);
	void Run();
	void Disconnect(const ClientHandler& handler);
	~TcpServer();
private:
	friend class ClientHandler;
	typedef unsigned int id_t;
	int m_backlog;
	unsigned short m_port;
	size_t m_max_clients;
	size_t m_concurrency;
	std::shared_mutex m_lock;
	std::unordered_set<ClientHandler> m_handlers;
	thread_pool m_tp;
	io_context m_ioctx;
	executor_work_guard<io_context::executor_type> m_work_guard;
	tcp::acceptor m_acceptor;
};