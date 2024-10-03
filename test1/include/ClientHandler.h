#pragma once
#include "CommonIncludes.h"
#include <memory> // for std::hash and weak_ptr

class TcpServer;

class ClientHandler : public std::enable_shared_from_this<ClientHandler> {
public:
	using pointer_type = std::shared_ptr<ClientHandler>;
	using server_ptr_type = std::weak_ptr<TcpServer>;
private:
	friend struct std::hash<pointer_type>;
	friend bool operator==(const ClientHandler& lhs, const ClientHandler& rhs);
private:
	tcp::socket m_s;
	std::string m_msg;
	server_ptr_type m_serv;
	bool isHandled = false;
	char dummy[BUFLEN] = { 0 };
	mutable_buffer m_buf = buffer(dummy, BUFLEN);
public:
	using pointer_type = std::shared_ptr<ClientHandler>;
	ClientHandler(tcp::socket s, server_ptr_type serv);
	ClientHandler(io_context& ctx, server_ptr_type serv);
	ClientHandler() = delete;
	ClientHandler(const ClientHandler&) = delete;
	ClientHandler(ClientHandler&&) noexcept;
	~ClientHandler();

	void start();
	inline tcp::socket& socket() { return m_s; }
private:
	static void handle_client(pointer_type,
		const boost::system::error_code& error,
		size_t nBytesRead
	);
	void do_read();
	void send_response(const json response);
};

template <>
struct std::hash<ClientHandler::pointer_type>
{
	std::size_t std::hash<ClientHandler::pointer_type>::operator()(const ClientHandler::pointer_type& key) const noexcept;
};
