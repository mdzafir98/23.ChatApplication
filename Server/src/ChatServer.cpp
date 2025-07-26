#include "../include/ChatServer.h"

ChatServer::ChatServer()
{
    std::cout<<"ChatServer instance created."<<"\n";
}

void ChatServer::handleInput()
{
    if(IsKeyPressed(KEY_L)){
        this->listMessage();
    }
}

void ChatServer::addMessage(std::string message)
{
    messageVector.push_back(message);
}

void ChatServer::stateMessageCount() const
{
    std::cout<<messageVector.size()<<"\n";
}

void ChatServer::listMessage() const
{
    for(int i=0; i<messageVector.size(); i++){
        std::cout<<messageVector.at(i)<<"\n";
    }
}
