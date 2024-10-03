// test1.cpp: определяет точку входа для приложения.
//

#include "test1.h"
#include "Logger.h"
#include "Storage.h"
#include "TcpServer.h"
#include "ClientHandler.h"
#include "JsonValidator.h"
#include <utility>

std::unordered_map<std::string, JsonValidator> LoadSchemas() noexcept;

Storage g_storage {
	std::make_pair("key1", "value1"),
	std::make_pair("key2", "value2"),
	std::make_pair("key3", "value3"),
};

extern const std::unordered_map<std::string, JsonValidator> g_validators = LoadSchemas();

/*
*	TODO:
*	2) JSON PARSE
*	3) SEND RESPONSE TO CLIENT
*	ADDITIONAL:
*	4) NETWORK ERRORS TRY-CATCH
*/

std::unordered_map<std::string, JsonValidator> LoadSchemas() noexcept
{
	char buf[4096U] = { 0 };
	const char fname[] = "schema_read.json";
	const char fname2[] = "schema_write.json";
	json read_schema, write_schema;
	try {
		std::ifstream f(fname, std::ios::binary | std::ios::in);
		std::ifstream f2(fname2, std::ios::binary | std::ios::in);
		auto fsize = fileSize(fname);
		auto fsize2 = fileSize(fname2);
		f.read(buf, fsize);
		read_schema = json::parse(std::string(buf));
		memset(buf, 0, 4096U);
		f2.read(buf, fsize2);
		write_schema = json::parse(std::string(buf));
	}
	catch (const std::exception& ex) {
		cerr << ex.what() << endl;
		Logger::error(ex.what());
		exit(1);
	}
	return std::unordered_map<std::string, JsonValidator> {
		std::make_pair("read", std::move(read_schema)),
			std::make_pair("write", std::move(write_schema))};
}

int main()
{
	try
	{
		Localise();
		std::shared_ptr<TcpServer> Serv = TcpServer::Create(3333, 25, std::thread::hardware_concurrency());
		Serv->Run();
	}
	catch (std::exception& ex)
	{
		cerr << ex.what() << endl;
		Logger::error(ex.what());
		return 1;
	}
}
