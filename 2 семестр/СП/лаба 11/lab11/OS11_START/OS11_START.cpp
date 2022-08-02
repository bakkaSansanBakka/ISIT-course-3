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
		HT::HTHANDLE* HT = HT::Open(GetWC(argv[1]), true);
		if (HT == NULL) throw "Invalid handle";

		std::cout << "--- HT-Storage Started ---" << std::endl;
		std::cout << "filename: " << argv[1] << std::endl;
		std::cout << "snapshotinterval: " << HT->SecSnapshotInterval << std::endl;
		std::cout << "capacity: " << HT->Capacity << std::endl;
		std::cout << "maxkeylength: " << HT->MaxKeyLength << std::endl;
		std::cout << "maxdatalength: " << HT->MaxPayloadLength << std::endl;

		std::cout << std::endl << "Press any key to close HT: ";
		char a;
		std::cin >> a;
		if (!HT::Snap(HT)) throw HT::GetLastError(HT);
		if (!HT::Close(HT)) throw "Error close";
	}
	catch (const char* error) { std::cout << "-- Error: " << error << std::endl; }
}