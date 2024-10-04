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
#include <unordered_set>
#include <unordered_map>

class JsonValidator
{
private:
	json m_schema;
	// Map of JSON keys and their required value types
	std::unordered_map<json::string_t, json::value_t> m_map;
public:
	JsonValidator() = default;
	JsonValidator(const JsonValidator&) = default;
	JsonValidator(JsonValidator&&) = default;
	JsonValidator(const json& schema);
	JsonValidator(const std::string& raw_schema);
	~JsonValidator() = default;

	inline void set_schema(const json& new_schema) { m_schema = new_schema; initialize_map(); }
	bool validate(const json& data) const;
private:
	void initialize_map();
};
