#include "SocketHolder.h"

void WinSocket::SocketHolder::WSAInit() const
{
    WinSocket::WSAStartupSingleton::Startup();
}

void WinSocket::SocketHolder::CloseSocket(SOCKET &SockFD) const
{
    if(SockFD != INVALID_SOCKET)
    {
        closesocket(SockFD);
        SockFD = INVALID_SOCKET;
    }
}

WinSocket::SocketHolder::SocketHolder(SOCKET Sock)
{
    WSAInit();
    m_Sock = Sock;
}

WinSocket::SocketHolder::SocketHolder(int domain, int type, int protocol)
{
    WSAInit();
    m_Sock = socket(domain, type, protocol);
}

void WinSocket::SocketHolder::CloseSocket() const
{
    CloseSocket(m_Sock);
}

WinSocket::SocketHolder::SocketHolder(WinSocket::SocketHolder &&anoSocketHolder):
    m_Sock(anoSocketHolder.m_Sock)
{
    anoSocketHolder.m_Sock = INVALID_SOCKET;
}

WinSocket::SocketHolder &WinSocket::SocketHolder::operator=(WinSocket::SocketHolder &&anoSocketHolder)
{
    if(this != &anoSocketHolder)
    {
        CloseSocket(m_Sock);
        m_Sock = anoSocketHolder.m_Sock;
        anoSocketHolder.m_Sock = INVALID_SOCKET;
    }

    return *this;
}

WinSocket::SocketHolder::~SocketHolder()
{
    CloseSocket(m_Sock);
}

SOCKET WinSocket::SocketHolder::GetSocket() const
{
    return m_Sock;
}