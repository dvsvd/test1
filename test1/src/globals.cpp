#include "globals.h"
#include "Storage.h"
#include <xutility>

Storage storage{
	std::make_pair("key1", "value1"),
	std::make_pair("key2", "value2"),
	std::make_pair("key3", "value3"),
};