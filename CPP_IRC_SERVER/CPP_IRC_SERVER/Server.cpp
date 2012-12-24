#include "Server.hpp"

unsigned int Server::client_id;

Server::Server(void)
{
	client_id = 0;
	network = new ServerNetwork();
}

void Server::update()
{
	if (network->acceptNewClient(client_id))
	{
		printf("client %d has been connected to the server\n", client_id); 
        client_id++;
	}
	receiveFromClients();
}

void Server::receiveFromClients()
{
	Packet packet;
	map<unsigned int, SOCKET>::iterator iter;

	for(iter = network->sessions.begin() ; iter != network->sessions.end() ; iter++)
	{
		int data_length = network->receiveData(iter->first, network_data);
		if (data_length <= 0)
		{
			continue;
		}
		unsigned int i=0;
		while(i < (unsigned int)data_length)
		{
			packet.deserialize(&network_data[i]);
			printf("Package Type: %d   Packet Data: %d\n", packet.packet_type, packet.packet_data);
			i += sizeof(Packet);

			switch(packet.packet_type)
			{
			case INIT_CONNECTION:
				printf("Server received INIT_CONNECTION packet from client\n");
                break;
			case MESSAGE_EVENT:
				printf("Server received MESSAGE_EVENT packet from client\n");
                break;
			default:
				printf("Error in packet types\n");
				break;
			}
		}
	}
}

void Server::sendMessagePacket(char* message)
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = MESSAGE_EVENT;

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size);
}