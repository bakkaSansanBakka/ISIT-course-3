#pragma once
#include <list>
#include "WinSock2.h"
#pragma comment(lib, "WS2_32.lib")

using namespace std;

struct Contact
{
	enum TE
	{
		EMPTY,
		ACCEPT,
		CONTACT
	} type;

	enum ST
	{
		WORK,
		ABORT,
		TIMEOUT,
		FINISH
	} sthread;

	SOCKET socket;
	SOCKADDR_IN params;
	int lParams;
	HANDLE hThread;
	HANDLE hTimer;
	HANDLE hAcceptServer;
	PAPCFUNC pStartMessage;
	PAPCFUNC pFinishMessage;

	LONG* pSuccessNumbers;
	LONG* pDenialNumbers;
	LONG* pActiveNumbers;


	char msg[256];
	char serverName[20];

	Contact(TE t = EMPTY, const char* srvName = "")
	{
		params = {};
		lParams = sizeof(SOCKADDR_IN);
		type = t;
		strcpy_s(serverName, srvName);
		memset(&msg, 0, sizeof(msg));
	}

	void SetSt(ST sth, const char* m = "")
	{
		sthread = sth;
		strcpy_s(msg, m);
	}

	bool operator == (const Contact& right) const
	{
		if (params.sin_family == right.params.sin_family && params.sin_port == right.params.sin_port && params.sin_addr.s_addr == right.params.sin_addr.s_addr)
			return  true;
		return false;
	}

};