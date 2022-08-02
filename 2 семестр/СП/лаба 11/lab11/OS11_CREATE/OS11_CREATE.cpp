#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include "../OS11_HTAPI/HT.h"
#pragma comment(lib, "E:\\3 курс\\2 семестр\\Системное программирование\\лаба 11\\lab11\\x64\\Debug\\OS11_HTAPI.lib")

const wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	size_t outSize;
	mbstowcs_s(&outSize, wc, cSize, c, cSize - 1);
	return wc;
}

int main(int argc, char** argv)
{
	try
	{
		HT::HTHANDLE* HT = HT::Create(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), GetWC(argv[5]));
		if (HT == NULL) throw "Invalid handle";

		std::cout << "--- HT-Storage Created ---" << std::endl;
		std::cout << "capacity: " << argv[1] << std::endl;
		std::cout << "snapshotinterval: " << argv[2] << std::endl;
		std::cout << "maxkeylength: " << argv[3] << std::endl;
		std::cout << "maxdatalength: " << argv[4] << std::endl;
		std::cout << "filename: " << argv[5] << std::endl;

		if (!HT::Close(HT)) throw "Error close";
	}
	catch (const char* error) { std::cout << "-- Error: " << error << std::endl; }
}