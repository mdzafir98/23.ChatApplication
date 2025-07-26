#include "../include/Game.h"

Game::Game()
{
    this->init();
    std::cout<<"Game instance created.\n";
}

void Game::handleInput()
{
    this->handleKeyInput();
}

void Game::update()
{
    this->checkMouseOnTextbox();
}

void Game::draw()
{
    DrawRectangleLinesEx(textBox,2.f,RAYWHITE);
    // DrawRectangleRec(textBox,DARKGRAY);
    this->drawChar();
    this->drawTextBlink();
}

// PRIVATE
void Game::init()
{
    letterCount=0;
    textBox={25.f,GetScreenHeight()-50.f,400,30};
    mouseText={false};
}

void Game::checkMouseOnTextbox()
{
    if(CheckCollisionPointRec(GetMousePosition(),textBox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        mouseText=true;
    }

    if(mouseText){
        frameCounter++;
    }else{
        frameCounter=0;
    }
}

void Game::handleKeyInput()
{
    if(mouseText){
        int key=GetCharPressed();
        while(key>0){
            if((key>=32) && (key<=125)){
                str[letterCount]=char(key);
                str[letterCount+1]='\0';
                letterCount++;
            }
            key=GetCharPressed();
        }
        if(IsKeyPressed(KEY_BACKSPACE)){
            letterCount--;
            if(letterCount<0){
                letterCount=0;
            }
            str[letterCount]='\0';
        }
    }

    if(IsKeyPressed(KEY_ENTER)){
        for(int i=0; i>letterCount; i++){
            str[letterCount]='\0';
        }
        std::cout<<"Sent message to server."<<"\n";
    }
}

void Game::drawChar()
{
    DrawText(str,(int)textBox.x+5,(int)textBox.y+5,18,RAYWHITE);
}

void Game::drawTextBlink()
{
    if((frameCounter/20)%2==0){
        DrawText("|",(int)textBox.x+5+MeasureText(str,18),(int)textBox.y+6,18,RAYWHITE);
    }
}

