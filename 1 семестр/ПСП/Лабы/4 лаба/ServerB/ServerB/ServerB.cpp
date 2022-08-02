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

SOCKET  sS;           // дескриптор сокета 
WSADATA wsaData;
SOCKADDR_IN serv;                     // параметры  сокета sS
//SOCKET cS;	                 // сокет для обмена данными с клиентом 
SOCKADDR_IN clnt;             // параметры  сокета клиента
int lc = sizeof(clnt);    // размер SOCKADDR_IN

char ibuf[50];                    //буфер ввода
int  lb = 0;                   //количество принятых байт
SOCKADDR_IN to;
char bto[50];
char servName[50] = "Hello";
SOCKADDR_IN serverAnother;

string  SetErrorMsgText(string msgText, int code)
{
    return  msgText + GetErrorMsgText(code);
};

bool GetRequestFromClient(
    char* name,             //[in] позывной сервера  
    short port,             //[in] номер просушиваемого порта
    struct sockaddr* from,  //[out] указатель на SOCKADDR_IN
    int* flen               //[out] указатель на размер from
    )
{
    *flen = sizeof(*from);
    int recvResult;

    try {
        if (recvResult = (recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)from, flen) == WSAETIMEDOUT))
            return false;
        if (recvResult == SOCKET_ERROR)
            throw  SetErrorMsgText("recv:", WSAGetLastError());
        
        if (strcmp(ibuf, name) == 0) {
            /*from = (sockaddr*)&clnt;
            flen = &lc;*/
            return true;
        }
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
        return false;
    }
    return false;
}

bool PutAnswerToClient(
    char* name,             //[in] позывной сервера
    struct sockaddr* to,    //[in] указатель на SOCKADDR_IN
    int lto)               //[in] указатель на размер to
{
    if (sendto(sS, name, strlen(name) + 1, NULL, (sockaddr*)to, sizeof(*to)) == SOCKET_ERROR)
        throw SetErrorMsgText("send:", WSAGetLastError());
    cout << "successful sendto from server" << endl;
    return true;
}

bool GetServer(
    char* call,             //[in] позывной сервера  
    short port,             //[in] номер порта сервера    
    struct sockaddr* from,  //[out] указатель на SOCKADDR_IN
    int* flen               //[out] указатель на размер from
) {
    *flen = sizeof(*from);
    int recvResult;

    try {
        if ((lb = sendto(sS, call, strlen(call) + 1, NULL, (sockaddr*)from, sizeof(*from))) == SOCKET_ERROR)
            throw  SetErrorMsgText("send:", WSAGetLastError());

        if (recvResult = recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)from, flen) == WSAETIMEDOUT)
            return false;
        if (recvResult == SOCKET_ERROR)
            throw  SetErrorMsgText("recv:", WSAGetLastError());

        if (strcmp(ibuf, call) == 0) {
            return true;
        }
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
        return false;
    }
    return false;
}

int main(int argc, char* argv[])
{
    serv.sin_family = AF_INET;           // используется IP-адресация  
    serv.sin_port = htons(2000);          // порт 2000
    serv.sin_addr.s_addr = INADDR_ANY;   // любой собственный IP-адрес
    memset(&clnt, 0, sizeof(clnt)); // обнулить память


    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw  SetErrorMsgText("Startup:", WSAGetLastError());

        if ((sS = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
            throw  SetErrorMsgText("socket:", WSAGetLastError());

        int optval = 1;
        if (setsockopt(sS, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
            throw SetErrorMsgText("Set socket option error:", WSAGetLastError());

        /*int timeno = 2000;
        if (setsockopt(sS, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeno, sizeof(int)) == SOCKET_ERROR)
            throw SetErrorMsgText("Set socket option error:", WSAGetLastError());*/

        if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
            throw  SetErrorMsgText("bind:", WSAGetLastError());

        serverAnother.sin_family = AF_INET;
        serverAnother.sin_port = htons(2000);
        serverAnother.sin_addr.s_addr = INADDR_ANY;
        int len = sizeof(serverAnother);

        if (GetServer(servName, serverAnother.sin_port, (sockaddr*)&serverAnother, &len)) {
            cout << "Found another Server (" << inet_ntoa(serverAnother.sin_addr) << ":" << htons(serverAnother.sin_port) << ")";
        }
        else {
            cout << "Server name is unique" << endl;
        }

        memset(&clnt, 0, sizeof(clnt)); // обнулить память

        while (true) {
            if (GetRequestFromClient(servName, serv.sin_port, (sockaddr*)&clnt, &lc)) {
                cout << "Got request from Client (" << inet_ntoa(clnt.sin_addr) << ":" << htons(clnt.sin_port) << ")" << endl;
                PutAnswerToClient(servName, (sockaddr*)&clnt, sizeof(clnt));
                
            }
            else {
                cout << "Fail" << endl;
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