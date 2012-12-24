#include <string>

#ifndef MAX_PACKET_SIZE
#define MAX_PACKET_SIZE 1048576 // 1 Megabit

enum PacketType 
{
	INIT_CONNECTION = 0x00,
	MESSAGE_EVENT = 0x01,
};

struct Packet
{
	unsigned char packet_type;
	char* packet_data;

	void serialize(char* p_data)
	{
		memcpy(p_data, this, sizeof(Packet));
	}
	void deserialize(char* p_data)
	{
		memcpy(this, p_data, sizeof(Packet));
	}
};
#endif