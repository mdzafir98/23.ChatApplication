#pragma once
#include <iostream>
#include <enet/enet.h>
#include <cstring>
#include <string>

void send_client_packet_to_server(ENetPeer* peer,char data[100])
{
    ENetPacket* packet=enet_packet_create(data,strlen(data)+1,ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer,0,packet);
}

std::string convert_DATAPACKET_to_string(unsigned char* dataPacket)
{
    std::string temp=reinterpret_cast<const char*>(dataPacket);
    return temp;
}
