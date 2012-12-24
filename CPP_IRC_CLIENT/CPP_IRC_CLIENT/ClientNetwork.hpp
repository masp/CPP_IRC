#include "../../CPP_IRC_DEFAULTS/NetworkServices.hpp"
#include "../../CPP_IRC_DEFAULTS/NetworkData.h"
#include <cstdio>

#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

class ClientNetwork
{
public:
	SOCKET ConnectSocket;
	int iResult;

	ClientNetwork(void);
	~ClientNetwork(void);

	int receivePackets(char*);
};