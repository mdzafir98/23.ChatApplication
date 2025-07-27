#pragma once
#include <raylib.h>
#include <iostream>
#include <cstring>

enum State{
    STATE_INTRO=0,
    STATE_MSG_LOOP=1
};

class Game{
public:
    Game();
    State gameState=STATE_INTRO;

    void handleInput();
    void update();
    void draw();
    char data[100]="\0";
    char name[20]="Bob\0";
    char msg[100]="\0";

private:
    void init();
    void checkMouseOnTextbox();
    void handleKeyInput();
    void drawIntroScreen();
    void handleGameState();
    void drawChar();
    void drawTextBlink();
    void drawChatScreen();

private:
    Font font=LoadFont("Resources/font.ttf");
    int frameCounter=0;
    char emptyStr[100]="\0";
    int letterCount;
    Rectangle textBox;
    bool mouseText;
};
