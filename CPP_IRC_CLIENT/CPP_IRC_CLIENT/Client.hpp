#include "ClientNetwork.hpp"
#include "../../CPP_IRC_DEFAULTS/NetworkData.h"

class Client
{
public:
	Client();
	~Client(void);

	ClientNetwork* network;
	char network_data[MAX_PACKET_SIZE];

	void sendMessagePacket(char* message);
	void update();
};