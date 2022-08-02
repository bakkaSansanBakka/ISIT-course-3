#pragma once
#include <Windows.h>
#include <objbase.h>
#include <iostream>
#include <iomanip>
#include <string>

namespace HTlib    // HT API
{
	struct HTHANDLE    // ���� ���������� HT
	{
		HTHANDLE();
		HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t FileName[512]);
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

	struct Element   // ������� 
	{
		Element();
		Element(const void* key, int keylength);                                             // for Get
		Element(const void* key, int keylength, const void* payload, int  payloadlength);    // for Insert
		Element(Element* oldelement, const void* newpayload, int  newpayloadlength);         // for update
		void* key;                 // �������� ����� 
		int             keylength;           // ������ �����
		void* payload;             // ������ 
		int             payloadlength;       // ������ ������
	};

	bool OpenCOM();
	bool CloseCOM();

	HTlib::HTHANDLE* Create   //  ������� HT             
	(
		int	  Capacity,					   // ������� ���������
		int   SecSnapshotInterval,		   // ������������� ���������� � ���.
		int   MaxKeyLength,                // ������������ ������ �����
		int   MaxPayloadLength,            // ������������ ������ ������
		const wchar_t  FileName[512]          // ��� ����� 
	);

	HTlib::HTHANDLE* Open     //  ������� HT             
	(
		const wchar_t    FileName[512],         // ��� ����� 
		bool flag
	); 	// != NULL �������� ����������  

	BOOL Snap         // ��������� Snapshot
	(
		HTlib::HTHANDLE* hthandle           // ���������� HT (File, FileMapping)
	);


	BOOL Close        // Snap � ������� HT  �  �������� HT::HTHANDLE
	(
		HTlib::HTHANDLE* hthandle           // ���������� HT (File, FileMapping)
	);	//  == TRUE �������� ����������   


	BOOL Insert      // �������� ������� � ���������
	(
		HTlib::HTHANDLE* hthandle,            // ���������� HT
		HTlib::Element* element              // �������
	);	//  == TRUE �������� ���������� 


	BOOL Delete      // ������� ������� � ���������
	(
		HTlib::HTHANDLE* hthandle,            // ���������� HT (����)
		HTlib::Element* element              // ������� 
	);	//  == TRUE �������� ���������� 

	HTlib::Element* Get     //  ������ ������� � ���������
	(
		HTlib::HTHANDLE* hthandle,            // ���������� HT
		HTlib::Element* element              // ������� 
	); 	//  != NULL �������� ���������� 


	BOOL Update     //  ������� ������� � ���������
	(
		HTlib::HTHANDLE* hthandle,            // ���������� HT
		HTlib::Element* oldelement,          // ������ ������� (����, ������ �����)
		void* newpayload,          // ����� ������  
		int newpayloadlength     // ������ ����� ������
	); 	//  != NULL �������� ���������� 

	char* GetLastErrorHt  // �������� ��������� � ��������� ������
	(
		HTlib::HTHANDLE* ht                         // ���������� HT
	);

	BOOL Print // ����������� �������
	(
		char* key, int keyl, char* payload, int payloadl // �������
	);
};