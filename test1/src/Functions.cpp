/*
Copyright 2024 D. Kochetov (github.com/dvsvd)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
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
