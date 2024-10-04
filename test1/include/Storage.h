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

	size_t size() { return std::unordered_map<std::string, std::string>::size(); }
	const_iterator begin() const { return std::unordered_map<std::string, std::string>::begin(); }
	const_iterator cbegin() const { return std::unordered_map<std::string, std::string>::cbegin(); }
	const_iterator end() const { return std::unordered_map<std::string, std::string>::end(); }
	const_iterator cend() const { return std::unordered_map<std::string, std::string>::cend(); }
};