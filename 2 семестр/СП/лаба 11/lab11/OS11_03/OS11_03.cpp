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
		hf = CreateFile(L"E:\\3 курс\\2 семестр\\Системное программирование\\лаба 11\\delete.log", GENERIC_WRITE | GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hf == INVALID_HANDLE_VALUE) throw "INVALID_HANDLE_VALUE";
		SetFilePointer(hf, NULL, NULL, FILE_END);

		std::string key;
		HT::Element* deleting;
		if (!WriteFile(hf, "START DELETE\n", 13, NULL, NULL)) throw "WriteFile";
		for (int i = 1; i <= 9; i++)
		{
			if (HT->Addr == NULL) throw "HT IS CLOSEN";
			key = "key" + std::to_string(i);
			deleting = new HT::Element(key.c_str(), key.length());
			std::cout << "deleting..." << std::endl;
			if (!HT::Delete(HT, deleting))
			{
				if (!WriteFile(hf, "-- Error: Deleting element\n", 27, NULL, NULL)) throw "WriteFile";
				std::cout << "--Error: " << HT::GetLastError(HT) << std::endl;
			}
			else if (!WriteFile(hf, "-- Deleting element\n", 20, NULL, NULL)) throw "WriteFile";
			Sleep(5000);
		}
		if (!CloseHandle(hf)) throw "CloseHandle";
	}
	catch (const char* error)
	{
		std::cout << "-- Error: " << error << std::endl;
	}
}