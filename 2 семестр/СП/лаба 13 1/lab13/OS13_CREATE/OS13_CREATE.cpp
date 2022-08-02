#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include "../OS13_COMlib/HTlib.h"
#pragma comment(lib, "E:\\3 курс\\2 семестр\\Системное программирование\\лаба 13 1\\lab13\\Release\\OS13_COMlib.lib")

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
		int capacity = 50;
		int secSnapshotInterval = 10;
		int maxKeyLength = 2000;
		int maxPayloadLength = 2000;
		const wchar_t* fileName = L"E:\\OS\\storage.ht";

		if (!HTlib::OpenCOM()) throw "OpenCOM error";
		HTlib::HTHANDLE* HT = HTlib::Create(capacity, secSnapshotInterval, maxKeyLength, maxPayloadLength, fileName);
		if (HT == NULL) throw "Invalid handle";

		std::cout << "--- HT-Storage Created ---" << std::endl;
		std::cout << "filename: " << fileName << std::endl;
		std::cout << "snapshotinterval: " << secSnapshotInterval << std::endl;
		std::cout << "capacity: " << capacity << std::endl;
		std::cout << "maxkeylength: " << maxKeyLength << std::endl;
		std::cout << "maxdatalength: " << maxPayloadLength << std::endl;

		if (!HTlib::Close(HT)) throw "Error close";
		if (!HTlib::CloseCOM()) throw "CloseCOM error";
	}
	catch (const char* error) { std::cout << "-- Error: " << error << std::endl; }
}