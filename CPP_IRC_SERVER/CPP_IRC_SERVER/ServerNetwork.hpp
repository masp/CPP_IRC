#include "../../CPP_IRC_DEFAULTS/NetworkServices.hpp"
#include "../../CPP_IRC_DEFAULTS/NetworkData.h"
#include <map>

class ServerNetwork
{
public:
	ServerNetwork(void);
	~ServerNetwork(void);

	SOCKET ListenSocket;
	SOCKET ClientSocket;

	int iResult;
	map<unsigned int, SOCKET> sessions;

	bool acceptNewClient(unsigned int& id);
	int receiveData(unsigned int client_id, char* p_recvbuf);
	void sendToAll(char* packets, int totalSize, SOCKET ignore);
};