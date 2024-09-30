#pragma once
#include "CommonIncludes.h"

class ClientHandler {
private:
	tcp::socket m_s;
	std::string msg;
	bool isHandled = false;
	char dummy[BUFLEN] = { 0 };
	mutable_buffer buf = buffer(dummy, BUFLEN);
public:
	ClientHandler(tcp::socket&& s);
	static void handle_client(ClientHandler* inst,
		const boost::system::error_code& error,
		size_t nBytesRead
	);
	~ClientHandler();
};