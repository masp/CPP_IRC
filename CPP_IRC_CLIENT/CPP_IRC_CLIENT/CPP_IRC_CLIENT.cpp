#include "Client.hpp"
#include <process.h>

bool running = true;
Client* client;

BOOL WINAPI console_handler(DWORD ctrltype)
{
	running = false;
	client->sendPacket(CLOSE_CONNECTION);
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

	while(running)
	{
		client->sendPacket(PING_EVENT);
		Sleep(2000);
	}

	return 0;
}

