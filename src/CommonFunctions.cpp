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