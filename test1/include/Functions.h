#pragma once

#include "test1.h"
#include "Storage.h"

namespace Operations
{
	json ReadData(const std::string& key, std::string& value);
	json WriteData(const std::string& key, const std::string& value);

	const std::map<std::string,
		std::function<json(const std::string& key, std::string& value)>> map
	{
		std::make_pair("read", ReadData),
		std::make_pair("write", WriteData)
	};
}

namespace Functions
{
	bool ValidationProc(int depth, json::parse_event_t event, json& parsed);
	//bool ValidateJSON(const json& doc, const json& schema)
	//{
	//	//TODO here
	//	return true;
	//}
	bool isRuChar(char c);
	void ValidateString(std::string& s);
	std::string FormPacket(const std::string& s);
	void Thread2Work(tcp::socket& tcp_socket);
	void recv_handler(
		const boost::system::error_code& error, // Result of operation.
		std::size_t bytes_transferred // Number of bytes received.
	);
};