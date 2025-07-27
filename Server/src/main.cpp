// this is the server application
#include <enet/enet.h>
#include <raylib.h>

#include <iostream>
#include <cstring>
#include <string>
#include <stdio.h>
#include "../include/ChatServer.h"
#include "../../Shared/Functions.h"

int main(void)
{
    if(enet_initialize()!=0){
        fprintf(stderr,"An error occurred while tring to init Enet!\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    ENetAddress address;
    ENetHost* server;
    ENetEvent event;

    address.host=ENET_HOST_ANY;
    address.port=7777;
    server=enet_host_create(&address,32,1,0,0);

    if(server==nullptr){
        fprintf(stderr,"An error occurred while trying to create an Enet server!\n");
        return EXIT_FAILURE;
    }

    InitWindow(512.f,512.f,"SERVER");
    SetTargetFPS(60);

    ChatServer chatServer;

    bool clientConnected={false};
    int clientCount={0};

    while(WindowShouldClose()==false){
        while(enet_host_service(server,&event,10)>0){
            switch(event.type){
                // 01. client connects to server
                case ENET_EVENT_TYPE_CONNECT:
                {
                    printf("A new client connected from %x:%u.\n",
                                event.peer->address.host,
                                event.peer->address.port);

                    // broadcast data packet to all clients
                    broadcast_server_packet(server,"hi client\0");

                    clientCount++;
                    clientConnected=true;
                    std::cout<<"Client connect: "<<std::boolalpha<<clientConnected<<"\n";
                    std::cout<<"Client count: "<<clientCount<<"\n";
                    break;
                }

                // 02. recieve packet from client
                case ENET_EVENT_TYPE_RECEIVE:
                {
                    printf("Recieved data packet from %x:%u containing: %s.",
                                event.peer->address.host,
                                event.peer->address.port,
                                event.packet->data);
                    std::cout<<"\n";
                    std::string temp=convert_DATAPACKET_to_string(event.packet->data);
                    chatServer.addMessage(temp);
                    chatServer.stateMessageCount();
                    enet_packet_destroy(event.packet);
                    break;
                }

                // 03. client disconnects from server
                case ENET_EVENT_TYPE_DISCONNECT:
                {
                    printf("%x:%u disconnected.\n",
                                event.peer->address.host,
                                event.peer->address.port);

                    clientCount--;
                    clientConnected=false;
                    std::cout<<"Client connect: "<<clientConnected<<"\n";
                    std::cout<<"Client count: "<<clientCount<<"\n";
                    break;
                }
            }
        }
        BeginDrawing();
            chatServer.handleInput();
            if(clientCount>0){
                DrawCircle(200,200,50,GREEN);
                DrawText(TextFormat("ClientCount: %u",clientCount),100,20,20,RAYWHITE);
            }
            ClearBackground({29,29,27,255});
        EndDrawing();
    }
    CloseWindow();

    enet_host_destroy(server);
    return EXIT_SUCCESS;
}
