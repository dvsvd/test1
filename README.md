![Build](https://github.com/dvsvd/test1/actions/workflows/c-cpp.yml/badge.svg)

Test assignment for Diginext application.

# REQUIREMENTS
- CMake (ver. 3.14 or higher)
- Boost (ver. 1.79.0 or higher)

# BUILD
To build application, run "cmake -D BOOST_ROOT=/path/to/boost/location -G "Your Generator" /path/to/project/root/folder",
and then build it with your generator.

# SERVER MANUAL
Server application has these optional command line arguments:
* -port: port to listen on (default: 3333)
* -maxclients: unused
* -concurrency: number of threads for server to use (default: std::thread::hardware_concurrency() - 1)
* -backlog: acceptor's backlog (default: boost::asio::ip::tcp::acceptor::max_listen_connections).

The server also accepts these console commands:
* exit: gracefully shutdown the application
* get_storage: print data storage to std::cout.

# CLIENT
Client application is provided to test the server's work.
It connects to 127.0.0.1:3333.
It accepts one positional argument: query file in JSON format.
JSON requests must match schemas located in [test1](test1/).
Schemas specify the JSON requst format in the form of "request_key_name" : "mapped_value_type".
