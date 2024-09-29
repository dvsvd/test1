#pragma once

#include "CommonIncludes.h"
#include <shared_mutex>

class Storage : protected std::unordered_map<std::string, std::string>
{
private:
	std::shared_mutex _m;
public:
	Storage();
	Storage(std::initializer_list<value_type> list);
	const std::string& at(const std::string& key) const;
	std::pair<iterator, bool> insert_or_assign(const std::string& key, const std::string& value);
};