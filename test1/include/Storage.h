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