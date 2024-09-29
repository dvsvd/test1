#include "ClientHandler.h"
#include "Logger.h"

ClientHandler::ClientHandler(tcp::socket& s)
	: m_s(s)
{

}
void ClientHandler::operator() (
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
		msg += buffer_cast<char*>(buf);
		memset(buffer_cast<char*>(buf), 0, BUFLEN);
		isHandled = m_s.available() == 0;
		break;
	default:
		msg += buffer_cast<char*>(buf);
		isHandled = true;
		break;
	}
}