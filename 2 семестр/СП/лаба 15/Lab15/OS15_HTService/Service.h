#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>

#define SERVICENAME L"Narkevich"
#define TRACEPATH "D:\\BSTU stuff\\6 семестр 3 курс\\СП\\Lab15\\Release\\Service.trace"

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
VOID WINAPI ServiceHandler(DWORD fdwControl);

void trace(const char* msg, int r = std::ofstream::app);