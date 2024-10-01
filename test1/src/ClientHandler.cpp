#include "ClientHandler.h"
#include "Logger.h"
#include "TcpServer.h"

ClientHandler::ClientHandler()
	: m_s(io_context())
{

}

ClientHandler::ClientHandler(tcp::socket&& s)
	: m_s(std::move(s))
{
	// Avoid copy construct
	m_s.async_receive(buf, std::bind(&ClientHandler::handle_client,
		this,
		std::placeholders::_1,
		std::placeholders::_2));
}

void ClientHandler::handle_client (ClientHandler* inst,
	const boost::system::error_code& error,
	size_t nBytesRead
	)
{
	switch (nBytesRead)
	{
	case 0: // Disconnect
		post(inst->m_s.get_executor(), std::bind(&TcpServer::Disconnect, *inst));
		wcout << L"Client disconnected" << endl;
		Logger::log("Client disconnected");
		break;
	case BUFLEN:
		inst->m_msg += buffer_cast<char*>(inst->buf);
		memset(buffer_cast<char*>(inst->buf), 0, BUFLEN);
		inst->isHandled = inst->m_s.available() == 0;
		break;
	default:
		inst->m_msg += buffer_cast<char*>(inst->buf);
		inst->isHandled = true;
		break;
	}
}

ClientHandler::~ClientHandler()
{
	m_s.cancel();
	m_s.shutdown(socket_base::shutdown_type::shutdown_both);
	m_s.close();
}

bool ClientHandler::operator==(const ClientHandler& other) const
{
	return const_cast<ClientHandler&>(*this).m_s.native_handle() ==
		const_cast<ClientHandler&>(other).m_s.native_handle() &&
		this == &other;
}

std::size_t std::hash<ClientHandler>::operator()(const ClientHandler& key) const noexcept
{
	boost::asio::detail::socket_type h = const_cast<ClientHandler&>(key).m_s.native_handle();
	return std::hash<boost::asio::detail::socket_type>()(h) ^ reinterpret_cast<std::size_t>(&key);
}