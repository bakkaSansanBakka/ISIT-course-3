#pragma once
#include "Contact.h"
#include "TalkersCommand.h"
#include "Timetable.h"

DWORD WINAPI AcceptServer(LPVOID prm);
DWORD WINAPI ConsolePipe(LPVOID prm);
DWORD WINAPI GarbageCleaner(LPVOID prm);
DWORD WINAPI DispatchServer(LPVOID prm);
DWORD WINAPI ResponseServer(LPVOID prm);
DWORD WINAPI MailSlotServer(LPVOID prm);

void CALLBACK ASStartMessage(Contact* contact);
void CALLBACK ASFinishMessage(Contact* contact);
void CALLBACK ASWTimer(LPVOID contact, DWORD timerLowValue, DWORD timerHighValue);

void CommandCycle(TalkersCommand& cmd);
bool AcceptCycle(int squirt);
bool GetRequestFromClient(SOCKET serverSocket, string name, SOCKADDR_IN* from);
bool PutAnswerToClient(SOCKET serverSocket, string name, SOCKADDR_IN* to);
list<string> SplitMail(string mail);
string CreateMaintainMessage(string serverName, Timetable* timetable);

TalkersCommand GetCmdFromStr(char* str);