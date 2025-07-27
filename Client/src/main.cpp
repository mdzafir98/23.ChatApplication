// this is the client application
#include <enet/enet.h>
#include <raylib.h>
#include "../include/Game.h"
#include "../../Shared/Functions.h"

#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>

int main(void)
{
    if(enet_initialize()!=0){
        fprintf(stderr,"An error occurred while trying to init Enet!\n");
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    ENetHost* client;
    client=enet_host_create(nullptr,1,1,0,0);

    if(client==nullptr){
        fprintf(stderr,"An error occurred while tring to create an Enet client!\n");
        return EXIT_FAILURE;
    }

    ENetAddress address;
    ENetEvent event;
    ENetPeer* peer;

    enet_address_set_host(&address,"127.0.0.1");
    address.port=7777;

    peer=enet_host_connect(client,&address,1,0);
    if(peer==nullptr){
        fprintf(stderr,"No available peers for initialising an Enet connection!\n");
        return EXIT_FAILURE;
    }

    if(enet_host_service(client,&event,5000)>0 && event.type==ENET_EVENT_TYPE_CONNECT){
        puts("Connect to 127.0.0.1:7777 succeed.");
    }else{
        enet_peer_reset(peer);
        puts("Connection to 127.0.0.1:7777 fail.");
        return EXIT_SUCCESS;
    }

    InitWindow(512.f,512.f,"CLIENT");
    SetTargetFPS(60);
    Game game;

    while(WindowShouldClose()==false){
        while(enet_host_service(client,&event,10)>0){
            switch(event.type){
                case ENET_EVENT_TYPE_RECEIVE:
                    std::string temp=convert_DATAPACKET_to_string(event.packet->data);
                    std::cout<<temp<<"\n";
                    enet_packet_destroy(event.packet);
                    break;
            }
        }

        // GAME LOGIC STARTS
        game.handleInput();
        if(IsKeyPressed(KEY_ENTER)){
            send_client_packet_to_server(peer,game.data);

            // clear the char array after sending the data packet to server
            memset(game.data,'\0',sizeof(game.data));
        }
        game.update();
        BeginDrawing();
            ClearBackground({29,29,27,255});
            game.draw();
            DrawFPS(10,10);
        EndDrawing();
    }
    CloseWindow();

    enet_peer_disconnect(peer,0);
    while(enet_host_service(client,&event,3000)>0){
        switch(event.type){
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Diconnection succeed.");
                break;
        }
    }
    return EXIT_SUCCESS;
}
