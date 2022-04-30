#include "WSAStartup.h"

WinSocket::WSAStartupSingleton::WSAStartupSingleton(WORD version)
{
    WSAStartup(version, &wsaData);
}

WinSocket::WSAStartupSingleton::~WSAStartupSingleton()
{
    WSACleanup();
}

void WinSocket::WSAStartupSingleton::Startup(WORD version)
{
    static WinSocket::WSAStartupSingleton wsa(version);
}