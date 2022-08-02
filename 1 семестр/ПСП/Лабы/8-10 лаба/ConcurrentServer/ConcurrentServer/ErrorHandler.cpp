#include <string>
#include <WS2tcpip.h>
#include "ErrorHandler.h"

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
