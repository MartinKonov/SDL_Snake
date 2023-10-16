#pragma once
#include "LinkedList.h"
#include <SDL.h>

class Snake
{
    SDL_Rect snakeHead;
    List<SDL_Rect> wholeSnake;
    int size;

public:
    Snake();

    void popBackSnake();

    void pushFrontSnake(SDL_Rect toPush);

    SDL_Rect* getSnakeHead();

    List<SDL_Rect>* getWholeSnake();

    int getSize();

    void incrSize();

    bool collisionWithBody();

    bool collisionWithApple(SDL_Rect currentApplePos);

    bool collisionWithBorder();

    void moveHead();
    
};