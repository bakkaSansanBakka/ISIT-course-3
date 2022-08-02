#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
using namespace std;

BOOL delRowFileTxt(LPWSTR FileName, DWORD row) {
	try {
		HANDLE file = CreateFile((L"%s", FileName),
			GENERIC_WRITE | GENERIC_READ,
			NULL,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (file == INVALID_HANDLE_VALUE) throw "open file failed\n";

		DWORD n = NULL;
		char buf[1024];
		char newBuf[1024];
		int rowCount = 1;
		int lenNewBuf = 0;

		ZeroMemory(buf, sizeof(buf));
		ZeroMemory(newBuf, sizeof(newBuf));

		BOOL b = ReadFile(
			file,
			&buf,
			1024,
			&n,
			NULL
		);
		if (b == 0) throw "read file is failed\n";

		CloseHandle(file);
		
		for (int i = 0; i < strlen(buf); i++) {
			if (rowCount != row) {
				newBuf[lenNewBuf] = buf[i];
				lenNewBuf++;
			}
			if (buf[i] == '\n') {
				rowCount++;
			}
			
		}
		
		BOOL deleteSucc = DeleteFile(L"E:\\3 курс\\2 семестр\\Системное программирование\\лаба 1\\OS09_01.txt");
		if (!deleteSucc) throw "delete file failed\n";
		else cout << "delete file successful\n";

		HANDLE newFile = CreateFile((L"%s", FileName),
			GENERIC_WRITE | GENERIC_READ,
			NULL,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (newFile == INVALID_HANDLE_VALUE) throw "create file failed\n";
		else cout << "create file successful\n";

		n = NULL;

		BOOL writeSucc = WriteFile(
			newFile,
			newBuf,
			1024,
			&n,
			NULL
		);

		if (!writeSucc) throw "write file failed\n";

		CloseHandle(newFile);
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

int main()
{
	const char* fileName = "E:\\3 курс\\2 семестр\\Системное программирование\\лаба 1\\OS09_01.txt";
	wchar_t wcTemp[128];

	MultiByteToWideChar(CP_ACP, 0, fileName, -1, wcTemp, 128);

	delRowFileTxt(wcTemp, 1);
	delRowFileTxt(wcTemp, 3);
	delRowFileTxt(wcTemp, 8);
	delRowFileTxt(wcTemp, 10);
	printFileTxt(wcTemp);

	return 0;
}