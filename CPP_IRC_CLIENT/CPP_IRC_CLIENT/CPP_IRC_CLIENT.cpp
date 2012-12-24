#include "Client.hpp"
#include <process.h>

bool running = true;
Client* client;

BOOL WINAPI console_handler(DWORD ctrltype)
{
	running = false;
	client->sendPacket(CLOSE_CONNECTION, "Closing connection");
	closesocket(client->network->ConnectSocket);
	return TRUE;
}

void clientNetworkLoop(void*)
{
	while(running)
	{
		client->update();
		Sleep(250);
	}
}

int main()
{
	system("Color 0A");
	SetConsoleTitle(L"CPP_IRC Client");
	SetConsoleCtrlHandler(console_handler, TRUE);
	printf("Welcome to the CPP_IRC Client.\n");

	printf("Attempting to connect to server...\n");
	client = new Client();

	_beginthread(clientNetworkLoop, 0, (void*)12);

	char message[255];
	while(running)
	{
		cin >> message;
		if (message == "PING")
		{
			client->sendPacket(PING_EVENT, "Random ping");
		}
		else
		{
			client->sendPacket(MESSAGE_EVENT, message);
		}
	}
	return 0;
}

