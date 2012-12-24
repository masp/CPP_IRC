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
			i += sizeof(Packet);

			switch(packet.packet_type)
			{
			case INIT_CONNECTION:
				printf("Server received INIT_CONNECTION packet from client_id %d\n", iter->first);
                break;
			case PING_EVENT:
				printf("Server received PING_EVENT packet from client_id %d\n", iter->first);
				sendPacket(PING_EVENT, iter->second);
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

void Server::sendPacket(PacketType packet_type, SOCKET ignore)
{
	const unsigned int packet_size = sizeof(Packet);
	char packet_data[packet_size];

	Packet packet;
	packet.packet_type = packet_type;

	packet.serialize(packet_data);

	network->sendToAll(packet_data, packet_size, ignore);
}