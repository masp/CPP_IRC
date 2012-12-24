#include "Client.hpp"

Client::Client(void)
{
	network = new ClientNetwork();

	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = INIT_CONNECTION;
	packet.serialize(packet_data);

	int result = NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
	if (result <= 0)
	{
		printf("Failed to connected to server with error: " + result);
	}
	else
	{
		printf("Sucessfully connected to server\n\n");
	}
}

void Client::sendMessagePacket(char* message)
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = MESSAGE_EVENT;
	packet.packet_data = message;

	packet.serialize(packet_data);

	int result = NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
	if (result <= 0)
	{
		printf("Failed to send message!");
	}
}

void Client::update()
{
	Packet packet;
	int data_length = network->receivePackets(network_data);

	if (data_length <= 0)
	{
		return;
	}

	int i = 0;
	while(i < (unsigned int)data_length)
	{
		packet.deserialize(&network_data[i]);
		i += sizeof(Packet);

		switch(packet.packet_type)
		{
		case MESSAGE_EVENT:
			printf("Client received MESSAGE_EVENT packet from server\n");
			break;
		default:
			printf("Error in packet types\n");
			break;
		}
	}
}