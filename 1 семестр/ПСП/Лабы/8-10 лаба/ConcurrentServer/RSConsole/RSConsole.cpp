#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
using namespace std;

string SetPipeError(string message, int code);
string GetErrorMsgText(int code);
string Read(HANDLE pipe);
bool Write(HANDLE pipe, string message);
string Transact(HANDLE pipe, char* message);
string Call(const wchar_t* pipe, char* message);

int main()
{
	HANDLE pipe;
	wstring name;

	try
	{
		cout << "~~~~~~Welcome to Remote Server Console~~~~~~" << endl;
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

		while (true)
		{
			wstring hostName, pipeName;
			cout << "Write server hostname: ";
			wcin >> hostName;
			cout << "Write pipe name: ";
			wcin >> pipeName;

			name = L"\\\\" + hostName + L"\\pipe\\" + pipeName;

			//Waiting for NP and connecting to pipe

			if (!WaitNamedPipe(name.c_str(), 10000))
			{
				cout << GetLastError() << endl;
				cout << "Incorrect hostname or pipename." << endl;
				continue;
			}

			break;
		}

		if ((pipe = CreateFile(name.c_str(),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			&SecurityAttributes, OPEN_EXISTING, NULL, NULL)) == INVALID_HANDLE_VALUE)
			throw SetPipeError("Create File Error: ", GetLastError());

		//Working Area

		cout << "Connection created successfully..." << endl;

		cout << "List of commands:" << endl;
		cout << "start" << endl;
		cout << "stop" << endl;
		cout << "exit" << endl;
		cout << "wait" << endl;
		cout << "shutdown (wait + exit)" << endl;
		cout << "statistics" << endl;


		string msg;

		while (true)
		{

			cin >> msg;

			if (Write(pipe, msg))
			{
				cout << "Successfully write to pipe" << endl;
			}

			if (strcmp(msg.c_str(), "exit") == 0)
			{
				cout << "Read message from pipe: " << Read(pipe) << endl;

				cout << "Disconnected from server." << endl;
				break;
			}
			if (strcmp(msg.c_str(), "shutdown") == 0)
			{
				cout << "Read message from pipe: " << Read(pipe) << endl;

				cout << "Concurrent server shutdown." << endl;
				break;
			}
			if (strcmp(msg.c_str(), "quit") == 0 )
			{
				cout << "Quit remote console" << endl;

				break;
			}
			cout << "Read message from pipe: " << Read(pipe) << endl;

		}

	}
	catch (string errorMsgText)
	{
		cout << endl << GetLastError();
		cout << endl << errorMsgText;
	}
	getchar();
	getchar();
	return 0;
}

string Read(HANDLE pipe)
{
	unsigned long bytesRead;
	char buffer[1024]{};
	if (!ReadFile(pipe, buffer, sizeof(buffer), &bytesRead, NULL))
		throw SetPipeError("Read Error: ", GetLastError());

	return buffer;
}

bool Write(HANDLE pipe, string message)
{
	unsigned long bytesWriten;
	if (!WriteFile(pipe, message.c_str(), sizeof(message), &bytesWriten, NULL))
	{
		throw SetPipeError("Write Error: ", GetLastError());
		return false;
	}

	return true;
}

string SetPipeError(string message, int code)
{
	return message + GetErrorMsgText(code);
}

