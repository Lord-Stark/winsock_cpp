#pragma once

#include <winsock2.h>

namespace WinSocket
{
    class WSAStartupSingleton
    {
    private:
        WSADATA wsaData;

    private:
        WSAStartupSingleton(WORD version);

        ~WSAStartupSingleton();
        
    public:
        WSAStartupSingleton(const WSAStartupSingleton &) = delete;
        WSAStartupSingleton(WSAStartupSingleton &&) = delete;

        WSAStartupSingleton &operator=(const WSAStartupSingleton &) = delete;
        WSAStartupSingleton &operator=(WSAStartupSingleton &&) = delete;

    public:
        static void Startup(WORD version = MAKEWORD(2, 2));
    };
}