#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <raylib.h>

class ChatServer{
public:
    ChatServer();

    void handleInput();

    void addMessage(std::string message);
    void stateMessageCount() const;
    void listMessage() const;

private:
    std::vector<std::string> messageVector;
};
