//#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include"Snake.h"
//#include "LinkedList.h"
using std::cerr;
using std::endl;

int WIN_WIGHT = 1000;
int WIN_HEIGHT = 1000;

enum LastMove
{
    UP,
    DOWN,
    LEFT,
    RIGHT,

};


SDL_Rect generateApplePosition(Snake &snake)
{
    std::vector<int> xForbidden;
    std::vector<int> yForbidden;

    Node<SDL_Rect>* current = snake.getWholeSnake()->getTail();
    while (current != nullptr)
    {
        xForbidden.push_back(current->data.x);
        yForbidden.push_back(current->data.y);
        current = current->next;

    }

    int applX, applY, applW, applH;

    applW = 10;
    applH = 10;

    bool flag = true;
    do 
    {
        applX = rand() % 100 * 10;
        applY = rand() % 100 * 10;

        for (int i = 0; i < xForbidden.size(); i++)
        {
            if (applX == xForbidden[i] || applY == yForbidden[i])
                   break;

            if (i == xForbidden.size() - 1)
                flag = false;
           
        }


    } while (flag);


    return { applX, applY, applW, applH };
}


void drawBody(SDL_Renderer* ren, Snake& snake)
{
    SDL_SetRenderDrawColor(ren, 212, 199, 131, 255);

    Node<SDL_Rect> *current = snake.getWholeSnake()->getTail();
    
    while (current->data.x != snake.getSnakeHead()->x || current->data.y != snake.getSnakeHead()->y)
    {
        SDL_RenderFillRect(ren, &current->data);
        current = current->next;
    }
}

int main(int argc, char* argv[])
{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_Window* win = SDL_CreateWindow("SnakeGame!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_HEIGHT, WIN_WIGHT, 0);
    if (win == nullptr) {
        cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
        return EXIT_FAILURE;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        cerr << "SDL_CreateRenderer Error" << SDL_GetError() << endl;
        if (win != nullptr) {
            SDL_DestroyWindow(win);
        }
        SDL_Quit();
        return EXIT_FAILURE;
    }

    int score = 0;

    bool running = true;

    SDL_Event event;

    Snake snake;

    bool appleExists = true;
    SDL_Rect applePos{ 50,50,10,10 };

    LastMove lastmove = RIGHT;

    int slowness = 200;

    Uint32 startTime = SDL_GetTicks();
    Uint32 currentTime = startTime;
    Uint32 previousTime = startTime;
    Uint32 time = 0;

    while (running)
    {
        //Input && move
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) { running = false; }

            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    if (lastmove == DOWN)
                        break;
                    lastmove = UP;
                    break;
                case SDLK_DOWN:
                    if (lastmove == UP)
                        break;
                    lastmove = DOWN;
                    break;
                case SDLK_LEFT:
                    if (lastmove == RIGHT)
                        break;
                    lastmove = LEFT;
                    break;
                case SDLK_RIGHT:
                    if (lastmove == LEFT)
                        break;
                    lastmove = RIGHT;
                    
                }
                //add collision with border
            }
        }
        switch (lastmove)
        {
        case UP:
            snake.getSnakeHead()->y -= 10;
            break;
        case DOWN:
            snake.getSnakeHead()->y += 10;
            break;
        case LEFT:
            snake.getSnakeHead()->x -= 10;
            break;
        case RIGHT:
            snake.getSnakeHead()->x += 10;
            break;
        }


        SDL_SetRenderDrawColor(ren, 19, 109, 21, 255);
        SDL_RenderClear(ren);


        //time
        char timerText[20];
        snprintf(timerText, sizeof(timerText), "Time: %u", time / 1000); // Convert milliseconds to seconds

        currentTime = SDL_GetTicks();
        time = currentTime - previousTime;
        previousTime = currentTime; 

        //SDL_Surface* textSurface = TTF_RenderText_Solid(font, timerText, textColor);



        //draw snakeHead
        SDL_SetRenderDrawColor(ren, 212, 199, 131, 255);
        SDL_RenderFillRect(ren, snake.getSnakeHead());

        

        //collision with apple
        if (snake.collisionWithApple(applePos))
        {
            snake.incrSize();
            if (slowness - 20 >= 40)
            {
                slowness -= 20;
            }
            appleExists = false;
        }

        if (!appleExists)
        {
            applePos = generateApplePosition(snake);
            appleExists = true;
        }
        
        
        SDL_SetRenderDrawColor(ren, 199, 55, 47, 255);
        SDL_RenderFillRect(ren, &applePos);

        if (snake.collisionWithBody())
        {
            //end screen
        }

        //move head
        snake.moveHead();

        //draw body
        drawBody(ren, snake);

        SDL_RenderPresent(ren);
        SDL_Delay(slowness);

    }


    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}