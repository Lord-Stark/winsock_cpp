#include "socket.h"

// SocketBase
void WinSocket::SocketBase::SetAddress(const char *IPAddr, unsigned short port)
{
    memset(&m_SockAddr, 0, sizeof(m_SockAddr));
    m_SockAddr.sin_family = PF_INET;
    m_SockAddr.sin_addr.s_addr = inet_addr(IPAddr);
    m_SockAddr.sin_port = htons(port);
}

inline bool WinSocket::SocketBase::SocketVaild(const SocketHolder &SockHD)
{
    return SockHD.GetSocket() != INVALID_SOCKET;
}

WinSocket::SocketBase::SocketBase(WinSocket::SocketHolder &sockHD, const char *IPAddr, unsigned short port):
    m_SockHD(sockHD)
{
    memset(m_RecvBuffer, 0, MAXBYTE);
    memset(&m_SockAddr, 0, sizeof(struct sockaddr_in));
    SetAddress(IPAddr, port);
}

void WinSocket::SocketBase::SocketClose()
{
    m_SockHD.CloseSocket();
}

inline bool WinSocket::SocketBase::SocketVaild()
{
    return SocketVaild(m_SockHD);
}


WinSocket::SocketBase::~SocketBase()
{

}

// ClientSocket
WinSocket::ClientSocket::ClientSocket(WinSocket::SocketHolder &sockHD, const char *IPAddr, unsigned short port):
    WinSocket::SocketBase(sockHD, IPAddr, port)
{

}

bool WinSocket::ClientSocket::SocketConnect()
{
    if(SocketVaild() && connect(m_SockHD.GetSocket(), (SOCKADDR *)&m_SockAddr, sizeof(SOCKADDR)) == WinSocket::WinSocketFailure)
    {
        SocketClose();
        return false;
    }
    return true;
}
const char *WinSocket::ClientSocket::SocketRecv()
{
    memset(m_RecvBuffer, 0, MAXBYTE);

    if(SocketVaild() && recv(m_SockHD.GetSocket(), m_RecvBuffer, MAXBYTE, 0) <= 0)
    {
        SocketClose();
    }
    return m_RecvBuffer;
}

void WinSocket::ClientSocket::SocketSend(const char *message)
{
    if(SocketVaild() && send(m_SockHD.GetSocket(), message, strlen(message), 0) <= 0)
    {
        SocketClose();
    }
}

// ServSocket
WinSocket::ServSocket::ServSocket(WinSocket::SocketHolder &sockHD, const char *IPAddr, unsigned short port):
    WinSocket::SocketBase(sockHD, IPAddr, port), m_Size(sizeof(m_SockAddr))
{
    memset(&m_ClientAddr, 0, sizeof(struct sockaddr_in));
}

void WinSocket::ServSocket::SocketBind()
{
    if(SocketVaild() && bind(m_SockHD.GetSocket(), (SOCKADDR *)&m_SockAddr, sizeof(SOCKADDR)) == WinSocket::WinSocketFailure)
    {
        SocketClose();
    }
}

void WinSocket::ServSocket::SocketListen(int ListLength)
{
    if(SocketVaild() && listen(m_SockHD.GetSocket(), ListLength) == WinSocket::WinSocketFailure)
    {
        SocketClose();
    }
}

WinSocket::ServSocket::ConnHandler WinSocket::ServSocket::SocketAccept()
{
    if(SocketVaild())
    {
        SOCKET sock = accept(m_SockHD.GetSocket(), (SOCKADDR *)&m_ClientAddr, &m_Size);
        ConnSockVector.emplace_back(sock);
        return ConnSockVector.size() - 1;
    }

    return -1;
}

const char *WinSocket::ServSocket::SocketRecv(WinSocket::ServSocket::ConnHandler ConnHD)
{
    memset(m_RecvBuffer, 0, MAXBYTE);
    if(SocketVaild(ConnSockVector[ConnHD]) && recv(ConnSockVector[ConnHD].GetSocket(), m_RecvBuffer, MAXBYTE, 0) == WinSocket::WinSocketFailure)
    {
        CloseConn(ConnHD);
    }

    return m_RecvBuffer;
}

void WinSocket::ServSocket::SocketSend(WinSocket::ServSocket::ConnHandler ConnHD, const char *message)
{
    if(SocketVaild(ConnSockVector[ConnHD]) && send(ConnSockVector[ConnHD].GetSocket(), message, strlen(message), 0) == WinSocket::WinSocketFailure)
    {
        CloseConn(ConnHD);
    }
}

void WinSocket::ServSocket::CloseConn(WinSocket::ServSocket::ConnHandler ConnHD)
{
    ConnSockVector[ConnHD].CloseSocket();
}