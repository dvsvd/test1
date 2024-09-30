#include "ClientHandler.h"
#include "Logger.h"

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
		wcout << L"Client disconnected" << endl;
		Logger::log("Client disconnected");
		break;
	case BUFLEN:
		inst->msg += buffer_cast<char*>(inst->buf);
		memset(buffer_cast<char*>(inst->buf), 0, BUFLEN);
		inst->isHandled = inst->m_s.available() == 0;
		break;
	default:
		inst->msg += buffer_cast<char*>(inst->buf);
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