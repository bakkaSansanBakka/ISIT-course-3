#pragma once
#include <objbase.h>
#include <iostream>
#include "INTERFACE.h"
#include <string>

class OS13:public IHashTable
{
public:
	OS13();
	~OS13();


	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);


	virtual HRESULT STDMETHODCALLTYPE Create   //  ������� HT             
	(
		//DWORD& address,
		HT::HTHANDLE** result,
		int	  Capacity,					   // ������� ���������
		int   SecSnapshotInterval,		   // ������������� ���������� � ���.
		int   MaxKeyLength,                // ������������ ������ �����
		int   MaxPayloadLength,            // ������������ ������ ������
		const wchar_t  FileName[512]          // ��� ����� 
	); 	// != NULL �������� ����������  

	virtual HRESULT STDMETHODCALLTYPE Open     //  ������� HT             
	(
		const wchar_t    FileName[512],         // ��� ����� 
		bool flag,
		HT::HTHANDLE**  result
	); 	// != NULL �������� ����������  

	virtual HRESULT STDMETHODCALLTYPE Snap         // ��������� Snapshot
	(
		HT::HTHANDLE**  hthandle           // ���������� HT (File, FileMapping)
	);


	virtual HRESULT STDMETHODCALLTYPE Close        // Snap � ������� HT  �  �������� HT::HTHANDLE
	(
		HT::HTHANDLE** hthandle
		//DWORD address     // ���������� HT (File, FileMapping)
	);	//  == TRUE �������� ����������   


	virtual HRESULT STDMETHODCALLTYPE Insert      // �������� ������� � ���������
	(
		HT::HTHANDLE**  hthandle,            // ���������� HT
		HT::Element* element              // �������
	);	//  == TRUE �������� ���������� 


	virtual HRESULT STDMETHODCALLTYPE Delete      // ������� ������� � ���������
	(
		HT::HTHANDLE**  hthandle,            // ���������� HT (����)
		HT::Element* element              // ������� 
	);	//  == TRUE �������� ���������� 

	virtual HRESULT STDMETHODCALLTYPE Get     //  ������ ������� � ���������
	(
		HT::Element& result,
		HT::HTHANDLE**  hthandle,            // ���������� HT
		HT::Element* element              // ������� 
	); 	//  != NULL �������� ���������� 


	virtual HRESULT STDMETHODCALLTYPE Update     //  ������� ������� � ���������
	(
		HT::HTHANDLE**  hthandle,            // ���������� HT
		HT::Element* oldelement,          // ������ ������� (����, ������ �����)
		void* newpayload,          // ����� ������  
		int             newpayloadlength     // ������ ����� ������
	); 	//  != NULL �������� ���������� 

	virtual HRESULT STDMETHODCALLTYPE GetLastErrorHt  // �������� ��������� � ��������� ������
	(
		HT::HTHANDLE**  ht                         // ���������� HT
	);

	virtual HRESULT STDMETHODCALLTYPE Print  // �������� ��������� � ��������� ������
	(
		char* key, int keyl, char* payload, int payloadl               // �������
	);

private:
	volatile ULONG m_Ref;
};
