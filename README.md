# Introduction

A simple program written in `C++` to show the usage of `Windows Socket`.

This project is based on [`Lord-Stark/winsock_c: A simple program written in C to show the usage of Windows Socket.`](https://github.com/Lord-Stark/winsock_c).

I wrapped the raw Windows socket with an object-oriented language ` (C++)`  to make it `robust` and more importantly `easy to use`.

# Build

```bash
mkdir build

cd ./src
g++ WSAStartup.cpp socketHolder.cpp socket.cpp ws_server.cpp -lws2_32 -o ../build/ws_server.exe
g++ WSAStartup.cpp socketHolder.cpp socket.cpp ws_client.cpp -lws2_32 -o ../build/ws_client.exe
```

# Run

```bash
"./build/ws_server.exe"
"./build/ws_client.exe"
```

