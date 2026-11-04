#include "raylib.h"
#include "headers/Game.hpp"

int main(int, char**)
{
    InitWindow(800, 600, "TEKKO");

    Game game;
    game.Start();

    while (!WindowShouldClose())
    {
        game.Update();
    }
    
    CloseWindow();

    return 0;
}
