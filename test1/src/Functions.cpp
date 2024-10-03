#include "Functions.h"
#include "Logger.h"
#include "ClientHandler.h"
#include "JsonValidator.h"
#include <exception>

extern Storage g_storage;

extern const std::unordered_map<std::string, JsonValidator> g_validators;

json Operations::ReadData(const json& request)
{
	json response;
	try
	{
		response["value"] = g_storage.at(request["key"]);
		response["status"] = "ok";
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

json Operations::WriteData(const json& request)
{
	json response;
	try
	{
		g_storage.insert_or_assign(request["key"], request["value"]);
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
