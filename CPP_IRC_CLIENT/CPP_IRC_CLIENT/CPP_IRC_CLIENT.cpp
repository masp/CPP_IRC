#include "Client.hpp"

bool running = true;
Client* client;

int main()
{
	system("Color 0A");
	SetConsoleTitle(L"CPP_IRC Client");
	printf("Welcome to the CPP_IRC Client.\n");

	printf("Attempting to connect to server...\n");
	client = new Client();

	char message[] = "Hello World!";
	client->sendMessagePacket(message);
	while(running)
	{
		client->update();
		Sleep(50);
	}
	return 0;
}