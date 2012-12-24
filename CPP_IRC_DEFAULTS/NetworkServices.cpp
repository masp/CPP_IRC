#include "NetworkServices.hpp"

int NetworkServices::sendMessage(SOCKET socket, char* message, int messageSize)
{
	return send(socket, message, messageSize, 0);
}

int NetworkServices::receiveMessage(SOCKET socket, char* buffer, int bufferSize)
{
	return recv(socket, buffer, bufferSize, 0);
}