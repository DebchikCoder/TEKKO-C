#include "raylib.h"
#include "headers/Player.hpp"

int main(int, char**)
{
    InitWindow(800, 600, "TEKKO");

    //magic numbers i love them!
    Player player("assets/Test.png", NUMtoUNIT(15), NUMtoUNIT(12), NUMtoUNIT(12));

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
