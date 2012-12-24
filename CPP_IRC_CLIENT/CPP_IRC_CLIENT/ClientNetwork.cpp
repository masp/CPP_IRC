#include "ClientNetwork.hpp"

ClientNetwork::ClientNetwork(void)
{
	WSADATA wsaData;
	ConnectSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL,
					*ptr = NULL,
					hints;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (iResult != 0)
	{
		printf("Failed to initialize connection!\n");
		return;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo("192.168.1.76", DEFAULT_PORT, &hints, &result);

	if (iResult != 0)
	{
		printf("Failed to get address info!\n");
		return;
	}

	for(ptr=result ; ptr != NULL ; ptr=ptr->ai_next)
	{
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Failed to connect socket!\n");
			WSACleanup();
			return;
		}
		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			printf("Failed to connect to server!\n");
			return;
		}
	}

	freeaddrinfo(result);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		WSACleanup();
		return;
	}

	u_long iMode = 1;
	iResult = ioctlsocket(ConnectSocket, FIONBIO, &iMode);
	if (iResult == SOCKET_ERROR)
	{
		printf("ioctlsocket failed with error: &d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return;
	}

	char value = 1;
	setsockopt(ConnectSocket, IPPROTO_TCP, TCP_NODELAY, &value, sizeof(value));
}

int ClientNetwork::receivePackets(char* p_recvbuf)
{
	iResult = NetworkServices::receiveMessage(ConnectSocket, p_recvbuf, MAX_PACKET_SIZE);
	if (iResult == 0)
	{
		printf("Connection closed\n");
        closesocket(ConnectSocket);
        WSACleanup();
	}
	return iResult;
}