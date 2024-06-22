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
    menu->titlePosX = 175;
    menu->titlePosY = 25;
    menu->titleSize = 200;
    menu->titleColor = WHITE;
    
    menu->play = "PLAY";
    menu->playPosX = 550;
    menu->playPosY = 400;
    menu->playSize = 50;
    menu->playColor = WHITE;
    
    menu->exit = "EXIT";
    menu->exitPosX = 550;
    menu->exitPosY = 500;
    menu->exitSize = 50;
    menu->exitColor = WHITE;
    
    menu->topScore = "TOP SCORE:";
    menu->topScorePosX = 475;
    menu->topScorePosY = 600;
    menu->topScoreSize = 25;
    menu->topScoreColor = WHITE;
    
    menu->copyright= "@2024 MADE BY MIKNSJ.";
    menu->copyrightPosX = 475;
    menu->copyrightPosY = 650;
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
void eventMenuHighlight(struct Menu* menu, unsigned int* menuKey) {
    switch (*menuKey) {
        case 1:
            menu->playColor = RED;
            menu->exitColor = WHITE;
            break;
        case 2:
            menu->exitColor = RED;
            menu->playColor = WHITE;
            break;
        default:
            break;
    }
}


// navigates the menu options
void eventMenuScroll(unsigned int* status, unsigned int* menuKey,
        int inputKey) { 
    if (inputKey == KEY_W || inputKey == KEY_UP) {
        if (*menuKey == 1) {
            *menuKey = 2;
        } else {
            *menuKey = 1;
        }
    }
    if (inputKey == KEY_S || inputKey == KEY_DOWN) {
        if (*menuKey == 1) {
            *menuKey = 2;
        } else {
            *menuKey = 1;
        }
    }
    
    if (*menuKey == 2 && (inputKey == KEY_ENTER)) {
        *status = 1;
    }

    if (*menuKey == 1 && (inputKey == KEY_ENTER)) {
        *status = 2;
    }
}
// ========== END OF MENU =====================================================



// ========== GAME ============================================================
// ========== GAME FUNCTIONS ==================================================
// selects the game options
void eventGameOptions(unsigned int* status, int inputKey) {
    if (inputKey == KEY_M) {
        *status = 0;
    }
}
// ========= END OF GAME ======================================================

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
    unsigned int menuKey = 0;
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
                ClearBackground(BLACK);
                eventMenuScroll(&status, &menuKey, GetKeyPressed());
                eventMenuHighlight(menu, &menuKey);
                DrawMenu(menu);
            } else if (status == 1) {
                break;
            } else {
                ClearBackground(RAYWHITE);
                eventGameOptions(&status, GetKeyPressed());
                DrawText("To the game", 100, 100, 50, BLACK);
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
