#include "client.h"

uint64_t fileSize(const char* name);

int main(int argc, char** argv)
{
	try
	{
		io_context ioctx;
		tcp::socket tcp_socket(ioctx);
		char buf[4096U] = { 0 };
		const char fname[] = "query.json";
		std::ifstream f(fname, std::ios::binary | std::ios::in);
		auto fsize = fileSize(fname);
		tcp_socket.connect(tcp::endpoint(address::from_string("127.0.0.1"), 3333));
		Localise();
		f.read(buf, fsize);
		tcp_socket.send(buffer(buf, fsize));
		cout << "Message sent!" << endl;
	}
	catch (std::exception& ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}

uint64_t fileSize(const char* name)
{
	std::ifstream f(name, std::ios::ate | std::ios::binary);
	return static_cast<uint64_t>(f.tellg());
}