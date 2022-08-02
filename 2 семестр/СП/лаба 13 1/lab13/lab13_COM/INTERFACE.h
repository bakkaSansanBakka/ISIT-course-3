#pragma once
#include <objbase.h>
#include "HT.h"
#include <string>

#define FNAME L"SDA.COM"
#define VINDX L"SDA.1"
#define PRGID L"SDA"

// {352CB0AE-1F06-4A76-AD11-D1B96F900115}
static GUID CLSID_CA =
{ 0x352cb0ae, 0x1f06, 0x4a76, { 0xad, 0x11, 0xd1, 0xb9, 0x6f, 0x90, 0x1, 0x15 } };


// {5533B146-DEE2-4647-AD2B-5E388DBDD7B4}
static GUID IID_IHashTable =
{ 0x5533b146, 0xdee2, 0x4647, { 0xad, 0x2b, 0x5e, 0x38, 0x8d, 0xbd, 0xd7, 0xb4 } };

interface IHashTable :IUnknown  
{
	virtual HRESULT STDMETHODCALLTYPE Create   //  ������� HT             
	(
		//DWORD& address,
		HT::HTHANDLE** result,
		int	  Capacity,					   // ������� ���������
		int   SecSnapshotInterval,		   // ������������� ���������� � ���.
		int   MaxKeyLength,                // ������������ ������ �����
		int   MaxPayloadLength,            // ������������ ������ ������
		const wchar_t  FileName[512]          // ��� ����� 
	) = 0; 	// != NULL �������� ����������  

	virtual HRESULT __stdcall Open     //  ������� HT             
	(
		const wchar_t    FileName[512],         // ��� ����� 
		bool flag,
		HT::HTHANDLE** result
	) = 0; 	// != NULL �������� ����������  

	virtual HRESULT __stdcall Snap         // ��������� Snapshot
	(
		HT::HTHANDLE** hthandle           // ���������� HT (File, FileMapping)
	) = 0;


	virtual HRESULT __stdcall Close        // Snap � ������� HT  �  �������� HTHANDLE
	(

		HT::HTHANDLE** hthandle       // ���������� HT (File, FileMapping)
	) = 0;	//  == TRUE �������� ����������   


	virtual HRESULT __stdcall Insert      // �������� ������� � ���������
	(
		HT::HTHANDLE** hthandle,            // ���������� HT
		HT::Element * element              // �������
	) = 0;	//  == TRUE �������� ���������� 


	virtual HRESULT __stdcall Delete      // ������� ������� � ���������
	(
		HT::HTHANDLE** hthandle,            // ���������� HT (����)
		HT::Element * element              // ������� 
	) = 0;	//  == TRUE �������� ���������� 

	virtual HRESULT __stdcall Get     //  ������ ������� � ���������
	(
		HT::Element & result,
		HT::HTHANDLE** hthandle,            // ���������� HT
		HT::Element * element              // ������� 
	) = 0; 	//  != NULL �������� ���������� 


	virtual HRESULT __stdcall Update     //  ������� ������� � ���������
	(
		HT::HTHANDLE** hthandle,            // ���������� HT
		HT::Element * oldelement,          // ������ ������� (����, ������ �����)
		void* newpayload,          // ����� ������  
		int             newpayloadlength     // ������ ����� ������
	) = 0; 	//  != NULL �������� ���������� 

	virtual HRESULT __stdcall GetLastErrorHt  // �������� ��������� � ��������� ������
	(
		HT::HTHANDLE** ht                         // ���������� HT
	) = 0;

	virtual HRESULT __stdcall Print
	(
		char* key, int keyl, char* payload, int payloadl // �������
	) = 0; 	//  != NULL �������� ����������
};
