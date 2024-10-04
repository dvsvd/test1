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

#define HANDLER_LOCATION \
  BOOST_ASIO_HANDLER_LOCATION((__FILE__, __LINE__, __func__))

using json = nlohmann::json;
using namespace boost::asio;
using namespace boost::asio::ip;

using std::string;
using std::wstring;
using std::cin;
using std::cout;
using std::cerr;
using std::wcin;
using std::wcout;
using std::wcerr;
using std::endl;
using uint = unsigned int;

inline constexpr size_t BUFLEN = 256U;