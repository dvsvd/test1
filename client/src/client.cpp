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
#include "client.h"

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		cout << "Please provide JSON query filename" << endl;
		return 0;
	}
	try
	{
		io_context ioctx;
		tcp::socket tcp_socket(ioctx);
		char buf[4096U] = { 0 };
		std::ifstream f(argv[1], std::ios::binary | std::ios::in);
		auto fsize = fileSize(argv[1]);
		tcp_socket.connect(tcp::endpoint(address::from_string("127.0.0.1"), 3333));
		Localise();
		f.read(buf, fsize);
		tcp_socket.send(buffer(buf, fsize));
		cout << "Message sent!" << endl;
		memset(buf, 0, 4096U);
		tcp_socket.receive(buffer(buf, 4096U));
		// convert to json to test
		json response = buf;
		cout << "Incoming response:" << endl << buf << endl;
		tcp_socket.shutdown(socket_base::shutdown_both);
		tcp_socket.close();
	}
	catch (std::exception& ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}
