#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Windows.h"
#include "Contact.h"
#include <iostream>
#include <string>
#include <ctime>
#include <WS2tcpip.h>

using namespace std;
struct Contact;
extern "C" __declspec(dllexport) HANDLE SSS(char* id, LPVOID prm);

std::string SetErrorMsgText(std::string message, int code);
std::string GetErrorMsgText(int code);

DWORD __stdcall EchoServer(LPVOID prm)
{
	Contact* contact = (Contact*)prm;

	try
	{
		QueueUserAPC(contact->pStartMessage, contact->hAcceptServer, (ULONG_PTR)contact);

		InterlockedIncrement(contact->pActiveNumbers);

		char hello[50] = "Echo server dispatched.";
		char sendbuffer[50]{};
		char receivebuffer[50]{};
		int result = 0;

		if (send(contact->socket, hello, sizeof(hello), NULL) == SOCKET_ERROR)
			throw SetErrorMsgText("Send: ", WSAGetLastError());


 		while (true)
		{
			if (contact->sthread == Contact::TIMEOUT)
				break;


			//strcpy_s(receivebuffer, "");
			//strcpy_s(sendbuffer, "");

			result = recv(contact->socket, receivebuffer, sizeof(receivebuffer), NULL);
			if (result == SOCKET_ERROR || WSAGetLastError() == WSAECONNRESET)
			{
				contact->sthread = Contact::ABORT;

				InterlockedIncrement(contact->pDenialNumbers);
				InterlockedDecrement(contact->pActiveNumbers);
				QueueUserAPC(contact->pFinishMessage, contact->hAcceptServer, (ULONG_PTR)contact);
				TerminateThread(GetCurrentThread(), 0);
			}
			if (result == SOCKET_ERROR)
				throw SetErrorMsgText("Recieve: ", WSAGetLastError());


			if (strcmp(receivebuffer, "exit") == 0)
				break;
			strcpy_s(sendbuffer, receivebuffer);

			if (send(contact->socket, sendbuffer, strlen(sendbuffer), NULL) == SOCKET_ERROR)
				return 0;

			if (contact->sthread == Contact::TIMEOUT)
			{
				InterlockedIncrement(contact->pDenialNumbers);
				InterlockedDecrement(contact->pActiveNumbers);
				QueueUserAPC(contact->pFinishMessage, contact->hAcceptServer, (ULONG_PTR)contact);
				TerminateThread(GetCurrentThread(), 0);
			}
		}

		InterlockedDecrement(contact->pActiveNumbers);
		InterlockedIncrement(contact->pSuccessNumbers);

		QueueUserAPC(contact->pFinishMessage, contact->hAcceptServer, (ULONG_PTR)contact);

		TerminateThread(GetCurrentThread(), 0);
	}
	catch (string Message)
	{
		cout << Message << endl;
	}
}

DWORD __stdcall TimeServer(LPVOID prm)
{
	Contact* contact = (Contact*)prm;

	try
	{
		QueueUserAPC(contact->pStartMessage, contact->hAcceptServer, (ULONG_PTR)contact);

		InterlockedIncrement(contact->pActiveNumbers);

		char hello[50] = "Time server dispatched.";
		string timeString = "";
		char receivebuffer[50]{};
		int result = 0;

		if (send(contact->socket, hello, sizeof(hello), NULL) == SOCKET_ERROR)
			throw SetErrorMsgText("Send: ", WSAGetLastError());


		while (true)
		{
			if (contact->sthread == Contact::TIMEOUT)
				break;

			result = recv(contact->socket, receivebuffer, sizeof(receivebuffer), NULL);

			if (result == SOCKET_ERROR || WSAGetLastError() == WSAECONNRESET)
			{
				contact->sthread = Contact::ABORT;

				InterlockedIncrement(contact->pDenialNumbers);
				InterlockedDecrement(contact->pActiveNumbers);
				QueueUserAPC(contact->pFinishMessage, contact->hAcceptServer, (ULONG_PTR)contact);
				TerminateThread(GetCurrentThread(), 0);
			}

			if (result == SOCKET_ERROR)
				throw SetErrorMsgText("Recieve: ", WSAGetLastError());


			if (strcmp(receivebuffer, "time") != 0)
				break;

			__time64_t long_time;
			_time64(&long_time);
			tm ltm;
			localtime_s(&ltm, &long_time);

			timeString = to_string(ltm.tm_mday) + "." + to_string(1 + ltm.tm_mon) + "." + to_string(1900 + ltm.tm_year) + "/"
				+ to_string(ltm.tm_hour) + ":" + to_string(ltm.tm_min) + ":" + to_string(ltm.tm_sec);

			if (send(contact->socket, timeString.c_str(), strlen(timeString.c_str()), NULL) == SOCKET_ERROR)
				TerminateThread(GetCurrentThread(), 0);

			if (contact->sthread == Contact::TIMEOUT)
			{
				InterlockedIncrement(contact->pDenialNumbers);
				InterlockedDecrement(contact->pActiveNumbers);
				QueueUserAPC(contact->pFinishMessage, contact->hAcceptServer, (ULONG_PTR)contact);
				TerminateThread(GetCurrentThread(), 0);
			}
		}

		InterlockedDecrement(contact->pActiveNumbers);
		InterlockedIncrement(contact->pSuccessNumbers);

		QueueUserAPC(contact->pFinishMessage, contact->hAcceptServer, (ULONG_PTR)contact);

		TerminateThread(GetCurrentThread(), 0);
	}
	catch (string Message)
	{
		cout << Message << endl;
	}
}

