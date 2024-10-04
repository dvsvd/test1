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
