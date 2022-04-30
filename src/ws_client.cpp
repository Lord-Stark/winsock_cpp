#include "socket.h"
#include "socketHolder.h"

#include <iostream>

using namespace std;

int main()
{
    // create socket
    WinSocket::TCPSocketHolder tcpholder;

    // initialization
    WinSocket::ClientSocket client(tcpholder, "127.0.0.1", 1234);

    // connect
    if(client.SocketConnect() == false)
    {
        cout << "Connect Function Failed." << endl;
        return -1;
    }

    // recv
    const char *message = client.SocketRecv();
    if(message == nullptr)
    {
        cout << "Recv Function Failed." << endl;
        return -1;
    }
    cout << "Message form server: " << message << endl;

    // send
    client.SocketSend("Hello, server! This is a message from client.\n");

    return 0;
}