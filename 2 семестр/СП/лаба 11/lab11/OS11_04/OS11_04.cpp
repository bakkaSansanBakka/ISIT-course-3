#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <string>
#include "../OS11_HTAPI/HT.h"
#pragma comment(lib, "E:\\3 курс\\2 семестр\\Системное программирование\\лаба 11\\lab11\\x64\\Debug\\OS11_HTAPI.lib")

int main(int argc, char** argv)
{
	HANDLE hf = NULL;
	try
	{
		HT::HTHANDLE* HT = HT::Open(L"E:\\storage.ht", false);
		if (HT == NULL) throw "Invalid handle";
		hf = CreateFile(L"E:\\3 курс\\2 семестр\\Системное программирование\\лаба 11\\update.log", GENERIC_WRITE | GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hf == INVALID_HANDLE_VALUE) throw "INVALID_HANDLE_VALUE";
		SetFilePointer(hf, NULL, NULL, FILE_END);

		std::string key;
		HT::Element* updating;
		HT::Element* getting;
		if (!WriteFile(hf, "START UPDATE\n", 13, NULL, NULL)) throw "WriteFile";
		for (int i = 1; i <= 9; i++)
		{
			if (HT->Addr == NULL) throw "HT IS CLOSEN";
			key = "key" + std::to_string(i);
			updating = new HT::Element(key.c_str(), key.length());
			std::cout << "updating..." << std::endl;
			if (!HT::Update(HT, updating, (void*)"payload", 8)) {
				if (!WriteFile(hf, "-- Error: Updating element\n", 27, NULL, NULL)) throw "WriteFile";
				std::cout << HT::GetLastError(HT) << std::endl;
			}
			else {
				if ((getting = HT::Get(HT, updating)) == NULL)
				{
					if (!WriteFile(hf, "-- Error: Getting element\n", 26, NULL, NULL)) throw "WriteFile";
					std::cout << HT::GetLastError(HT) << std::endl;
				}
				else {
					if (!WriteFile(hf, "-- Updating and getting element\n", 32, NULL, NULL)) throw "WriteFile";
					HT::print(getting);
				}
			}
			Sleep(2000);
		}
		if (!CloseHandle(hf)) throw "CloseHandle";
	}
	catch (const char* error)
	{
		std::cout << "-- Error: " << error << std::endl;
	}
}