#include <string>

#ifndef MAX_PACKET_SIZE
#define MAX_PACKET_DATA_SIZE 1024 // 1 Kilobit
#define MAX_PACKET_SIZE 1048576 // 1 Megabit

enum PacketType 
{
	INIT_CONNECTION = 0x00,		//Used for initializing connection with the server
	CLOSE_CONNECTION = 0x01,	//Used for closing connection with the server
	PING_EVENT = 0x02,			//Used to ping the server
	MESSAGE_EVENT = 0x03,		//Used to send a message
};

class Packet
{

public:

	void serialize(PacketType type, char* data, unsigned int length)
	{
		packet_data[0] = type;
		memcpy(&packet_data + 1, data, length);
	}
	void deserialize(char p_data[])
	{
		memcpy(this, p_data, sizeof(Packet));
	}
	
private:
	
	unsigned char packet_data[256]; // byte identifier + 255 length string
	
};
#endif
