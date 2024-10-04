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
#include "CommonFunctions.h"

void Localise()
{
#ifdef _UNICODE
	setlocale(LC_ALL, ".utf8");
#ifdef WIN32
	SetConsoleCP(65001);
	SetConsoleOutputCP(65001);
#endif // WIN32
#else
	setlocale(LC_ALL, "Rus");
#ifdef WIN32
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
#endif // WIN32
#endif // _UNICODE
}

uint64_t fileSize(const char* name)
{
	std::ifstream f(name, std::ios::ate | std::ios::binary);
	return static_cast<uint64_t>(f.tellg());
}