#pragma once
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <algorithm>

#define CREATE_HTFILE_ERROR "Create HTFile error";
#define CREATE_FILEMAPPING_ERROR "Create FileMapping error";
#define MAPPING_VIEW_ERROR "Mapping view failed";

#define MATHLIBRARY_API __declspec(dllexport)

namespace HT    // HT API
{
	// API HT - ����������� ��������� ��� ������� � ��-��������� 
	//          ��-��������� ������������� ��� �������� ������ � �� � ������� ����/��������
	//          ���������������� (�����������) ������ �������������� � ������� snapshot-���������� 
	//          Create - �������  � ������� HT-��������� ��� �������������   
	//          Open   - ������� HT-��������� ��� �������������
	//          Insert - ������� ������� ������
	//          Delete - ������� ������� ������    
	//          Get    - ������  ������� ������
	//          Update - �������� ������� ������
	//          Snap   - �������� snapshot
	//          Close  - ��������� Snap � ������� HT-��������� ��� �������������
	//          GetLastError - �������� ��������� � ��������� ������

	MATHLIBRARY_API struct HTHANDLE    // ���� ���������� HT
	{
		MATHLIBRARY_API HTHANDLE();
		MATHLIBRARY_API HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t FileName[512]);
		int     Capacity;               // ������� ��������� � ���������� ��������� 
		int     SecSnapshotInterval;    // ������������� ���������� � ���. 
		int     MaxKeyLength;           // ������������ ����� �����
		int     MaxPayloadLength;       // ������������ ����� ������
		char    FileName[512];          // ��� ����� 
		HANDLE  File;                   // File HANDLE != 0, ���� ���� ������
		HANDLE  FileMapping;            // Mapping File HANDLE != 0, ���� mapping ������  
		LPVOID  Addr;                   // Addr != NULL, ���� mapview ��������  
		char    LastErrorMessage[512];  // ��������� �� ��������� ������ ��� 0x00  
		time_t  lastsnaptime;           // ���� ���������� snap'a (time())  

		HANDLE Mutex;
		int N;//������� ����������
		HANDLE SnapshotThread;
	};

	extern "C" MATHLIBRARY_API struct Element   // ������� 
	{
		MATHLIBRARY_API Element();
		MATHLIBRARY_API Element(const void* key, int keylength);                                             // for Get
		MATHLIBRARY_API Element(const void* key, int keylength,  const void* payload, int  payloadlength);    // for Insert
		MATHLIBRARY_API Element(Element* oldelement,  const void* newpayload, int  newpayloadlength);         // for update
		void* key;                 // �������� ����� 
		int             keylength;           // ������ �����
		void* payload;             // ������ 
		int             payloadlength;       // ������ ������
	};

	extern "C" MATHLIBRARY_API HTHANDLE* Create   //  ������� HT             
	(
		int	  Capacity,					   // ������� ���������
		int   SecSnapshotInterval,		   // ������������� ���������� � ���.
		int   MaxKeyLength,                // ������������ ������ �����
		int   MaxPayloadLength,            // ������������ ������ ������
		const wchar_t  FileName[512]          // ��� ����� 
	); 	// != NULL �������� ����������  

	extern "C" MATHLIBRARY_API HTHANDLE* Open     //  ������� HT             
	(
		const wchar_t    FileName[512],         // ��� ����� 
		bool flag
	); 	// != NULL �������� ����������  

	extern "C" MATHLIBRARY_API BOOL Snap         // ��������� Snapshot
	(
		HTHANDLE* hthandle           // ���������� HT (File, FileMapping)
	);


	extern "C" MATHLIBRARY_API BOOL Close        // Snap � ������� HT  �  �������� HTHANDLE
	(
		HTHANDLE* hthandle           // ���������� HT (File, FileMapping)
	);	//  == TRUE �������� ����������   


	extern "C" MATHLIBRARY_API BOOL Insert      // �������� ������� � ���������
	(
		 HTHANDLE* hthandle,            // ���������� HT
		 Element* element              // �������
	);	//  == TRUE �������� ���������� 


	extern "C" MATHLIBRARY_API BOOL Delete      // ������� ������� � ���������
	(
		 HTHANDLE* hthandle,            // ���������� HT (����)
		 Element* element              // ������� 
	);	//  == TRUE �������� ���������� 

	extern "C" MATHLIBRARY_API Element* Get     //  ������ ������� � ���������
	(
		 HTHANDLE* hthandle,            // ���������� HT
		 Element* element              // ������� 
	); 	//  != NULL �������� ���������� 


	extern "C" MATHLIBRARY_API BOOL Update     //  ������� ������� � ���������
	(
		HTHANDLE* hthandle,            // ���������� HT
		Element* oldelement,          // ������ ������� (����, ������ �����)
		void* newpayload,          // ����� ������  
		int             newpayloadlength     // ������ ����� ������
	); 	//  != NULL �������� ���������� 

	extern "C" MATHLIBRARY_API char* GetLastErrorHt  // �������� ��������� � ��������� ������
	(
		HTHANDLE* ht                         // ���������� HT
	);

	extern "C" MATHLIBRARY_API BOOL print                               // ����������� ������� 
	(
		char* key, int keyl, char* payload, int payloadl         // ������� 
	);


};
