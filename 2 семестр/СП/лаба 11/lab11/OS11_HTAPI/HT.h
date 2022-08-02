#pragma once
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <algorithm>

#define CREATE_HTFILE_ERROR "Create HTFile error";
#define CREATE_FILEMAPPING_ERROR "Create FileMapping error";
#define MAPPING_VIEW_ERROR "Mapping view failed";

namespace HT
{
	struct __declspec(dllexport) HTHANDLE
	{
		HTHANDLE();
		HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t FileName[512]);
		int     Capacity;
		int     SecSnapshotInterval;
		int     MaxKeyLength;
		int     MaxPayloadLength;
		char    FileName[512];
		HANDLE  File;
		HANDLE  FileMapping;
		LPVOID  Addr;
		char    LastErrorMessage[512];
		time_t  lastsnaptime;

		HANDLE Mutex;
		int N;
		HANDLE SnapshotThread;
	};

	struct __declspec(dllexport) Element
	{
		Element();
		Element(const void* key, int keylength);
		Element(const void* key, int keylength, const void* payload, int  payloadlength);
		Element(Element* oldelement, const void* newpayload, int  newpayloadlength);
		void* key;
		int keylength;
		void* payload;
		int payloadlength;
	};

	__declspec(dllexport) HTHANDLE* Create(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t  FileName[512]);
	__declspec(dllexport) HTHANDLE* Open(const wchar_t FileName[512], bool flag);
	__declspec(dllexport) BOOL Snap(HTHANDLE* hthandle);
	__declspec(dllexport) BOOL Close(HTHANDLE* hthandle);
	__declspec(dllexport) BOOL Insert(HTHANDLE* hthandle, Element* element);
	__declspec(dllexport) BOOL Delete(HTHANDLE* hthandle, Element* element);
	__declspec(dllexport) Element* Get(HTHANDLE* hthandle, Element* element);
	__declspec(dllexport) BOOL Update(HTHANDLE* hthandle, Element* oldelement, void* newpayload, int newpayloadlength);
	__declspec(dllexport) char* GetLastError(HTHANDLE* ht);
	__declspec(dllexport) void print(const Element* element);
};
