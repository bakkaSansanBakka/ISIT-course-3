#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Winsock2.h"
#pragma comment(lib, "WS2_32.lib")

#include <iostream>
#include <string>
using namespace std;

string  GetErrorMsgText(int code)    // cформировать текст ошибки 
{
    string msgText;
    switch (code)                      // проверка кода возврата  
    {
        case WSAEINTR:  msgText = "WSAEINTR";   break;
        case WSAEACCES: msgText = "WSAEACCESS"; break;
        case WSAEFAULT: msgText = "WSAEFAULT";  break;
        case WSAEINVAL: msgText = "WSAEINVAL";  break;
        case WSAEMFILE: msgText = "WSAEMFILE";  break;
        case WSAEWOULDBLOCK:    msgText = "WSAEWOULDBLOCK"; break;
        case WSAEALREADY:       msgText = "WSAEALREADY";    break;
        case WSAENOTSOCK:       msgText = "WSAENOTSOCK";    break;
        case WSAEDESTADDRREQ:   msgText = "WSAEDESTADDRREQ";    break;
        case WSAEPROTOTYPE:     msgText = "WSAEPROTOTYPE";  break;
        case WSAENOPROTOOPT:    msgText = "WSAENOPROTOOPT"; break;
        case WSAEPROTONOSUPPORT:    msgText = "WSAEPROTONOSUPPORT"; break;
        case WSAESOCKTNOSUPPORT:    msgText = "WSAESOCKTNOSUPPORT"; break;
        case WSAEOPNOTSUPP:     msgText = "WSAEOPNOTSUPP";  break;
        case WSAEPFNOSUPPORT:   msgText = "WSAEPFNOSUPPORT";        break;
        case WSAEAFNOSUPPORT:   msgText = "WSAEAFNOSUPPORT";        break;
        case WSAEADDRINUSE:     msgText = "WSAEADDRINUSE";  break;
        case WSAEADDRNOTAVAIL:  msgText = "WSAEADDRNOTAVAIL";       break;
        case WSAENETDOWN:       msgText = "WSAENETDOWN";    break;
        case WSAENETUNREACH:    msgText = "WSAENETUNREACH"; break;
        case WSAENETRESET:      msgText = "WSAENETRESET";   break;
        case WSAECONNABORTED:   msgText = "WSAECONNABORTED";        break;
        case WSAECONNRESET:     msgText = "WSAECONNRESET";  break;
        case WSAENOBUFS:        msgText = "WSAENOBUFS";     break;
        case WSAEISCONN:        msgText = "WSAEISCONN";     break;
        case WSAENOTCONN:       msgText = "WSAENOTCONN";    break;
        case WSAESHUTDOWN:      msgText = "WSAESHUTDOWN";   break;
        case WSAEINPROGRESS:    msgText = "WSAEINPROGRESS"; break;
        case WSAEMSGSIZE:       msgText = "WSAEMSGSIZE";    break;
        case WSAETIMEDOUT:      msgText = "WSAETIMEDOUT";   break;
        case WSAECONNREFUSED:   msgText = "WSAECONNREFUSED";        break;
        case WSAEHOSTDOWN:      msgText = "WSAEHOSTDOWN";   break;
        case WSAEHOSTUNREACH:   msgText = "WSAEHOSTUNREACH";        break;
        case WSAEPROCLIM:       msgText = "WSAEPROCLIM";    break;
        case WSAVERNOTSUPPORTED:    msgText = "WSAVERNOTSUPPORTED"; break;
        case WSANOTINITIALISED: msgText = "WSANOTINITIALISED";      break;
        case WSAEDISCON:        msgText = "WSAEDISCON";     break;
        case WSATYPE_NOT_FOUND: msgText = "WSATYPE_NOT_FOUND";      break;
        case WSAHOST_NOT_FOUND: msgText = "WSAHOST_NOT_FOUND";      break;
        case WSATRY_AGAIN:      msgText = "WSATRY_AGAIN";   break;
        case WSANO_RECOVERY:    msgText = "WSANO_RECOVERY"; break;
        case WSANO_DATA:        msgText = "WSANO_DATA";     break;
        case WSA_INVALID_HANDLE:    msgText = "WSA_INVALID_HANDLE"; break;
        case WSA_INVALID_PARAMETER: msgText = "WSA_INVALID_PARAMETER";  break;
        case WSA_IO_INCOMPLETE:     msgText = "WSA_IO_INCOMPLETE";  break;
        case WSA_IO_PENDING:    msgText = "WSA_IO_PENDING"; break;
        case WSA_NOT_ENOUGH_MEMORY: msgText = "WSA_NOT_ENOUGH_MEMORY";  break;
        case WSA_OPERATION_ABORTED: msgText = "WSA_OPERATION_ABORTED";  break;
        case WSAEINVALIDPROCTABLE:  msgText = "WSAINVALIDPROCTABLE";    break;
        case WSAEINVALIDPROVIDER:   msgText = "WSAEINVALIDPROVIDER";    break;
        case WSAEPROVIDERFAILEDINIT:    msgText = "WSAPROVIDERFAILEDINIT";  break;
        case WSASYSCALLFAILURE:     msgText = "WSASYSCALLFAILURE";      break;
        case WSASYSNOTREADY:        msgText = "WSASYSNOTREADY";     break;
        default:    msgText = "Error";  break;
    };
    return msgText;
};


string  SetErrorMsgText(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};

int main(int argc, char* argv[])
{
    SOCKET  sS;           // дескриптор сокета 
    WSADATA wsaData;
    SOCKADDR_IN serv;                     // параметры  сокета sS
    serv.sin_family = AF_INET;           // используется IP-адресация  
    serv.sin_port = htons(2000);          // порт 2000
    serv.sin_addr.s_addr = INADDR_ANY;   // любой собственный IP-адрес
    SOCKET cS;	                 // сокет для обмена данными с клиентом 
    SOCKADDR_IN clnt;             // параметры  сокета клиента
    memset(&clnt, 0, sizeof(clnt)); // обнулить память
    int lclnt = sizeof(clnt);    // размер SOCKADDR_IN

    char ibuf[50];                    //буфер ввода
    int  libuf = 0;                   //количество принятых байт

    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw  SetErrorMsgText("Startup:", WSAGetLastError());

        if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
            throw  SetErrorMsgText("socket:", WSAGetLastError());

        if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
            throw  SetErrorMsgText("bind:", WSAGetLastError());
        while (true) {


            if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
                throw  SetErrorMsgText("listen:", WSAGetLastError());

            memset(&clnt, 0, sizeof(clnt));
            lclnt = sizeof(clnt);


            if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET)
                throw  SetErrorMsgText("accept:", WSAGetLastError());

            /*cout << "Client IP: " << inet_ntoa(clnt.sin_addr);
            cout << endl << "Client port: " << htons(clnt.sin_port) << endl;*/

            while (true) {

                libuf = recv(cS, ibuf, sizeof(ibuf), NULL);
                if (libuf == 0)
                    break;
                cout << endl << ibuf;
                send(cS, ibuf, strlen(ibuf) + 1, NULL);
            }

        }

        if (closesocket(sS) == SOCKET_ERROR)
            throw  SetErrorMsgText("closesocket:", WSAGetLastError());

        if (WSACleanup() == SOCKET_ERROR)
            throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
    }

    cout << endl;

    return 0;
}
