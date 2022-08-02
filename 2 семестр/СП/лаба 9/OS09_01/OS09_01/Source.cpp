#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <filesystem>
#include <windows.h>
#include <tchar.h>
#include <string.h>
#include <psapi.h>
#include <strsafe.h>
using namespace std;

bool PrintFileInfo(LPWSTR FileName) {
	try {
		HANDLE file = CreateFile((L"%s", FileName), 
			GENERIC_WRITE | GENERIC_READ, 
			NULL,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (file == INVALID_HANDLE_VALUE) {
			throw "open file failed";
		}
		
		char* fn = (char*)malloc(100);
		wcstombs(fn, FileName, 100);

		LPBY_HANDLE_FILE_INFORMATION fileInfo = new _BY_HANDLE_FILE_INFORMATION();
		SYSTEMTIME stCreate, stUpdate, stCreateLP, stUpdateLP;
		if (!GetFileInformationByHandle(file, fileInfo)) throw "GetInformationByHandle is faild";
		if (!FileTimeToSystemTime(&fileInfo->ftCreationTime, &stCreate)) throw "FileTimeToSystemTime is faild";
		if (!FileTimeToSystemTime(&fileInfo->ftLastWriteTime, &stUpdate)) throw "FileTimeToSystemTime is faild";
		SystemTimeToTzSpecificLocalTime(NULL, &stCreate, &stCreateLP);
		SystemTimeToTzSpecificLocalTime(NULL, &stUpdate, &stUpdateLP);


		cout << "File name: " << fn << endl;
		if (GetFileType(file) == 1) {
			cout << "File type: disk file" << endl;
		}
		else
			cout << "Filetype function failed or file type is unknown" << endl;
		cout << "File size: " << GetFileSize(file, NULL) << " bytes" << endl;
		cout << "Creation date and time: "
			<< stCreateLP.wDay << "."
			<< stCreateLP.wMonth << "."
			<< stCreateLP.wYear << " "
			<< stCreateLP.wHour << ":"
			<< stCreateLP.wMinute << ":"
			<< stCreateLP.wSecond << endl;
		cout << "Last update date and time: "
			<< stUpdateLP.wDay << "."
			<< stUpdateLP.wMonth << "."
			<< stUpdateLP.wYear << " "
			<< stUpdateLP.wHour << ":"
			<< stUpdateLP.wMinute << ":"
			<< stUpdateLP.wSecond << endl;

		CloseHandle(file);

	}
	catch (const char* error_message) {
		cout << "Error: " << error_message << endl;

		return false;
	}
	
	return true;
}

bool printFileTxt(LPWSTR FileName) {
	try {
		HANDLE file = CreateFile((L"%s", FileName),
			GENERIC_WRITE | GENERIC_READ,
			NULL,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (file == INVALID_HANDLE_VALUE) throw "open file failed";

		DWORD n = NULL;
		char buf[1024];

		ZeroMemory(buf, sizeof(buf));
		BOOL b = ReadFile(
			file,
			&buf,
			1024,
			&n,
			NULL
		);
		if (!b) throw "read file failed";
		else cout << "File contents: \n" << buf << endl;

		CloseHandle(file);
	}
	catch (const char* error_message) {
		cout << "Error: " << error_message << endl;

		return false;
	}
	return true;
}

int main() {
	setlocale(LC_CTYPE, "Russian");

	const char* fileName = "E:\\3 курс\\2 семестр\\Системное программирование\\лаба 1\\OS09_01.txt";
	wchar_t wcTemp[128];

	MultiByteToWideChar(CP_ACP, 0, fileName, -1, wcTemp, 128);

	PrintFileInfo(wcTemp);
	printFileTxt(wcTemp);

	return 0;
}