DWORD __stdcall RandServer(LPVOID prm)
{
	Contact* contact = (Contact*)prm;

	try
	{
		QueueUserAPC(contact->pStartMessage, contact->hAcceptServer, (ULONG_PTR)contact);

		InterlockedIncrement(contact->pActiveNumbers);

		char hello[50] = "Rand server dispatched.";
		string randString = "";
		char receivebuffer[50]{};
		int result = 0;

		if (send(contact->socket, hello, sizeof(hello), NULL) == SOCKET_ERROR)
			throw SetErrorMsgText("Send: ", WSAGetLastError());


		while (true)
		{
			if (contact->sthread == Contact::TIMEOUT)
				break;

			result = recv(contact->socket, receivebuffer, sizeof(receivebuffer), NULL);

			if (result == SOCKET_ERROR || WSAGetLastError() == WSAECONNRESET)
			{
				contact->sthread = Contact::ABORT;

				InterlockedIncrement(contact->pDenialNumbers);
				InterlockedDecrement(contact->pActiveNumbers);
				QueueUserAPC(contact->pFinishMessage, contact->hAcceptServer, (ULONG_PTR)contact);
				TerminateThread(GetCurrentThread(), 0);
			}

			if (result == SOCKET_ERROR)
				throw SetErrorMsgText("Recieve: ", WSAGetLastError());


			if (strcmp(receivebuffer, "rand") != 0)
			{
				break;
			}

			randString = to_string(rand());

			if (send(contact->socket, randString.c_str(), strlen(randString.c_str()), NULL) == SOCKET_ERROR)
				TerminateThread(GetCurrentThread(), 0);

			if (contact->sthread == Contact::TIMEOUT)
			{
				InterlockedIncrement(contact->pDenialNumbers);
				InterlockedDecrement(contact->pActiveNumbers);
				QueueUserAPC(contact->pFinishMessage, contact->hAcceptServer, (ULONG_PTR)contact);
				TerminateThread(GetCurrentThread(), 0);
			}
		}

		InterlockedDecrement(contact->pActiveNumbers);
		InterlockedIncrement(contact->pSuccessNumbers);

		QueueUserAPC(contact->pFinishMessage, contact->hAcceptServer, (ULONG_PTR)contact);

		TerminateThread(GetCurrentThread(), 0);
	}
	catch (string Message)
	{
		cout << Message << endl;
	}
}



std::string SetErrorMsgText(std::string message, int code)
{
	return message + GetErrorMsgText(code);
}

