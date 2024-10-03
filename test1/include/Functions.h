#pragma once

#include "test1.h"
#include "Storage.h"

namespace Operations
{
	json ReadData(const json& request);
	json WriteData(const json& request);

	const std::unordered_map<std::string,
		std::function<json(const json&)>> map
	{
		std::make_pair("read", ReadData),
		std::make_pair("write", WriteData)
	};
}

namespace Functions
{
	// From https://ru.stackoverflow.com/a/484001
	// FNV-1a hash, 32-bit 
	inline constexpr std::uint32_t fnv1a(const char* str, std::uint32_t hash = 2166136261UL) {
		return *str ? fnv1a(str + 1, (hash ^ *str) * 16777619ULL) : hash;
	}
};
