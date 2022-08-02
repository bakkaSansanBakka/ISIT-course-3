#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <string>
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")
using namespace std;

string SetErrorMsgText(string message, int code);
string GetErrorMsgText(int code);
void Send(SOCKET clientSocket, const char* message);
string Receive(SOCKET clientSocket);
string ReceiveFrom(SOCKET clientSocket, SOCKADDR_IN* serverAddr);
bool GetServer(SOCKET clientSocket, string name, SOCKADDR_IN* from);
void SendTo(SOCKET clientSocket, SOCKADDR_IN* serverAddress, string message);


int main()
{
	SOCKADDR_IN server;
	SOCKADDR_IN all;

	SOCKET clientSocket;
	WSADATA wsaData;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup:", WSAGetLastError());

		if ((clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket:", WSAGetLastError());


	
		int timeno = 6000;
		if (setsockopt(clientSocket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeno, sizeof(int)) == SOCKET_ERROR)
			throw SetErrorMsgText("Set socket option error:", WSAGetLastError());

		auto optval = "1";
		if (setsockopt(clientSocket, SOL_SOCKET, SO_BROADCAST, optval, sizeof(optval)))
			throw SetErrorMsgText("Set socket option error: ", WSAGetLastError());


		string receivedMessage, sendingMessage;

		all.sin_family = AF_INET;
		all.sin_addr.s_addr = INADDR_BROADCAST;
		u_short responsePort;

		while (true)
		{

			cout << "Input server port to search concurrent server:";
			cin >> responsePort;

			all.sin_port = htons(responsePort);

			cout << "Write a server name to connect:";
			cin >> sendingMessage;
			if (GetServer(clientSocket, sendingMessage, &all))
			{
				server = all;
				break;
			}

			cout << "Timeout. Wrong server name or port (or server is not available)...\n" << endl;
		}

		if ((closesocket(clientSocket)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket:", WSAGetLastError());

		if ((clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
			throw SetErrorMsgText("Socket:", WSAGetLastError());

		if ((connect(clientSocket, (SOCKADDR*)&server, sizeof(server))) == SOCKET_ERROR)
			throw SetErrorMsgText("Connect:", WSAGetLastError());

		//cout << "Connected to concurrent server (" << inet_ntoa(server.sin_addr) << ":" << htons(server.sin_port) << ")" << "\n";

		cout << "Choose and write server service to work with: ECHO, RAND, TIME" << endl;
		cout << "~~Write 'exit' to stop working with server~~" << endl;

		while (true)
		{
			cin >> sendingMessage;

			if (strcmp(sendingMessage.c_str(), "exit") == 0)
			{
				cout << "Stop working with concurrent server..." << endl;
				break;
			}

			cout << "Sending: " << sendingMessage.c_str() << endl;
			Send(clientSocket, sendingMessage.c_str());

			receivedMessage = Receive(clientSocket);

			if (receivedMessage == "Error Inquiry")
			{
				cout << "Wrong command. Exit..." << endl;
				break;
			}

			if (receivedMessage == "TIMEDOUT")
			{
				cout << "TIMEDOUT" << endl;
				break;
			}

			if (receivedMessage.empty())
				break;

			cout << "Received: " << receivedMessage << endl;

		}

		if (closesocket(clientSocket) == SOCKET_ERROR)
			throw SetErrorMsgText("Close Socket:", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup:", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << " code " << WSAGetLastError() << endl;
	}

	getchar();
	getchar();
	return 0;
}

void SendTo(SOCKET clientSocket, SOCKADDR_IN* serverAddress, string message)
{
	if ((sendto(clientSocket, message.c_str(), strlen(message.c_str()), NULL, (sockaddr*)serverAddress, sizeof(*serverAddress)) == SOCKET_ERROR))
		throw SetErrorMsgText("SendTo:", WSAGetLastError());
}

string ReceiveFrom(SOCKET clientSocket, SOCKADDR_IN* serverAddr)
{
	char buffer[50] = {};
	int addressLength = sizeof(*serverAddr);
	if (recvfrom(clientSocket, buffer, sizeof(buffer), NULL, (sockaddr*)serverAddr, &addressLength) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT)
			return "TIMEOUT";
		else
			throw SetErrorMsgText("RecvFrom:", WSAGetLastError());
	}

	return string(buffer);
}


bool GetServer(SOCKET clientSocket, string name, SOCKADDR_IN* from)
{
	string receivedMessage;

	SendTo(clientSocket, from, name);
	receivedMessage = ReceiveFrom(clientSocket, from);

	if (WSAGetLastError() == WSAETIMEDOUT)
	{
		return false;
	}
	if (!receivedMessage.empty())
	{
		u_short servPort = atoi(receivedMessage.c_str());
		from->sin_port = htons(servPort);

		return true;
	}

	return false;

}

void Send(SOCKET clientSocket, const char* message)
{
	if ((send(clientSocket, message, sizeof(message), NULL)) == SOCKET_ERROR)
		throw SetErrorMsgText("Send:", WSAGetLastError());
}

string Receive(SOCKET clientSocket)
{
	char buffer[50] = {};

	if (recv(clientSocket, buffer, sizeof(buffer), NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT)
			return "TIMEDOUT";
		throw SetErrorMsgText("Recv:", WSAGetLastError());
	}

	return buffer;
}

string SetErrorMsgText(string message, int code)
{
	return message + GetErrorMsgText(code);
}

string GetErrorMsgText(int code)
{
	string message;
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
	case WSAEINPROGRESS:
		message = "WSAEINPROGRESS";
		break;
	case WSAEMSGSIZE:
		message = "WSAEMSGSIZE";
		break;
	case WSAEADDRINUSE:
		message = "WSAEADDRINUSE";
		break;
	case WSAETIMEDOUT:
		message = "WSAETIMEDOUT";
		break;
	case WSAHOST_NOT_FOUND:
		message = "WSAHOST_NOT_FOUND";
		break;
	case WSASYSNOTREADY:
		message = "WSASYSNOTREADY";
		break;
	case WSAEHOSTUNREACH:
		message = "WSAEHOSTUNREACH";
		break;
	case WSAESHUTDOWN:
		message = "WSAESHUTDOWN";
		break;
	case WSAENOTCONN:
		message = "WSAENOTCONN";
		break;
	case WSAENETDOWN:
		message = "WSAENETDOWN";
		break;
	case WSAENETUNREACH:
		message = "WSAENETUNREACH";
		break;
	case WSAENOTSOCK:
		message = "WSAENOTSOCK";
		break;
	default:
		message = "~Error~";
		break;
	};
	return message;
}
