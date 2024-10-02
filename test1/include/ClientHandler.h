#pragma once
#include "CommonIncludes.h"
#include <memory> // for std::hash and weak_ptr

class TcpServer;

class ClientHandler {
	friend struct std::hash<ClientHandler>;
	friend bool operator==(const ClientHandler& lhs, const ClientHandler& rhs);
private:
	tcp::socket m_s;
	std::string m_msg;
	TcpServer& m_serv;
	bool isHandled = false;
	char dummy[BUFLEN] = { 0 };
	mutable_buffer m_buf = buffer(dummy, BUFLEN);
public:
	ClientHandler(tcp::socket&& s, TcpServer& serv);
	ClientHandler() = delete;
	ClientHandler(const ClientHandler&) = delete;
	ClientHandler(ClientHandler&&) = default;
	~ClientHandler();

	static void handle_client(ClientHandler* inst,
		const boost::system::error_code& error,
		size_t nBytesRead
	);
};

template <>
struct std::hash<ClientHandler>
{
	std::size_t operator()(const ClientHandler& key) const noexcept;
};