string GetErrorMsgText(int code)
{
	string message;
	switch (code)
	{
	case ERROR_SUCCESS:
		message = "ERROR_SUCCESS";
		break;
	case ERROR_INVALID_FUNCTION:
		message = "ERROR_INVALID_FUNCTION";
		break;
	case ERROR_FILE_NOT_FOUND:
		message = "ERROR_FILE_NOT_FOUND";
		break;
	case ERROR_PATH_NOT_FOUND:
		message = "ERROR_PATH_NOT_FOUND";
		break;
	case ERROR_TOO_MANY_OPEN_FILES:
		message = "ERROR_TOO_MANY_OPEN_FILES";
		break;
	case ERROR_ACCESS_DENIED:
		message = "ERROR_ACCESS_DENIED";
		break;
	case ERROR_INVALID_HANDLE:
		message = "ERROR_INVALID_HANDLE";
		break;
	case ERROR_ARENA_TRASHED:
		message = "ERROR_ARENA_TRASHED";
		break;
	case ERROR_NOT_ENOUGH_MEMORY:
		message = "ERROR_NOT_ENOUGH_MEMORY";
		break;
	case ERROR_INVALID_BLOCK:
		message = "ERROR_INVALID_BLOCK";
		break;
	case ERROR_BAD_ENVIRONMENT:
		message = "ERROR_BAD_ENVIRONMENT";
		break;
	case ERROR_BAD_FORMAT:
		message = "ERROR_BAD_FORMAT";
		break;
	case ERROR_INVALID_ACCESS:
		message = "ERROR_INVALID_ACCESS";
		break;
	case ERROR_INVALID_DATA:
		message = "ERROR_INVALID_DATA";
		break;
	case ERROR_OUTOFMEMORY:
		message = "ERROR_OUTOFMEMORY";
		break;
	case ERROR_INVALID_DRIVE:
		message = "ERROR_INVALID_DRIVE";
		break;
	case ERROR_CURRENT_DIRECTORY:
		message = "ERROR_CURRENT_DIRECTORY";
		break;
	case ERROR_NOT_SAME_DEVICE:
		message = "ERROR_NOT_SAME_DEVICE";
		break;
	case ERROR_NO_MORE_FILES:
		message = "ERROR_NO_MORE_FILES";
		break;
	case ERROR_WRITE_PROTECT:
		message = "ERROR_WRITE_PROTECT";
		break;
	case ERROR_BAD_UNIT:
		message = "ERROR_BAD_UNIT";
		break;
	case ERROR_NOT_READY:
		message = "ERROR_NOT_READY";
		break;
	case ERROR_BAD_COMMAND:
		message = "ERROR_BAD_COMMAND";
		break;
	case ERROR_CRC:
		message = "ERROR_CRC";
		break;
	case ERROR_BAD_LENGTH:
		message = "ERROR_BAD_LENGTH";
		break;
	case ERROR_SEEK:
		message = "ERROR_SEEK";
		break;
	case ERROR_NOT_DOS_DISK:
		message = "ERROR_NOT_DOS_DISK";
		break;
	case ERROR_SECTOR_NOT_FOUND:
		message = "ERROR_SECTOR_NOT_FOUND";
		break;
	case ERROR_WRITE_FAULT:
		message = "ERROR_WRITE_FAULT";
		break;
	case ERROR_READ_FAULT:
		message = "ERROR_READ_FAULT";
		break;
	case ERROR_HANDLE_EOF:
		message = "ERROR_HANDLE_EOF";
		break;
	case ERROR_NOT_SUPPORTED:
		message = "ERROR_NOT_SUPPORTED";
		break;
	case ERROR_BAD_NETPATH:
		message = "ERROR_BAD_NETPATH";
		break;
	case ERROR_NETWORK_BUSY:
		message = "ERROR_NETWORK_BUSY";
		break;
	case ERROR_DEV_NOT_EXIST:
		message = "ERROR_DEV_NOT_EXIST";
		break;
	case ERROR_TOO_MANY_CMDS:
		message = "ERROR_TOO_MANY_CMDS";
		break;
	case ERROR_BAD_REM_ADAP:
		message = "ERROR_BAD_REM_ADAP";
		break;
	case ERROR_NO_SPOOL_SPACE:
		message = "ERROR_NO_SPOOL_SPACE";
		break;
	case ERROR_PRINT_CANCELLED:
		message = "ERROR_PRINT_CANCELLED";
		break;
	case ERROR_NETWORK_ACCESS_DENIED:
		message = "ERROR_NETWORK_ACCESS_DENIED";
		break;
	case ERROR_BAD_NET_NAME:
		message = "ERROR_BAD_NET_NAME";
		break;
	case ERROR_CANNOT_MAKE:
		message = "ERROR_CANNOT_MAKE";
		break;
	case ERROR_OUT_OF_STRUCTURES:
		message = "ERROR_OUT_OF_STRUCTURES";
		break;
	case ERROR_ALREADY_ASSIGNED:
		message = "ERROR_ALREADY_ASSIGNED";
		break;
	case ERROR_INVALID_PARAMETER:
		message = "ERROR_INVALID_PARAMETER";
		break;
	case ERROR_NET_WRITE_FAULT:
		message = "ERROR_NET_WRITE_FAULT";
		break;
	case ERROR_TOO_MANY_SEMAPHORES:
		message = "ERROR_TOO_MANY_SEMAPHORES";
		break;
	default:
		message = "~Error~";
		break;
	};
	return message;
}
