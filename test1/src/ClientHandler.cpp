#include "ClientHandler.h"
#include "Logger.h"
#include "TcpServer.h"

ClientHandler::ClientHandler(tcp::socket s, server_ptr_type serv)
	: m_s(std::move(s)),
	m_serv(serv)
{
	do_read();
}

ClientHandler::ClientHandler(io_context& ctx, server_ptr_type serv)
	: m_s(ctx),
	m_serv(serv)
{
	do_read();
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
			[&]() mutable { inst->m_serv.lock()->Disconnect(inst); });
		wcout << L"Client disconnected" << endl;
		Logger::log("Client disconnected");
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
		cout << "Handled client. Message: " << inst->m_msg << endl;
#endif // _DEBUG
		break;
	}
	inst->do_read();
}

void ClientHandler::start()
{
	do_read();
}

void ClientHandler::do_read()
{
	// Avoid copy construct
	m_s.async_receive(m_buf, std::bind(&ClientHandler::handle_client,
		shared_from_this(),
		std::placeholders::_1,
		std::placeholders::_2));
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
