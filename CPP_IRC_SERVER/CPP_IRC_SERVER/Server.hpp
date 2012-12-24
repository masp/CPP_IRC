#include "ServerNetwork.hpp"
#include "../../CPP_IRC_DEFAULTS/NetworkData.h"

class Server
{
public:
	Server(void);
	~Server(void);

	void update();

private:
	static unsigned int client_id;
	ServerNetwork* network;
	char network_data[MAX_PACKET_SIZE];

	void receiveFromClients();
	void sendPacket(PacketType, SOCKET);
};