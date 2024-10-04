/*
Copyright 2024 D. Kochetov (github.com/dvsvd)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#pragma once
#include "CommonIncludes.h"
#include "ClientHandler.h"
#include <thread>
#include <unordered_set>
#include <shared_mutex>
#include <memory>

using std::string;
using std::wstring;
using std::cout;
using std::wcout;
using std::endl;

class TcpServer : public std::enable_shared_from_this<TcpServer>
{
public:
	using element_type = ClientHandler::pointer_type;
	using pointer_type = std::shared_ptr<TcpServer>;
	// DO NOT USE: exposed for std::make_shared purposes
	TcpServer(unsigned short port, size_t maxClients,
		size_t concurrency,
		int backlog);
	static pointer_type Create(unsigned short port = 3030, size_t maxClients = 25,
		size_t concurrency = 1,
		int backlog = tcp::acceptor::max_listen_connections);
	void StartAccept();
	void Run();
	void Disconnect(const std::shared_ptr<ClientHandler>& handler);
	~TcpServer();
private:
	friend class ClientHandler;
	typedef unsigned int id_t;
	int m_backlog;
	unsigned short m_port;
	size_t m_max_clients;
	size_t m_concurrency;
	std::shared_mutex m_lock;
	std::unordered_set<element_type> m_handlers;
	thread_pool m_tp;
	io_context m_ioctx;
	io_context::work m_work;
	executor_work_guard<io_context::executor_type> m_work_guard;
	tcp::acceptor m_acceptor;
};
