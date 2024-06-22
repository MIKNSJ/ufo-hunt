#include "raylib.h"
#include <stdlib.h>


// ========== SETUP ===========================================================
// ========== MENU ============================================================
typedef struct Menu {
    const char* title;
    const char* play;
    const char* exit;
    char* topScore;
    const char* copyright;
    int titlePosX, titlePosY, titleSize,
        playPosX, playPosY, playSize,
        exitPosX, exitPosY, exitSize,
        topScorePosX, topScorePosY, topScoreSize,
        copyrightPosX, copyrightPosY, copyrightSize;
    Color titleColor;
    Color playColor;
    Color exitColor;
    Color topScoreColor;
    Color copyrightColor;
} Menu;

// MENU INITIALIZATION
void menuConstructor(struct Menu* menu) {
    menu->title = "UFO Hunt";
    menu->titlePosX = 500;
    menu->titlePosY = 100;
    menu->titleSize = 50;
    menu->titleColor = WHITE;
    
    menu->play = "PLAY";
    menu->playPosX = 500;
    menu->playPosY = 200;
    menu->playSize = 25;
    menu->playColor = WHITE;
    
    menu->exit = "EXIT";
    menu->exitPosX = 500;
    menu->exitPosY = 225;
    menu->exitSize = 25;
    menu->exitColor = WHITE;
    
    menu->topScore = "TOP SCORE:";
    menu->topScorePosX = 500;
    menu->topScorePosY = 275;
    menu->topScoreSize = 25;
    menu->topScoreColor = WHITE;
    
    menu->copyright= "@2024 MADE BY MIKNSJ.";
    menu->copyrightPosX = 500;
    menu->copyrightPosY = 300;
    menu->copyrightSize = 25;
    menu->copyrightColor = WHITE;
}

// MENU FUNCTIONS
// draws the menu
void DrawMenu(struct Menu* menu) {
    DrawText(menu->title, menu->titlePosX, menu->titlePosY,
            menu->titleSize, menu->titleColor);
    DrawText(menu->play, menu->playPosX, menu->playPosY,
            menu->playSize, menu->playColor);
    DrawText(menu->exit, menu->exitPosX, menu->exitPosY,
            menu->exitSize, menu->exitColor);
    DrawText(menu->topScore, menu->topScorePosX, menu->topScorePosY,
            menu->topScoreSize, menu->topScoreColor);
    DrawText(menu->copyright, menu->copyrightPosX, menu->copyrightPosY,
            menu->copyrightSize, menu->copyrightColor);
}

// highlights the menu options
void eventMenuHighlight(struct Menu* menu, int menuKey) {
    switch (menuKey) {
        case 0:
            menu->playColor = RED;
            menu->exitColor = WHITE;
            break;
        case 1:
            menu->exitColor = RED;
            menu->playColor = WHITE;
            break;
        default:
            break;
    }
}
// ========== END OF MENU =====================================================

// ========== END OF SETUP ====================================================



int main(void)
{
    // ========== SETUP =======================================================
    // Window (Declaration and intialization)
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "resolution");
    SetWindowTitle("UFO Hunt");

    // Initialization
    Menu *menu = (Menu*)malloc(sizeof(Menu));
    menuConstructor(menu);

    unsigned int status = 0;
    int menuKey = -1;

    // =========== END OF SETUP ===============================================

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //---------------------------------------------------------------------
        // TODO: Update variables inside here.
        //---------------------------------------------------------------------

        // Draw
        //---------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            if (status == 0) {
                if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
                    if (menuKey == 0) {
                        menuKey = 1;
                    } else {
                        menuKey = 0;
                    }
                }

                if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
                    if (menuKey == 0) {
                        menuKey = 1;
                    } else {
                        menuKey = 0;
                    }
                }

                if (menuKey == 0 && IsKeyPressed(KEY_ENTER)) {
                    status = 1;
                }

                if (menuKey == 1 && IsKeyPressed(KEY_ENTER)) {
                    break;
                }

                eventMenuHighlight(menu, menuKey);
                DrawMenu(menu);
            } else {
                DrawText("To the game", 100, 100, 50, WHITE);
                //draw game
            }

        EndDrawing();
        //---------------------------------------------------------------------
    }

    // De-Initialization
    //-------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //-------------------------------------------------------------------------

    free(menu);
    return 0;
}
