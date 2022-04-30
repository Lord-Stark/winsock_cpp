#pragma once

#include <winsock2.h>

#include "WSAStartup.h"

namespace WinSocket
{
    class SocketHolder
    {
    private:
        mutable SOCKET m_Sock;

    private:
        void WSAInit() const;

        void CloseSocket(SOCKET &SockFD) const;

    public:
        SocketHolder(SOCKET m_Sock);

        SocketHolder(int domain, int type, int protocol);

        void CloseSocket() const;

        ~SocketHolder();

        SOCKET GetSocket() const;

    public:
        SocketHolder(const SocketHolder &) = delete;
        SocketHolder(SocketHolder &&);

        SocketHolder &operator=(const SocketHolder &) = delete;
        SocketHolder &operator=(SocketHolder &&);
    };

    class TCPSocketHolder: public SocketHolder
    {
    public:
        TCPSocketHolder(): SocketHolder(PF_INET, SOCK_STREAM, IPPROTO_TCP) {}
    };

    class UDPSocketHolder: public SocketHolder
    {
    public:
        UDPSocketHolder(): SocketHolder(PF_INET, SOCK_DGRAM, IPPROTO_UDP) {}
    };
}