#include "Server.hpp"

bool running = true;

Server* server;

int main()
{
	system("Color 0A");
	SetConsoleTitle(L"CPP_IRC Server");
	printf("Welcome to the CPP_IRC Server.\n\n");

	printf("Waiting for client to connect...\n\n");

	server = new Server();
	while(running)
	{
		server->update();
		Sleep(50);
	}
	return 0;
}