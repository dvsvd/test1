#pragma once
#include "CommonIncludes.h"

class Logger
{
private:
	std::ofstream ofs;
	Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
protected:
	static Logger* _self;
public:
	static void log(const char* str);
	static void log(const string& str);
	static void error(const char* str);
	static void error(const string& str);
	~Logger();
};