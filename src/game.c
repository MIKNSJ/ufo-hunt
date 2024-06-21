#include "raylib.h"



int main(void)
{
    // Initialization
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "resolution");
    SetWindowTitle("ufo-hunt");

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //---------------------------------------------------------------------
        // TODO: Update your variables here
        //---------------------------------------------------------------------

        // Draw
        //---------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("NEW LIFE UNBOUND", 190, 200, 20,
                    LIGHTGRAY);

        EndDrawing();
        //---------------------------------------------------------------------
    }

    // De-Initialization
    //-------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //-------------------------------------------------------------------------

    return 0;
}
