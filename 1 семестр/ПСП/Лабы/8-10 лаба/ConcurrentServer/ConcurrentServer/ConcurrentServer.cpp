#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>

#include "ConcurrentFunctions.h"
#include "TalkersCommand.h"
#include "ErrorHandler.h"
#include "WinSock2.h"
#include "Contact.h"
#include "ConcurrentServer.h"
#include "Timetable.h"
#pragma comment(lib, "WS2_32.lib")

#define AS_SQUIRT 10

typedef list<Contact> ListContact;

using namespace std;

HANDLE hAcceptServer, hConsolePipe, hGarbageCleaner, hDispatchServer, hResponseServer, hMailSlot;

u_short Port;
char dllName[50];
char pipeName[50];
char serverName[50];
u_short responsePort;

int squirt = 0;

ListContact contacts = {};

//WinSock
WSADATA wsaData;
SOCKET serverSocket;
SOCKADDR_IN server;

//DLL
volatile HMODULE st;

//Supports
time_t t;
struct tm* tt;

//CriticalSection
CRITICAL_SECTION csListContact;

//StatisitcVariables
LONG ConnectionNumbers = 0;
LONG DenialNumbers = 0;
LONG SuccessNumbers = 0;
LONG ActiveNumbers = 0;

HANDLE acceptEvent = CreateEvent(NULL, true, false, L"ClientAccept");

//TimeTable
int SecondsToCheckEmail = 60;
Timetable EchoTimetable{ "ECHO" };
Timetable TimeTimetable{ "TIME" };
Timetable RandTimetable{ "RAND" };


volatile TalkersCommand cmd;

int main(int argc, char* argv[])
{

	switch (argc)
	{
	case 1:
		Port = 2000;
		strcpy_s(dllName, "TableService.dll");
		strcpy_s(pipeName, "ConsolePipe");
		strcpy_s(serverName, "ConcurrentServer");
		responsePort = 2005;
		break;
	case 2:
		Port = atoi(argv[1]);
		break;
	case 3:
		Port = atoi(argv[1]);
		strcpy_s(dllName, argv[2]);
		break;
	case 4:
		Port = atoi(argv[1]);
		strcpy_s(dllName, argv[2]);
		strcpy_s(pipeName, argv[3]);
		break;
	case 5:
		Port = atoi(argv[1]);
		strcpy_s(dllName, argv[2]);
		strcpy_s(pipeName, argv[3]);
		strcpy_s(serverName, argv[4]);
		break;
	case 6:
		Port = atoi(argv[1]);
		strcpy_s(dllName, argv[2]);
		strcpy_s(pipeName, argv[3]);
		strcpy_s(serverName, argv[4]);
		responsePort = atoi(argv[5]);
		break;
	default:
		cout << "Wrong parameters count.... Exit";
		return 0;
	}

	cout << "Server port: " << Port << endl;
	cout << "Server name: " << serverName << endl;
	cout << "Server pipe name: " << pipeName << endl;

	cmd = TalkersCommand::START;
	st = LoadLibraryA(dllName);




	InitializeCriticalSection(&csListContact);

	hAcceptServer = CreateThread(NULL, NULL, AcceptServer, (LPVOID)&cmd, NULL, NULL);
	hDispatchServer = CreateThread(NULL, NULL, DispatchServer, (LPVOID)&cmd, NULL, NULL);
	hGarbageCleaner = CreateThread(NULL, NULL, GarbageCleaner, (LPVOID)&cmd, NULL, NULL);
	hConsolePipe = CreateThread(NULL, NULL, ConsolePipe, (LPVOID)&cmd, NULL, NULL);
	hResponseServer = CreateThread(NULL, NULL, ResponseServer, (LPVOID)&cmd, NULL, NULL);

	WaitForSingleObject(hAcceptServer, INFINITE);
	CloseHandle(hAcceptServer);
	WaitForSingleObject(hDispatchServer, INFINITE);
	CloseHandle(hDispatchServer);
	WaitForSingleObject(hGarbageCleaner, INFINITE);
	CloseHandle(hGarbageCleaner);
	WaitForSingleObject(hConsolePipe, INFINITE);
	CloseHandle(hConsolePipe);
	WaitForSingleObject(hResponseServer, INFINITE);
	CloseHandle(hResponseServer);

	DeleteCriticalSection(&csListContact);
	FreeLibrary(st);

	cout << "~~~~~~~~~~~~SERVER SHUTDOWN~~~~~~~~~~~~" << endl;
	return 0;
}

