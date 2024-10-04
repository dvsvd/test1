#include "client.h"

int main(int argc, char** argv)
{
	try
	{
		io_context ioctx;
		tcp::socket tcp_socket(ioctx);
		char buf[4096U] = { 0 };
		const char fname[] = "write_query.json";
		std::ifstream f(fname, std::ios::binary | std::ios::in);
		auto fsize = fileSize(fname);
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
