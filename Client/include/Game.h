#pragma once
#include <raylib.h>
#include <iostream>

class Game{
public:
    Game();

    void handleInput();
    void update();
    void draw();
    char str[100]="\0";

private:
    void init();
    void checkMouseOnTextbox();
    void handleKeyInput();
    void drawChar();
    void drawTextBlink();
    void drawChatScreen();

private:
    int frameCounter=0;
    char emptyStr[100]="\0";
    int letterCount;
    Rectangle textBox;
    bool mouseText;
};
