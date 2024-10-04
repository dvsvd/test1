// test1.cpp: определяет точку входа для приложения.
//

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
#include "test1.h"
#include "Logger.h"
#include "Storage.h"
#include "TcpServer.h"
#include "ClientHandler.h"
#include "JsonValidator.h"
#include <utility>

std::unordered_map<std::string, JsonValidator> LoadSchemas() noexcept;
unsigned short strtous(const char* str);

Storage g_storage {
	std::make_pair("key1", "value1"),
	std::make_pair("key2", "value2"),
	std::make_pair("key3", "value3"),
};

extern const std::unordered_map<std::string, JsonValidator> g_validators = LoadSchemas();

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

unsigned short strtous(const char* str)
{
	unsigned long ret = std::strtoul(str, nullptr, 10);
	if (errno == ERANGE)
		throw std::range_error(std::string("std::strtoul failed in ") + __FUNCTION__);
	if (ret > USHRT_MAX)
		throw std::range_error("value is out of USHORT range");
	return (unsigned short)ret;
}

int main(int argc, char** argv)
{
	unsigned short port = 3333;
	size_t maxclients = 25;
	int backlog = tcp::acceptor::max_listen_connections;
	size_t concurrency = std::thread::hardware_concurrency() - 1;
	std::string cmd;
	try
	{
		Localise();
		for (int i = 1; i < argc; i++)
		{

			if (argv[i][0] == '-') // check for an option marker
			{
				if (!strcmp((argv[i] + 1), "port"))
				{
					port = strtous(argv[++i]);
				}
				else if (!strcmp((argv[i] + 1), "maxclients"))
				{
					maxclients = std::strtoul(argv[++i], nullptr, 10);
				}
				else if (!strcmp((argv[i] + 1), "backlog"))
				{
					backlog = std::strtol(argv[++i], nullptr, 10);
				}
				else if (!strcmp((argv[i] + 1), "concurrency"))
				{
					concurrency = std::strtol(argv[++i], nullptr, 10);
				}
			}
		}
		std::shared_ptr<TcpServer> Serv = TcpServer::Create(port, maxclients, concurrency, backlog);
		std::thread(&TcpServer::Run, Serv).detach();
		while (true)
		{
			cout << ">";
			std::getline(cin, cmd);
			cin.clear();
			cout.clear();
			fflush(stdin);
			if (cmd == "exit")
				break;
			else if (cmd == "get_storage")
			{
				for (const auto it : g_storage)
				{
					cout << it.first << " : " << it.second << endl;
				}
			}
		}
	}
	catch (const std::exception& ex)
	{
		cerr << ex.what() << endl;
		Logger::error(ex.what());
		return 1;
	}
}
