#pragma once

#include <winsock2.h>
#include <vector>

#include "socketHolder.h"

namespace WinSocket
{
    constexpr int WinSocketFailure = -1;

    class SocketBase
    {
    protected:
        SocketHolder &m_SockHD;

    protected:
        char m_RecvBuffer[MAXBYTE];

    protected:
        struct sockaddr_in m_SockAddr;

    private:
        void SetAddress(const char *IPAddr, unsigned short port);

    protected:
        inline bool SocketVaild(const SocketHolder &SockHD);
        
    public:
        SocketBase(SocketHolder &sockHD, const char *IPAddr, unsigned short port);

        void SocketClose();

        inline bool SocketVaild();

        ~SocketBase();
    };

    class ClientSocket: public SocketBase
    {
    public:
        ClientSocket(SocketHolder &sockHD, const char *IPAddr, unsigned short port);

        bool SocketConnect();

        const char *SocketRecv();

        void SocketSend(const char *message);
    };

    class ServSocket: public SocketBase
    {
    public:
        using ConnHandler = unsigned short;

    private:
        int m_Size;

        struct sockaddr_in m_ClientAddr;

        std::vector<SocketHolder> ConnSockVector;

    public:
        ServSocket(SocketHolder &sockHD, const char *IPAddr, unsigned short port);

        void SocketBind();

    public:
        void SocketListen(int ListLength);

        ConnHandler SocketAccept();

        const char *SocketRecv(ConnHandler ConnHD);

        void SocketSend(ConnHandler ConnHD, const char *message);

        void CloseConn(ConnHandler ConnHD);
    };
}