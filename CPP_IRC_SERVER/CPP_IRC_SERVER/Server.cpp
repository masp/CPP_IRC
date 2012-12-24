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
		char* p_ping_message ("Ping from client_id ");
		while(i < (unsigned int)data_length)
		{
			packet.deserialize(&network_data[i]);
			i += sizeof(Packet);

			switch(packet.packet_data[0])
			{
			case INIT_CONNECTION:
				printf("Server received INIT_CONNECTION packet from client_id %d\n", iter->first);
                break;
			case CLOSE_CONNECTION:
				printf("Closing connection with client_id %d", iter->first);
				closesocket(iter->second);
				network->sessions.erase(iter);
				if (client_id > 0)
				{
					client_id--;
				}
				break;
			case PING_EVENT:
				printf("Server received PING_EVENT packet from client_id %d\n", iter->first);
				p_ping_message += iter->first;
				sendPacket(PING_EVENT, iter->second, p_ping_message);
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

void Server::sendPacket(PacketType packet_type, SOCKET ignore, char data[])
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
	network->sendToAll(packet_data, packet_size, ignore);
}