#pragma region Timer
void WINAPI ASWTimer(LPVOID contact, DWORD timerLowValue, DWORD timerHighValue)
{
	UNREFERENCED_PARAMETER(timerLowValue);
	UNREFERENCED_PARAMETER(timerHighValue);

	Contact* cont = (Contact*)&contact;

	cont->SetSt(Contact::TIMEOUT);
	char timedout[50] = "TIMEDOUT";
	time(&t);
	tt = localtime(&t);

	/*TerminateThread(cont->hThread, 0);*/

	cout << "Client timed out " << endl;
}
#pragma endregion

#pragma region AsyncFunctions
void CALLBACK ASStartMessage(Contact* contact)
{
	time(&t);
	tt = localtime(&t);

	cout << "Starting serving client (" << inet_ntoa(contact->params.sin_addr) << ":" << htons(contact->params.sin_port) << ") at " << contact->serverName << " " << asctime(tt);
}
void CALLBACK ASFinishMessage(Contact* contact)
{
	time(&t);
	tt = localtime(&t);

	cout << "Finished serving client " << asctime(tt);

	CancelWaitableTimer(contact->hTimer);
	contact->SetSt(Contact::FINISH);
}
#pragma endregion

#pragma region ResponseServer
bool GetRequestFromClient(SOCKET serverSocket, string name, SOCKADDR_IN* from)
{
	int addressLength = sizeof(*from);
	char buffer[1024] = {};

	int recvResult = recvfrom(serverSocket, buffer, sizeof(buffer), NULL, (sockaddr*)from, &addressLength);
	if (recvResult == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		throw SetErrorMsgText("RecvFrom RESPONSE:", WSAGetLastError());

	if (string(buffer)._Equal(name))
		return true;

	SOCKADDR_IN tempFrom = {};
	from = &tempFrom;
	return false;
}

bool PutAnswerToClient(SOCKET serverSocket, string serverInfo, SOCKADDR_IN* to)
{
	if ((sendto(serverSocket, serverInfo.c_str(), strlen(serverInfo.c_str()), NULL, (sockaddr*)to, sizeof(*to)) == SOCKET_ERROR))
		throw SetErrorMsgText("SendTo:", WSAGetLastError());
}

void SetupResponseSocket(SOCKET* sock, SOCKADDR_IN responseAddress)
{
	if ((*sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
		throw SetErrorMsgText("Socket:", WSAGetLastError());

	u_long nonblk;
	if ((ioctlsocket(*sock, FIONBIO, &(nonblk = 1))) == SOCKET_ERROR)
		throw SetErrorMsgText("ioctlsocket: ", WSAGetLastError());

	if (bind(*sock, (LPSOCKADDR)&responseAddress, sizeof(responseAddress)) == SOCKET_ERROR)
		throw SetErrorMsgText("Bind:", WSAGetLastError());
}

DWORD WINAPI ResponseServer(LPVOID prm)
{
	try
	{
		SOCKET sock;
		SOCKADDR_IN responseAddress{};
		SOCKADDR_IN client{};

		responseAddress.sin_family = AF_INET;
		responseAddress.sin_port = htons(responsePort);
		responseAddress.sin_addr.s_addr = INADDR_ANY;

		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup:", WSAGetLastError());

		SetupResponseSocket(&sock, responseAddress);

		u_long nonblk;
		if ((ioctlsocket(sock, FIONBIO, &(nonblk = 1))) == SOCKET_ERROR)
			throw SetErrorMsgText("ioctlsocket: ", WSAGetLastError());

		while (true)
		{
			Sleep(100);
			if (squirt == 0)
				continue;

			if (GetRequestFromClient(sock, serverName, &client))
			{
				string serverInfo = to_string(ntohs(server.sin_port));

				PutAnswerToClient(sock, serverInfo, &client);
				memset(&client, 0, sizeof(client));

				if (closesocket(sock) == SOCKET_ERROR)
					throw SetErrorMsgText("Close Socket:", WSAGetLastError());

				SetupResponseSocket(&sock, responseAddress);
			}

			if (cmd == EXIT)
				break;
		}
	}
	catch (string message)
	{
		cout << message << endl;
	}
}

#pragma endregion

#pragma region ConsolePipe
TalkersCommand GetCmdFromStr(char* str)
{
	if (strcmp(str, "start") == 0)
		return START;
	if (strcmp(str, "stop") == 0)
		return STOP;
	if (strcmp(str, "exit") == 0)
		return EXIT;
	if (strcmp(str, "statistics") == 0)
		return STATISTICS;
	if (strcmp(str, "wait") == 0)
		return WAIT;
	if (strcmp(str, "shutdown") == 0)
		return SHUTDOWN;

	return NOCMD;
}


DWORD WINAPI ConsolePipe(LPVOID prm)
{
	DWORD rc = 0;

	size_t cSize = strlen(pipeName) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, pipeName, cSize);
	SECURITY_ATTRIBUTES SecurityAttributes;
	SECURITY_DESCRIPTOR SecurityDescriptor;

	BOOL fSuccess = InitializeSecurityDescriptor(
		&SecurityDescriptor,
		SECURITY_DESCRIPTOR_REVISION);

	if (!fSuccess) {
		throw new string("InitializeSecurityDescriptor():");
	}

	fSuccess = SetSecurityDescriptorDacl(
		&SecurityDescriptor,
		TRUE,
		NULL,
		FALSE);

	if (!fSuccess) {
		throw new string("SetSecurityDescriptorDacl():");
	}

	SecurityAttributes.nLength = sizeof(SecurityAttributes);
	SecurityAttributes.lpSecurityDescriptor = &SecurityDescriptor;
	SecurityAttributes.bInheritHandle = FALSE;

	wstring name = L"\\\\.\\pipe\\";
	name += wc;

	HANDLE hPipe;
	if ((hPipe = CreateNamedPipe(name.c_str(),
		PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_WAIT | PIPE_READMODE_MESSAGE,
		1, NULL, NULL, INFINITE, &SecurityAttributes)) == INVALID_HANDLE_VALUE)
		throw SetErrorMsgText("Create Pipe Error: ", GetLastError());

	while (true)
	{
		if (cmd == EXIT || cmd == SHUTDOWN)
			break;

		if (!ConnectNamedPipe(hPipe, NULL))
			throw SetErrorMsgText("Connect Error: ", GetLastError());

		unsigned long bytesRead;
		unsigned long bytesWriten;
		char nocmd[50] = "nocmd";

		while (true)
		{

			char buffer[1024]{};
			if (!ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL))
				throw SetErrorMsgText("Read Error: ", GetLastError());

			TalkersCommand recvCmd = GetCmdFromStr(buffer);

			if (strcmp(buffer, "quit") == 0)
			{
				if (!DisconnectNamedPipe(hPipe))
					throw SetErrorMsgText("Disconnect Error: ", GetLastError());
				break;
			}

			if (recvCmd == NOCMD)
			{
				if (!WriteFile(hPipe, nocmd, sizeof(nocmd), &bytesWriten, NULL))
					throw SetErrorMsgText("Write Error: ", GetLastError());

				continue;
			}

			if (recvCmd == STATISTICS)
			{
				string stat = "\n~~~~~~~~~~~~STATISTICS~~~~~~~~~~~~\n";
				stat += "Connections count: " + to_string(ConnectionNumbers) + "\n";
				stat += "Denied connections count: " + to_string(DenialNumbers) + "\n";
				stat += "Successful connections count: " + to_string(SuccessNumbers) + "\n";
				stat += "Active connections count: " + to_string(ActiveNumbers) + "\n";

				if (!WriteFile(hPipe, stat.c_str(), strlen(stat.c_str()), &bytesWriten, NULL))
					throw SetErrorMsgText("Write Error: ", GetLastError());

				continue;
			}

			if (!WriteFile(hPipe, buffer, sizeof(buffer), &bytesWriten, NULL))
				throw SetErrorMsgText("Write Error: ", GetLastError());

			cmd = recvCmd;

			cout << "~~~~~~~~~~~~COMMAND SWITCHED TO " << buffer << "~~~~~~~~~~~~" << endl;

			if (cmd == EXIT || cmd == SHUTDOWN)
			{
				if (!DisconnectNamedPipe(hPipe))
					throw SetErrorMsgText("Disconnect Error: ", GetLastError());
				break;
			}
		}

	}

	ExitThread(rc);
}

#pragma endregion

#pragma region GarbageCleaner
DWORD WINAPI GarbageCleaner(LPVOID prm)
{
	DWORD rc = 0;

	while (true)
	{
		Sleep(5000);
		if (!contacts.empty())
		{
			for (auto contact = contacts.begin(); contact != contacts.end(); ++contact)
			{
				if (contact->sthread == Contact::ABORT || contact->sthread == Contact::TIMEOUT || contact->sthread == Contact::FINISH)
				{
					EnterCriticalSection(&csListContact);
					contacts.remove(*contact);
					LeaveCriticalSection(&csListContact);
					break;
				}
				if (contacts.empty())
					break;
			}
		}

		if (cmd == EXIT)
		{
			for (auto contact = contacts.begin(); contact != contacts.end(); ++contact)
			{

				TerminateThread(contact->hAcceptServer, 0);

				EnterCriticalSection(&csListContact);
				contacts.remove(*contact);
				LeaveCriticalSection(&csListContact);

				if (contacts.empty())
					break;
			}
			break;
		}
	}

	ExitThread(rc);
}

#pragma endregion

#pragma region DispatchServer
DWORD WINAPI DispatchServer(LPVOID prm)
{
	DWORD rc = 0;

	char echo[50] = "ECHO";
	char time[50] = "TIME";
	char rand[50] = "RAND";
	char chosenService[50] = {};
	char serverName[50] = {};
	DWORD result;

	string response;

	while (true)
	{
		result = WaitForSingleObject(OpenEvent(EVENT_ALL_ACCESS, TRUE, L"ClientAccept"), INFINITE);
		if (result == WAIT_OBJECT_0)
		{
			for (auto contact = contacts.begin(); contact != contacts.end(); ++contact)
			{

				if (contact->type == Contact::CONTACT)
				{
					u_long nonblk;
					if ((ioctlsocket(contact->socket, FIONBIO, &(nonblk = 0))) == SOCKET_ERROR)
						throw SetErrorMsgText("ioctlsocket: ", WSAGetLastError());

					int result = recv(contact->socket, contact->msg, sizeof(contact->msg), NULL);

					if (result == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
						throw SetErrorMsgText("Recv DISPATCH:", WSAGetLastError());


					if (strcmp(contact->msg, echo) == 0)
					{
						if (EchoTimetable.IsInTimePeriod())
						{
							strcpy_s(chosenService, echo);
							strcpy_s(serverName, "ECHO");
						}
						else
						{
							response = CreateMaintainMessage(echo, &EchoTimetable);

							if (send(contact->socket, response.c_str(), strlen(response.c_str()), NULL) == SOCKET_ERROR)
								throw SetErrorMsgText("Send DISPATCH:", WSAGetLastError());

							contact->sthread = Contact::FINISH;
							continue;

						}
					}
					else if (strcmp(contact->msg, time) == 0)
					{
						if (TimeTimetable.IsInTimePeriod())
						{
							strcpy_s(chosenService, time);
							strcpy_s(serverName, "TIME");
						}
						else
						{
							response = CreateMaintainMessage(time, &TimeTimetable);

							if (send(contact->socket, response.c_str(), strlen(response.c_str()), NULL) == SOCKET_ERROR)
								throw SetErrorMsgText("Send DISPATCH:", WSAGetLastError());

							contact->sthread = Contact::FINISH;
							continue;

						}
					}
					else if (strcmp(contact->msg, rand) == 0)
					{
						if (RandTimetable.IsInTimePeriod())
						{
							strcpy_s(chosenService, rand);
							strcpy_s(serverName, "RAND");
						}
						else
						{
							response = CreateMaintainMessage(rand, &RandTimetable);

							if (send(contact->socket, response.c_str(), strlen(response.c_str()), NULL) == SOCKET_ERROR)
								throw SetErrorMsgText("Send DISPATCH:", WSAGetLastError());

							contact->sthread = Contact::FINISH;
							continue;
						}
					}
					else
					{
						char error[20] = "Error Inquiry";
						if (send(contact->socket, error, sizeof(error), NULL) == SOCKET_ERROR)
							throw SetErrorMsgText("Send: ", WSAGetLastError());

						if (closesocket(contact->socket) == SOCKET_ERROR)
							throw SetErrorMsgText("Close Socket:", WSAGetLastError());

						contact->sthread = Contact::ABORT;
						contact->type = Contact::EMPTY;

						break;
					}

					HANDLE(*ts)(char*, LPVOID) = (HANDLE(*)(char*, LPVOID))GetProcAddress(st, "SSS");

					contact->hThread = ts(chosenService, (LPVOID) & (*contact));
					contact->hAcceptServer = hAcceptServer;
					contact->pStartMessage = PAPCFUNC(ASStartMessage);
					contact->pFinishMessage = PAPCFUNC(ASFinishMessage);
					contact->pActiveNumbers = &ActiveNumbers;
					contact->pDenialNumbers = &DenialNumbers;
					contact->pSuccessNumbers = &SuccessNumbers;

					strcpy_s(contact->serverName, serverName);

					contact->SetSt(Contact::WORK);

					if (cmd == EXIT)
					{
						break;
					}
				}
			}
		}

		if (cmd == EXIT)
		{
			break;
		}

	}
	ExitThread(rc);
}

string CreateMaintainMessage(string serverName, Timetable* timetable)
{
	string startTimeHours = to_string(timetable->StartTime.tm_hour);
	string startTimeMin = to_string(timetable->StartTime.tm_min);
	string endTimeHours = to_string(timetable->EndTime.tm_hour);
	string endTimeMin = to_string(timetable->EndTime.tm_min);

	if (startTimeHours.length() < 2)
		startTimeHours = "0" + startTimeHours;
	if (startTimeMin.length() < 2)
		startTimeMin = "0" + startTimeMin;
	if (endTimeHours.length() < 2)
		endTimeHours = "0" + endTimeHours;
	if (endTimeMin.length() < 2)
		endTimeMin = "0" + endTimeMin;


	string response = serverName + " is not available now. WT ("
		+ startTimeHours + ":" + startTimeMin + "-"
		+ endTimeHours + ":" + endTimeMin + ")";

	return response;
}

#pragma endregion

#pragma region AcceptServer
DWORD WINAPI AcceptServer(LPVOID prm)
{
	DWORD rc = 0;
	char buffer[256] = {};
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup (AS):", WSAGetLastError());

		if ((serverSocket = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket (AS):", WSAGetLastError());

		server.sin_family = AF_INET;
		server.sin_port = htons(Port);
		server.sin_addr.s_addr = INADDR_ANY;

		if (bind(serverSocket, (LPSOCKADDR)&server, sizeof(server)) == SOCKET_ERROR)
			throw SetErrorMsgText("Bind (AS):", WSAGetLastError());

		if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
			throw SetErrorMsgText("Listen: ", WSAGetLastError());

		//////////////////////////

		u_long nonblk;
		if ((ioctlsocket(serverSocket, FIONBIO, &(nonblk = 1))) == SOCKET_ERROR)
			throw SetErrorMsgText("ioctlsocket: ", WSAGetLastError());

		CommandCycle(*(TalkersCommand*)prm);


		//////////////////////////

		if (closesocket(serverSocket) == SOCKET_ERROR)
			throw SetErrorMsgText("Close Socket:", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());
	}
	catch (string ErrorMsg)
	{
		cout << ErrorMsg << " with code " << WSAGetLastError();
		ExitThread(rc);
	}
}

void CommandCycle(TalkersCommand& cmd)
{

	while (cmd != EXIT)
	{
		switch (cmd)
		{
		case START:
			cmd = GETCOMMAND;
			squirt = AS_SQUIRT;
			SetThreadPriority(hResponseServer, THREAD_PRIORITY_ABOVE_NORMAL);
			break;
		case STOP:
			cmd = GETCOMMAND;
			squirt = 0;
			SetThreadPriority(hResponseServer, THREAD_PRIORITY_IDLE);
			break;
		case WAIT:

			while (true)
			{
				squirt = 0;
				if (contacts.empty())
				{
					squirt = AS_SQUIRT;
					cmd = GETCOMMAND;
					break;
				}
			}
			break;
		case SHUTDOWN:
			while (true)
			{
				squirt = 0;
				if (contacts.empty())
				{
					cmd = EXIT;
					break;
				}
			}
			break;
		}

		if (AcceptCycle(squirt))
		{
			cmd = GETCOMMAND;
		}
		else
			SleepEx(0, true);

	}

	PulseEvent(acceptEvent);
	TerminateThread(hResponseServer, 0);
}

bool AcceptCycle(int squirt)
{
	bool rc = false;

	Contact contact(Contact::ACCEPT);

	while (squirt-- > 0 && rc == false)
	{

		if ((contact.socket = accept(serverSocket, (sockaddr*)&contact.params, &contact.lParams)) == INVALID_SOCKET)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
				throw SetErrorMsgText("Accept: ", WSAGetLastError());
		}
		else
		{
			contact.type = Contact::CONTACT;
			rc = true;

			EnterCriticalSection(&csListContact);
			contacts.push_front(contact);
			LeaveCriticalSection(&csListContact);
			SetEvent(acceptEvent);
			Sleep(100);
			ResetEvent(acceptEvent);

			InterlockedIncrement(&ConnectionNumbers);
		}
	}

	return rc;
}

#pragma endregion

