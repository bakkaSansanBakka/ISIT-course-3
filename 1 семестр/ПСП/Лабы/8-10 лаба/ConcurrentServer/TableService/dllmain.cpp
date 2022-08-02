// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Windows.h"
#include "DefineTableService.h"
#include "PrototypeService.h"

BEGIN_TABLESERVICE
	{"ECHO",EchoServer},
	{"TIME", TimeServer},
	{ "RAND", RandServer}
END_TABLESERVICE;


extern "C" __declspec(dllexport) HANDLE  SSS(char* id, LPVOID prm)
{
    HANDLE rc = NULL;
    int  i = 0;
    while (i < SIZETS && strcmp(TABLESERVICE_ID(i), id) != 0)i++;
    if (i < SIZETS)
        rc = CreateThread(NULL, NULL,
            TABLESERVICE_FN(i), prm, NULL, NULL);
    return rc;
};

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    return TRUE;
}

