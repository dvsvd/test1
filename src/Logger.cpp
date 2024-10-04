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
#include "Logger.h"

Logger::Logger() : ofs("Logfile.log", std::ios::out | std::ios::app | std::ios::ate)
{
#ifndef WIN32
	setenv("TZ", "/usr/share/zoneinfo/America/Los_Angeles", 1); // POSIX-specific
#endif // !WIN32
}

void Logger::log(const char* str)
{
	time_t now = time(0);
	tm* stime = localtime(&now);
	_self->ofs << '['
		<< std::put_time(stime, "%c %Z")
		<< "]: "
		<< str
		<< endl;
}

void Logger::log(const string& str)
{
	log(str.c_str());
}

void Logger::error(const char* str)
{
	static const string e("ERROR: ");
	log(e + str);
}
void Logger::error(const string& str)
{

}

Logger::~Logger()
{
	delete _self;
	_self = nullptr;
}

Logger* Logger::_self = new Logger();