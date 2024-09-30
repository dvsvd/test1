#pragma once

#include <iostream>
#include <string>
#include <locale>
#include <unordered_map>
#include <utility>
#include <sstream>
#include <fstream>
#include <boost/asio.hpp>
#include <ctime>
#include <iomanip>
#include <nlohmann/json.hpp>
#ifdef WIN32
#include <Windows.h>
#endif // WIN32

using json = nlohmann::json;
using namespace boost::asio;
using namespace boost::asio::ip;

using std::string;
using std::wstring;
using std::cin;
using std::cout;
using std::wcin;
using std::wcout;
using std::endl;
using uint = unsigned int;

inline constexpr size_t BUFLEN = 256U;