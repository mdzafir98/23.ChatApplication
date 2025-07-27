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
    }else if(CheckCollisionPointRec(GetMousePosition(),textBox)==false && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        mouseText=false;
    }

    if(mouseText){
        frameCounter++;
    }else{
        frameCounter=0;
    }
}

void Game::handleKeyInput()
{
    // checking game state
    this->handleGameState();

    // typing text in the textbox
    if(mouseText){
        int key=GetCharPressed();
        while(key>0){
            if((key>=32) && (key<=125)){
                msg[letterCount]=char(key);
                msg[letterCount+1]='\0';
                letterCount++;
            }
            key=GetCharPressed();
        }
        if(IsKeyPressed(KEY_BACKSPACE)){
            letterCount--;
            if(letterCount<0){
                letterCount=0;
            }
            msg[letterCount]='\0';
        }
    }

    // text input packaged into data packet to be sent to server
    if(IsKeyPressed(KEY_ENTER) && mouseText){
        for(int i=0; i>letterCount; i++){
            msg[letterCount]='\0';
        }
        strcat(data,name);
        strcat(data,msg);
        std::cout<<"Sending message to server."<<"\n";
    }
}

void Game::drawIntroScreen()
{
    DrawTextEx(font,"Press E to start application",{200.f,200.f},50,1.0,RAYWHITE);
}

void Game::drawChar()
{
    DrawTextEx(font,msg,{(float)textBox.x+5,(float)textBox.y+5},18,1.0,RAYWHITE);
    // DrawText(str,(int)textBox.x+5,(int)textBox.y+5,18,RAYWHITE);
}

void Game::drawTextBlink()
{
    if((frameCounter/20)%2==0){
        DrawText("|",(int)textBox.x+5+MeasureText(msg,18),(int)textBox.y+6,18,RAYWHITE);
    }
}

void Game::handleGameState()
{
    if(gameState==STATE_INTRO && IsKeyPressed(KEY_E)){
        gameState=STATE_MSG_LOOP;
    }
}

