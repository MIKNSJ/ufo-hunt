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



// ========= HUD ==============================================================
typedef struct HUD {
    char* border;
    char* round;
    char* ammo;
    char* hit;
    char* score;

    int borderPosX, borderPosY, borderSize,
    roundPosX, roundPosY, roundSize,
    ammoPosX, ammoPosY, ammoSize,
    hitPosX, hitPosY, hitSize,
    scorePosX, scorePosY, scoreSize;

    Color borderColor;
    Color roundColor;
    Color ammoColor;
    Color hitColor;
    Color scoreColor;
} HUD; 


// HUD Initialization
void hudConstructor(struct HUD* hud) {
    hud->border = "===================================================";
    hud->borderPosX = 5;
    hud->borderPosY = 525;
    hud->borderSize = 50;
    hud->borderColor = RAYWHITE;

    hud->round = "R = 1";
    hud->roundPosX = 100;
    hud->roundPosY = 600;
    hud->roundSize = 30;
    hud->roundColor = RAYWHITE;

    hud->ammo = "[*][*][*]\nSHOT";
    hud->ammoPosX = 275;
    hud->ammoPosY = 600;
    hud->ammoSize = 30;
    hud->ammoColor = RAYWHITE;

    hud->hit = "HIT   [  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ]";
    hud->hitPosX = 475;
    hud->hitPosY = 600;
    hud->hitSize = 30;
    hud->hitColor = RAYWHITE;

    hud->score = "000000\nSCORE";
    hud->scorePosX = 1100;
    hud->scorePosY = 600;
    hud->scoreSize = 30;
    hud->scoreColor = RAYWHITE;
}

// HUD Functions
// displays the game hud
void DrawHud(struct HUD* hud) {
    DrawText(hud->border, hud->borderPosX, hud->borderPosY, hud->borderSize,
            hud->roundColor);
    DrawText(hud->round, hud->roundPosX, hud->roundPosY, hud->roundSize,
            hud->roundColor);
    DrawText(hud->ammo, hud->ammoPosX, hud->ammoPosY, hud->ammoSize,
            hud->ammoColor);
    DrawText(hud->hit, hud->hitPosX, hud->hitPosY, hud->hitSize,
            hud->hitColor);
    DrawText(hud->score, hud->scorePosX, hud->scorePosY, hud->scoreSize,
            hud->scoreColor);
}
// ========== END OF HUD ======================================================



// ========== SPRITE ==========================================================
typedef struct Saucer {
    Texture2D sprite;
    int spritePosX, spritePosY;
    Color spriteColor;
} Saucer;


// Sprite Initialization
void constructSprite(struct Saucer* saucer) {
    saucer->sprite = LoadTexture("../assets/saucer.png");
    saucer->spritePosX = 100;
    saucer->spritePosY = 100;
    saucer->spriteColor = WHITE;
}
// ========== END OF SPRITE ===================================================
// ========== END OF SETUP ====================================================



int main(void) {
    // ========== SETUP =======================================================
    // Window (Declaration and intialization)
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "resolution");
    SetWindowTitle("UFO Hunt");

    // Initialization
    Menu* menu = (Menu*)malloc(sizeof(Menu));
    menuConstructor(menu);
    HUD* hud = (HUD*)malloc(sizeof(HUD));
    hudConstructor(hud);
    Saucer* saucer = (Saucer*)malloc(sizeof(Saucer));
    constructSprite(saucer);

    unsigned int status = 0;
    unsigned int menuKey = 0;
    // =========== END OF SETUP ===============================================



    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // Update
        //---------------------------------------------------------------------
        // TODO: Update variables inside here.
        //---------------------------------------------------------------------

        // Draw
        //---------------------------------------------------------------------
        BeginDrawing();

            if (status == 0) {
                ClearBackground(BLACK);
                eventMenuScroll(&status, &menuKey, GetKeyPressed());
                eventMenuHighlight(menu, &menuKey);
                DrawMenu(menu);
            } else if (status == 1) {
                break;
            } else {
                ClearBackground(BLACK);
                eventGameOptions(&status, GetKeyPressed());
                DrawHud(hud);
                DrawTexture(saucer->sprite, saucer->spritePosX,
                        saucer->spritePosY, saucer->spriteColor);
            }

        EndDrawing();
        //---------------------------------------------------------------------
    }



    // De-Initialization
    //-------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //-------------------------------------------------------------------------

    free(menu);
    free(hud);
    return 0;
}