std::string GetErrorMsgText(int code)
{
	std::string message;
	switch (code)
	{
	case WSAEINTR:
		message = "WSAEINTR";
		break;
	case WSAEACCES:
		message = "WSAEACCESS";
		break;
	case WSAEFAULT:
		message = "WSAEFAULT";
		break;
	case WSAEINVAL:
		message = "WSAEINVAL";
		break;
	case WSAEMFILE:
		message = "WSAEMFILE";
		break;
	case WSAEWOULDBLOCK:
		message = "WSAEWOULDBLOCK";
		break;
	case WSAEALREADY:
		message = "WSAEALREADY";
		break;
	case WSAENOTSOCK:
		message = "WSAENOTSOCK";
		break;
	case WSAEDESTADDRREQ:
		message = "WSAEDESTADDRREQ";
		break;
	case WSAEPROTOTYPE:
		message = "WSAEPROTOTYPE";
		break;
	case WSAENOPROTOOPT:
		message = "WSAENOPROTOOPT";
		break;
	case WSAEPROTONOSUPPORT:
		message = "WSAEPROTONOSUPPORT";
		break;
	case WSAESOCKTNOSUPPORT:
		message = "WSAESOCKTNOSUPPORT";
		break;
	case WSAEOPNOTSUPP:
		message = "WSAEOPNOTSUPP";
		break;
	case WSAEPFNOSUPPORT:
		message = "WSAEPFNOSUPPORT";
		break;
	case WSAEAFNOSUPPORT:
		message = "WSAEAFNOSUPPORT";
		break;
	case WSAEADDRINUSE:
		message = "WSAEADDRINUSE";
		break;
	case WSAEADDRNOTAVAIL:
		message = "WSAEADDRNOTAVAIL";
		break;
	case WSAENETDOWN:
		message = "WSAENETDOWN";
		break;
	case WSAENETUNREACH:
		message = "WSAENETUNREACH";
		break;
	case WSAENETRESET:
		message = "WSAENETRESET";
		break;
	case WSAECONNABORTED:
		message = "WSAECONNABORTED";
		break;
	case WSAECONNRESET:
		message = "WSAECONNRESET";
		break;
	case WSAENOBUFS:
		message = "WSAENOBUFS";
		break;
	case WSAEISCONN:
		message = "WSAEISCONN";
		break;
	case WSAENOTCONN:
		message = "WSAENOTCONN";
		break;
	case WSAESHUTDOWN:
		message = "WSAESHUTDOWN";
		break;
	case WSAEINPROGRESS:
		message = "WSAEINPROGRESS";
		break;
	case WSAEMSGSIZE:
		message = "WSAEMSGSIZE";
		break;
	case WSAETIMEDOUT:
		message = "WSAETIMEDOUT";
		break;
	case WSAECONNREFUSED:
		message = "WSAECONNREFUSED";
		break;
	case WSAEHOSTDOWN:
		message = "WSAEHOSTDOWN";
		break;
	case WSAEHOSTUNREACH:
		message = "WSAEHOSTUNREACH";
		break;
	case WSAEPROCLIM:
		message = "WSAEPROCLIM";
		break;
	case WSAVERNOTSUPPORTED:
		message = "WSAVERNOTSUPPORTED";
		break;
	case WSANOTINITIALISED:
		message = "WSANOTINITIALISED";
		break;
	case WSAEDISCON:
		message = "WSAEDISCON";
		break;
	case WSATYPE_NOT_FOUND:
		message = "WSATYPE_NOT_FOUND";
		break;
	case WSAHOST_NOT_FOUND:
		message = "WSAHOST_NOT_FOUND";
		break;
	case WSATRY_AGAIN:
		message = "WSATRY_AGAIN";
		break;
	case WSANO_RECOVERY:
		message = "WSANO_RECOVERY";
		break;
	case WSANO_DATA:
		message = "WSANO_DATA";
		break;
	case WSA_INVALID_HANDLE:
		message = "WSA_INVALID_HANDLE";
		break;
	case WSA_INVALID_PARAMETER:
		message = "WSA_INVALID_PARAMETER";
		break;
	case WSA_IO_INCOMPLETE:
		message = "WSA_IO_INCOMPLETE";
		break;
	case WSA_IO_PENDING:
		message = "WSA_IO_PENDING";
		break;
	case WSA_NOT_ENOUGH_MEMORY:
		message = "WSA_NOT_ENOUGH_MEMORY";
		break;
	case WSA_OPERATION_ABORTED:
		message = "WSA_OPERATION_ABORTED";
		break;
	case WSAEINVALIDPROCTABLE:
		message = "WSAINVALIDPROCTABLE";
		break;
	case WSAEINVALIDPROVIDER:
		message = "WSAEINVALIDPROVIDER";
		break;
	case WSAEPROVIDERFAILEDINIT:
		message = "WSAPROVIDERFAILEDINIT";
		break;
	case WSASYSCALLFAILURE:
		message = "WSASYSCALLFAILURE";
		break;
	case WSASYSNOTREADY:
		message = "WSASYSNOTREADY";
		break;
	default:
		message = "~Error~";
		break;
	};
	return message;
}
