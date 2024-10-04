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
#include "ClientHandler.h"
#include "Logger.h"
#include "TcpServer.h"
#include "Functions.h"
#include "JsonValidator.h"

extern const std::unordered_map<std::string, JsonValidator> g_validators;

ClientHandler::ClientHandler(tcp::socket s, server_ptr_type serv)
	: m_s(std::move(s)),
	m_serv(serv)
{
}

ClientHandler::ClientHandler(io_context& ctx, server_ptr_type serv)
	: m_s(ctx),
	m_serv(serv)
{
}

ClientHandler::ClientHandler(ClientHandler&& o) noexcept
	: m_s(std::move(o.m_s)),
	m_serv(std::move(o.m_serv)),
	m_msg(std::move(o.m_msg)),
	m_buf(std::move(o.m_buf)),
	isHandled(o.isHandled)
{
	memmove(dummy, o.dummy, BUFLEN);
}

void ClientHandler::handle_client(pointer_type inst,
	const boost::system::error_code& error,
	size_t nBytesRead
	)
{
	if (error == error::eof || error == error::connection_reset)
	{
		// Handle disconnect
		post(inst->m_serv.lock()->m_ioctx,
			[&]() mutable { HANDLER_LOCATION;
		inst->m_serv.lock()->Disconnect(inst);
		wcout << L"Client disconnected" << endl;
		Logger::log("Client disconnected");
		});
		return;
	}
	switch (nBytesRead)
	{
	case BUFLEN:
		inst->m_msg += buffer_cast<char*>(inst->m_buf);
		memset(buffer_cast<char*>(inst->m_buf), 0, BUFLEN);
		inst->isHandled = inst->m_s.available() == 0;
		break;
	default:
		inst->m_msg += buffer_cast<char*>(inst->m_buf);
		inst->isHandled = true;
#ifdef _DEBUG
		cout << "Read incoming client message: " << inst->m_msg << endl;
#endif // _DEBUG
		break;
	}
	if (inst->isHandled)
	{
		post(inst->m_serv.lock()->m_ioctx, [msg = inst->m_msg, inst]() {
			HANDLER_LOCATION;
			json request, response;
			try {
				request = json::parse(msg);
				auto validator_it = g_validators.find(request["request"]);
				if (validator_it == g_validators.end()) {
					// send no such schema error to client
					response["status"] = "error";
					response["error"] = "No such schema present";
				}
				if (validator_it->second.validate(request)) {
					response = Operations::map.at(request["request"])(request);
				}
				else {
					// send validation error to client
					response["status"] = "error";
					response["error"] = "Invalid JSON document";
				}
			}
			catch (const json::exception& ex) {
				response["status"] = "error";
				response["error"] = ex.what();
				cerr << ex.what() << endl;
				Logger::error(ex.what());
			}
			catch (const std::exception& ex) {
				cerr << ex.what() << endl;
				Logger::error(ex.what());
			}
			inst->send_response(response);
		});
		inst->m_msg.clear();
		memset(buffer_cast<char*>(inst->m_buf), 0, BUFLEN);
	}
	inst->do_read();
}

void ClientHandler::start()
{
	do_read();
}

void ClientHandler::do_read()
{
	HANDLER_LOCATION;
	// Avoid copy construct
	m_s.async_receive(m_buf, std::bind(&ClientHandler::handle_client,
		shared_from_this(),
		std::placeholders::_1,
		std::placeholders::_2));
}

void ClientHandler::send_response(const json response)
{
	HANDLER_LOCATION;
	try {
		std::string raw_msg = response.dump(2);
		m_s.send(buffer(raw_msg));
	}
	catch (const std::exception& ex) {
		cerr << ex.what() << endl;
		Logger::error(ex.what());
	}
}

ClientHandler::~ClientHandler()
{
	m_s.cancel();
	m_s.shutdown(socket_base::shutdown_type::shutdown_both);
	m_s.close();
}

bool operator==(const ClientHandler& lhs, const ClientHandler& rhs)
{
	return const_cast<ClientHandler&>(lhs).m_s.native_handle() ==
		const_cast<ClientHandler&>(rhs).m_s.native_handle() &&
		&lhs == &rhs;
}

std::size_t std::hash<ClientHandler::pointer_type>::operator()(const ClientHandler::pointer_type& key) const noexcept
{
	boost::asio::detail::socket_type h = key->m_s.native_handle();
	return std::hash<boost::asio::detail::socket_type>()(h) ^ reinterpret_cast<std::size_t>(key.get());
}
