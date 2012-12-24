#include <WinSock2.h>
#include <Windows.h>
#include <WS2tcpip.h>
#include <iostream>

using namespace std;
#ifndef DEFAULT_BUFLEN
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "256"

#pragma comment (lib, "Ws2_32.lib")

class NetworkServices
{
public:
	static int sendMessage(SOCKET curSocket, char* message, int messageSize);
	static int receiveMessage(SOCKET curSocket, char* buffer, int bufSize);
};

#endif