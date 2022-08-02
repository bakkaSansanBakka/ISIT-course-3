#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
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
    SOCKET  cC;                                     // дескриптор сокета 
    WSADATA wsaData;
    SOCKADDR_IN serv;                                 // параметры  сокета сервера
    serv.sin_family = AF_INET;                        // используется IP-адресация  
    serv.sin_port = htons(2000);                      // TCP-порт 2000
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");    // адрес сервера
    char obuf[50] = "Hello from ClientU2 ";           //буфер вывода
    int lobuf = 0;

    int buffint = 0;
    char buff[50];

    try
    {
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
            throw  SetErrorMsgText("Startup:", WSAGetLastError());

        if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
            throw  SetErrorMsgText("socket:", WSAGetLastError());

        if ((lobuf = sendto(cC, obuf, strlen(obuf) + 1, NULL,
            (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
            throw  SetErrorMsgText("send:", WSAGetLastError());

        memset(&serv, 0, sizeof(serv)); // обнулить память
        int lc = sizeof(serv);    // размер SOCKADDR_IN//количество отправленных байт

        /*if (lobuf = recvfrom(cC, buff, sizeof(buff), NULL, (sockaddr*)&serv, &lc) == SOCKET_ERROR)
            throw  SetErrorMsgText("recv:", WSAGetLastError());

        cout << buff;*/

        int amount;
        cout << "Enter the number of messages: ";
        cin >> amount;

        clock_t start = clock();

        for (int i = 1; i <= amount; i++) {
            itoa(i, &obuf[20], 10);
            sendto(cC, obuf, strlen(obuf) + 1, NULL, (sockaddr*)&serv, sizeof(serv));
            buffint = recvfrom(cC, buff, sizeof(buff), NULL, (sockaddr*)&serv, &lc);
            cout << buff << endl;
            if (buffint == 0) break;
        }

        clock_t stop = clock();

        cout << "Time passed: " << stop;

        if (closesocket(cC) == SOCKET_ERROR)
            throw  SetErrorMsgText("closesocket:", WSAGetLastError());

        if (WSACleanup() == SOCKET_ERROR)
            throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
    }
    catch (string errorMsgText)
    {
        cout << endl << errorMsgText;
    }

    return 0;
}
