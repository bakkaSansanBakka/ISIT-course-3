﻿#include <iostream>
#include <Windows.h>
#include <time.h>

void main()
{
	HANDLE hM;
	DWORD readBuf;
	time_t start;
	time_t stop;
	char buf[128];
	try
	{
		if ((hM = CreateMailslot(L"\\\\.\\mailslot\\Box", 500, MAILSLOT_WAIT_FOREVER, NULL)) == INVALID_HANDLE_VALUE)
			throw "CreateMailslotError";
		start = clock();
		while (true)
		{
			if (!ReadFile(hM, buf, sizeof(buf), &readBuf, NULL))
				throw "ReadFileError";
			if (strcmp(buf, "stop") == 0)
				break;
			std::cout << buf << std::endl;
		}
		stop = clock();
		std::cout << "Time passed: " << (stop - start) / CLOCKS_PER_SEC << std::endl;
		CloseHandle(hM);

	}
	catch (char* Error)
	{
		std::cout << Error << std::endl;
	}
}