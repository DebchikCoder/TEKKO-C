#include "raylib.h"
#include "headers/Player.hpp"

int main(int, char**)
{
    InitWindow(800, 600, "PENIS");

    //magic numbers i love them!
    Player player("assets/Test.png", 3, 2, NUMtoSPEED(7.0f));

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLUE);
            player.Update();
        EndDrawing();
    }
    
    CloseWindow();

    return 0;
}
