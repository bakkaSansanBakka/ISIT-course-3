#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
using namespace std;

BOOL insRowFileTxt(LPWSTR FileName, const char* str, DWORD row) {	
	HANDLE file, newFile;

	try {
		file = CreateFile(FileName,
			GENERIC_WRITE | GENERIC_READ,
			NULL,
			NULL,
			OPEN_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL);

		if (file == INVALID_HANDLE_VALUE) throw "open file failed\n";
		else cout << "open file successful" << endl;

		DWORD n = NULL;

		if (row == -1) {
			SetFilePointer(file, 0, NULL, FILE_END);
			if (!WriteFile(file, "\n", 1, &n, NULL)) throw "write file failed";
			if (!WriteFile(file, str, strlen(str), &n, NULL)) throw "write file failed";
			CloseHandle(file);
		}
		else if (row == 0) {
			char buf[1024];
			char newBuf[1024];
			int lenNewBuf = 0;

			ZeroMemory(buf, sizeof(buf));
			ZeroMemory(newBuf, sizeof(newBuf));

			if (!ReadFile(file, &buf, 1024, &n, NULL)) throw "read file is failed\n";
			CloseHandle(file);
			
			for (int i = 0; i < strlen(str); i++) {
				newBuf[lenNewBuf] = str[i];
				lenNewBuf++;
			}
			newBuf[lenNewBuf] = '\n';
			lenNewBuf++;

			for (int i = 0; i < strlen(buf); i++) {
				newBuf[lenNewBuf] = buf[i];
				lenNewBuf++;
			}

			newFile = CreateFile(FileName,
				GENERIC_WRITE | GENERIC_READ,
				NULL,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

			if (newFile == INVALID_HANDLE_VALUE) throw "create file failed\n";
			else cout << "create file successful\n";

			if (!WriteFile(newFile, newBuf, strlen(newBuf), &n, NULL)) throw "write file failed\n";

			CloseHandle(newFile);
		}
		else {
			int rowCount = 1;
			int lenNewBuf = 0;
			char buf[1024];
			char newBuf[1024];

			ZeroMemory(buf, sizeof(buf));
			ZeroMemory(newBuf, sizeof(newBuf));

			if (!ReadFile(file, &buf, 1024, &n, NULL)) throw "read file failed";
			CloseHandle(file);

			for (int i = 0; i < strlen(buf); i++) {
				if (rowCount == row) {
					for (int j = 0; j < strlen(str); j++) {
						newBuf[lenNewBuf] = str[j];
						lenNewBuf++;
					}
					newBuf[lenNewBuf] = '\n';
					lenNewBuf++;
					rowCount++;
				}
				if (buf[i] == '\n') rowCount++;
				newBuf[lenNewBuf] = buf[i];
				lenNewBuf++;
			}

			newFile = CreateFile(FileName,
				GENERIC_WRITE | GENERIC_READ,
				NULL,
				NULL,
				CREATE_ALWAYS,
				FILE_ATTRIBUTE_NORMAL,
				NULL);

			if (newFile == INVALID_HANDLE_VALUE) throw "open file failed\n";
			else cout << "open file successful" << endl;

			if (!WriteFile(newFile, newBuf, strlen(newBuf), &n, NULL)) throw "write file failed";
			CloseHandle(newFile);
		}
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
    const wchar_t* fileName = L"E:\\3 курс\\2 семестр\\Системное программирование\\лаба 1\\OS09_01.txt";
    const char* str = "Potapeyko Polina";

    insRowFileTxt((LPWSTR)fileName, str, 0);
    insRowFileTxt((LPWSTR)fileName, str, -1);
    insRowFileTxt((LPWSTR)fileName, str, 5);
    insRowFileTxt((LPWSTR)fileName, str, 7);

	printFileTxt((LPWSTR)fileName);

	return 0;
}