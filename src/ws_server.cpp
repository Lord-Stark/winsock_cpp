#include "socket.h"
#include "socketHolder.h"

#include <iostream>

using namespace std;

int main()
{
    // create TCP socket
    WinSocket::TCPSocketHolder TCPSockHD;

    // initialization
    WinSocket::ServSocket server(TCPSockHD, "127.0.0.1", 1234);

    // bind
    server.SocketBind();

    // listen
    server.SocketListen(1);

    // accept
    WinSocket::ServSocket::ConnHandler ConnHD = server.SocketAccept();
    if(ConnHD == -1)
    {
        cout << "Accept Function Failed." << endl;
        return -1;
    }

    // send
    server.SocketSend(ConnHD, "Hello, client! This is a message from server.\n");

    // recv
    const char *message = server.SocketRecv(ConnHD);
    if(message == nullptr)
    {
        cout << "Recv Function Failed." << endl;
        return -1;
    }
    cout << "Message form client: " << message << endl;

    // close (There is no need to do this. We did RAII.)
    server.CloseConn(ConnHD);
    server.SocketClose();

    return 0;
}