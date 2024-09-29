#include "Functions.h"
#include "Logger.h"
#include <exception>

extern Storage storage;
extern thread_local std::string msg;

json Operations::ReadData(const std::string& key, std::string& value)
{
	json response;
	try
	{
		//const_cast<std::string&>(value) = storage.at(key);
		value = storage.at(key);
		response["status"] = "ok";
		response["value"] = value;
	}
	catch (std::out_of_range& ex)
	{
		Logger::error(ex.what());
		response["status"] = "error";
		response["error"] = "No record for provided key found";
	}
	catch (std::exception& ex)
	{
		Logger::error(ex.what());
		response["status"] = "error";
		response["error"] = ex.what();
	}
	return response;
}

json Operations::WriteData(const std::string& key, const std::string& value)
{
	json response;
	try
	{
		storage.insert_or_assign(key, value);
		response["status"] = "ok";
	}
	catch (std::exception& ex)
	{
		Logger::error(ex.what());
		response["status"] = "error";
		response["error"] = ex.what();
	}
	return response;
}

bool Functions::ValidationProc(int depth, json::parse_event_t event, json& parsed)
{
	bool ret = false;
	return ret;
}

void Functions::recv_handler(
	const boost::system::error_code& error,
	size_t nBytesRead)
{
	switch (nBytesRead)
	{
	case 0: // Disconnect
		wcout << L"Client disconnected" << endl;
		Logger::log("Client disconnected");
		return;
	case BUFLEN:
		msg += buffer_cast<char*>(buf);
		memset(buffer_cast<char*>(buf), 0, BUFLEN);
		continue;
	default:
		msg += buffer_cast<char*>(buf);
		break;
	}
}
