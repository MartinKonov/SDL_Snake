#include "Snake.h"


Snake::Snake()
{
    this->snakeHead.x = 500;
    this->snakeHead.y = 500;
    this->snakeHead.h = 10;
    this->snakeHead.w = 10;
    wholeSnake.push_front(snakeHead);
    this->size = 1;
}

void Snake::popBackSnake()
{
    wholeSnake.pop_back();
}

void Snake::pushFrontSnake(SDL_Rect toPush)
{
    wholeSnake.push_front(toPush);
}



SDL_Rect* Snake::getSnakeHead()
{
    return &this->snakeHead;
}

List<SDL_Rect> * Snake::getWholeSnake()
{
    return &this->wholeSnake;
}

int Snake::getSize()
{
    return this->size;
}

void Snake::incrSize()
{
    size += 10;
}

bool Snake::collisionWithBody()
{
    Node<SDL_Rect>* current = this->wholeSnake.getTail();

    while (current->next != nullptr)
    {
        if (current->data.x == this->snakeHead.x && current->data.y == this->snakeHead.y)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}


bool Snake::collisionWithApple(SDL_Rect currentApplePos)
{
    if (this->snakeHead.x == currentApplePos.x && this->snakeHead.y == currentApplePos.y)
        return true;

    return false;
}

bool Snake::collisionWithBorder()
{ 
    if (this->snakeHead.x > 1000 || this->snakeHead.x < 0 || this->snakeHead.y > 1000 || this->snakeHead.y < 0)
        return true;

    return false;
}


void Snake::moveHead()
{
    if (this->snakeHead.x != this->wholeSnake.gethead()->data.x || this->snakeHead.y != this->wholeSnake.gethead()->data.y)
        wholeSnake.push_front(snakeHead);

    while (this->wholeSnake.getSize() > this->size)
    {
        wholeSnake.pop_back();
    }

}