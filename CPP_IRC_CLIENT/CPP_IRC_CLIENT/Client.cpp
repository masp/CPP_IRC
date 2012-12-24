#include "Client.hpp"

Client::Client(void)
{
	network = new ClientNetwork();

	if (int result = sendPacket(INIT_CONNECTION, "Initializing connection...") <= 0)
	{
		printf("Failed to connected to server with error: %d", result);
	}
	else
	{
		printf("Sucessfully connected to server\n\n");
	}
}

int Client::sendPacket(PacketType packet_type, char data[])
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_data[0] = packet_type;
	for(int i=0 ; i<sizeof(data) ; i++)
	{
		packet.packet_data[i + 1] = data[i];
	}

	packet.serialize(packet_data);

	return NetworkServices::sendMessage(network->ConnectSocket, packet_data, packet_size);
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

		switch(packet.packet_data[0])
		{
		case PING_EVENT:
			printf("You have been pinged by server");
			break;
		case MESSAGE_EVENT:
			printf("Client received MESSAGE_EVENT packet from server\n");
			break;
		default:
			printf("Error in packet types\n");
			break;
		}
	}
}