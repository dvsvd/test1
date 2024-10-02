#pragma once
#include "CommonIncludes.h"
#include <memory> // for std::hash and weak_ptr

class TcpServer;

class ClientHandler : public std::enable_shared_from_this<ClientHandler> {
public:
	using pointer_type = std::shared_ptr<ClientHandler>;
private:
	friend struct std::hash<pointer_type>;
	friend bool operator==(const ClientHandler& lhs, const ClientHandler& rhs);
private:
	tcp::socket m_s;
	std::string m_msg;
	TcpServer& m_serv;
	bool isHandled = false;
	char dummy[BUFLEN] = { 0 };
	mutable_buffer m_buf = buffer(dummy, BUFLEN);
public:
	using pointer_type = std::shared_ptr<ClientHandler>;
	ClientHandler(tcp::socket s, TcpServer& serv);
	ClientHandler(io_context& ctx, TcpServer& serv);
	ClientHandler() = delete;
	ClientHandler(const ClientHandler&) = delete;
	ClientHandler(ClientHandler&&) noexcept;
	~ClientHandler();

	void start();
	inline tcp::socket& socket() { return m_s; }
private:
	static void handle_client(std::shared_ptr<ClientHandler>,
		const boost::system::error_code& error,
		size_t nBytesRead
	);
	void do_read();
};

template <>
struct std::hash<ClientHandler::pointer_type>
{
	std::size_t std::hash<ClientHandler::pointer_type>::operator()(const ClientHandler::pointer_type& key) const noexcept;
};
