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
#include "TcpServer.h"
#include "Functions.h"
#include "Logger.h"
#include <algorithm>

TcpServer::TcpServer(unsigned short port, size_t maxClients, size_t concurrency, int backlog)
	:	m_tp(concurrency),
	m_ioctx(concurrency),
	m_work(m_ioctx),
	m_work_guard(make_work_guard(m_ioctx)),
	m_acceptor(m_ioctx, tcp::endpoint(tcp::v4(), port)),
	m_port(port),
	m_backlog(backlog),
	m_max_clients(maxClients),
	m_concurrency(concurrency)
{
	m_acceptor.set_option(socket_base::reuse_address(true));
	m_acceptor.set_option(socket_base::keep_alive(true));
	m_acceptor.listen(backlog);
}

TcpServer::pointer_type TcpServer::Create(unsigned short port, size_t maxClients, size_t concurrency, int backlog)
{
	pointer_type inst = std::make_shared<TcpServer>(port, maxClients, concurrency, backlog);
	inst->StartAccept();
	return inst;
}

void TcpServer::StartAccept()
{
	HANDLER_LOCATION;
	ClientHandler::pointer_type ptr = std::make_shared<ClientHandler>(std::ref(m_ioctx), weak_from_this());
	m_acceptor.async_accept(ptr->socket(),
		[this, ptr](const boost::system::error_code& ec)
		{
			HANDLER_LOCATION;
			if (!ec)
			{
				std::unique_lock l(m_lock);
				m_handlers.insert(ptr);
				ptr->start();
#ifdef _DEBUG
				cout << "Accepted connection" << endl;
#endif // _DEBUG
			}
			StartAccept();
		}
	);
}
void TcpServer::Run()
{
	for (size_t i = 0; i < m_concurrency; i++)
	{
		post(m_tp, std::bind(static_cast<size_t(io_context::*)()>(&io_context::run), &m_ioctx));
	}
	Logger::log("Server Started");
	cout << "Server successfully started on port "
		<< m_port << " and interface "
		<< m_acceptor.local_endpoint().address().to_string()
		<< ".\nAccepting connections..."
		<< endl;
	cout.clear();
	m_tp.join();
}

void TcpServer::Disconnect(const std::shared_ptr<ClientHandler>& handler)
{
	HANDLER_LOCATION;
	std::unique_lock l(m_lock);
	m_handlers.erase(handler);
}

TcpServer::~TcpServer()
{
	m_ioctx.stop();
	m_acceptor.cancel();
	m_acceptor.close();
}