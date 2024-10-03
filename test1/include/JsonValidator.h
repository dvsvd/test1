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
