#include "Storage.h"

Storage::Storage() {}
Storage::Storage(std::initializer_list<value_type> list) :
	std::unordered_map<std::string, std::string>(list) {}

const std::string& Storage::at(const std::string& key) const
{
	std::shared_lock l(const_cast<std::shared_mutex&>(_m));
	return std::unordered_map<std::string, std::string>::at(key);
}
std::pair<Storage::iterator, bool> Storage::insert_or_assign(const std::string& key, const std::string& value)
{
	std::unique_lock l(_m);
	return std::unordered_map<std::string, std::string>::insert_or_assign(key, value);
}