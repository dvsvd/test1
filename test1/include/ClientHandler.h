#pragma once
#include "CommonIncludes.h"
#include <memory> // for std::hash

class ClientHandler {
	friend struct std::hash<ClientHandler>;
private:
	tcp::socket m_s;
	std::string m_msg;
	bool isHandled = false;
	char dummy[BUFLEN] = { 0 };
	mutable_buffer buf = buffer(dummy, BUFLEN);
public:
	ClientHandler();
	ClientHandler(tcp::socket&& s);
	ClientHandler(const ClientHandler&) = delete;
	ClientHandler(ClientHandler&&) = default;
	~ClientHandler();

	static void handle_client(ClientHandler* inst,
		const boost::system::error_code& error,
		size_t nBytesRead
	);

	bool operator==(const ClientHandler& other) const;
};

template <>
struct std::hash<ClientHandler>
{
	std::size_t operator()(const ClientHandler& key) const noexcept;
};