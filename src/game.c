#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SAUCER_WIDTH 512
#define SAUCER_HEIGHT 512
#define WINDOW_TITLE "UFO Hunt"
#define FPS_CAP 60
#define PAUSE "[PAUSED]"
#define PAUSE_POS_X 525
#define PAUSE_POS_Y 200
#define PAUSE_SIZE 50
#define PAUSE_COLOR PINK


// ========== SETUP ===========================================================
// ========== GAME ============================================================
typedef struct Game {
    Texture2D background;
    int backgroundPosX, backgroundPosY;
    Color backgroundColor;
    unsigned int round;
    unsigned int requiredHits;
    unsigned int ammoRemaining;
    unsigned int status;
    bool paused;
} Game;


// Game Initialization
void gameConstructor(struct Game* game) {
    game->background = LoadTexture("../assets/game_background.png");
    game->backgroundPosX = 0;
    game->backgroundPosY = 0;
    game->backgroundColor = WHITE;
    game->round = 0;
    game->requiredHits = 10;
    game->ammoRemaining = 3;
    game->status = 0;
    game->paused = false;
}


// GAME FUNCTIONS
// selects the game options
void eventGameOptions(struct Game* game, int *inputKey) {
    // return to menu
    if (*inputKey == KEY_M) {
        game->status = 0;
    }
    
    // toggle game pause
    if (*inputKey == KEY_P) {
        if (game->paused == false) {
            game->paused = true;
            printf("[SYSTEM]: The game has been paused.\n");
        } else {
            game->paused = false;
            printf("[SYSTEM]: The game has been unpaused.\n");
        }
    }
}
// ========= END OF GAME ======================================================



// ========== CROSSHAIR =======================================================
typedef struct Crosshair {
    Rectangle recticle;
    Color reticleColor;
    bool clickedUFO;
} Crosshair;


// Crosshair Initialization
void crosshairConstructor(struct Crosshair* crosshair) {
    crosshair->recticle = (Rectangle){0, 0, 1, 1};
    crosshair->reticleColor = BLANK;
    crosshair->clickedUFO = false;
}


// Crosshair Functions
// Update Crosshair position
void updateCrosshairPosition(struct Crosshair* crosshair) {
    crosshair->recticle.x = GetMousePosition().x;
    crosshair->recticle.y = GetMousePosition().y;
}



// ========== MENU ============================================================
typedef struct Menu {
    Texture2D background;
    const char* title;
    const char* play;
    Rectangle playBox;
    const char* exit;
    Rectangle exitBox;
    char* topScore;
    const char* copyright;
    int backgroundPosX, backgroundPosY,
        titlePosX, titlePosY, titleSize,
        playPosX, playPosY, playSize,
        exitPosX, exitPosY, exitSize,
        topScorePosX, topScorePosY, topScoreSize,
        copyrightPosX, copyrightPosY, copyrightSize;
    Color titleColor;
    Color backgroundColor;
    Color playColor;
    Color playBoxColor;
    Color exitColor;
    Color exitBoxColor;
    Color topScoreColor;
    Color copyrightColor;
    unsigned int key;
} Menu;


// MENU INITIALIZATION
void menuConstructor(struct Menu* menu) {
    menu->background = LoadTexture("../assets/menu_background.png");
    menu->backgroundPosX = 0;
    menu->backgroundPosY = 0;
    menu->backgroundColor = WHITE;

    menu->title = "UFO Hunt";
    menu->titlePosX = 175;
    menu->titlePosY = 25;
    menu->titleSize = 200;
    menu->titleColor = GREEN;
    
    menu->play = "PLAY";
    menu->playPosX = 550;
    menu->playPosY = 400;
    menu->playSize = 50;
    menu->playColor = GREEN;

    menu->playBox.x = 540;
    menu->playBox.y = 400;
    menu->playBox.width = 150;
    menu->playBox.height = 50;
    menu->playBoxColor = BLANK;
    
    menu->exit = "EXIT";
    menu->exitPosX = 550;
    menu->exitPosY = 500;
    menu->exitSize = 50;
    menu->exitColor = GREEN;

    menu->exitBox.x = 540;
    menu->exitBox.y = 500;
    menu->exitBox.width = 150;
    menu->exitBox.height = 50;
    menu->exitBoxColor = BLANK;
    
    menu->topScore = "TOP SCORE:";
    menu->topScorePosX = 475;
    menu->topScorePosY = 600;
    menu->topScoreSize = 25;
    menu->topScoreColor = GREEN;
    
    menu->copyright= "@2024 MADE BY MIKNSJ.";
    menu->copyrightPosX = 475;
    menu->copyrightPosY = 650;
    menu->copyrightSize = 25;
    menu->copyrightColor = GREEN;

    menu->key = 0;
}


// MENU FUNCTIONS
// draws the menu
void DrawMenu(struct Menu* menu) {
    DrawTexture(menu->background, menu->backgroundPosX, menu->backgroundPosY,
            menu->backgroundColor);
    DrawText(menu->title, menu->titlePosX, menu->titlePosY,
            menu->titleSize, menu->titleColor);
    DrawRectangleRec(menu->playBox, menu->playBoxColor);
    DrawText(menu->play, menu->playPosX, menu->playPosY,
            menu->playSize, menu->playColor);
    DrawRectangleRec(menu->exitBox, menu->exitBoxColor);
    DrawText(menu->exit, menu->exitPosX, menu->exitPosY,
            menu->exitSize, menu->exitColor);
    DrawText(menu->topScore, menu->topScorePosX, menu->topScorePosY,
            menu->topScoreSize, menu->topScoreColor);
    DrawText(menu->copyright, menu->copyrightPosX, menu->copyrightPosY,
            menu->copyrightSize, menu->copyrightColor);
}


// highlights the menu options
void eventMenuHighlight(struct Menu* menu) {
    unsigned int key = menu->key;
    switch (key) {
        case 1:
            menu->playColor = RED;
            menu->exitColor = GREEN;
            break;
        case 2:
            menu->exitColor = RED;
            menu->playColor = GREEN;
            break;
        default:
            break;
    }
}


// navigates the menu options
void eventMenuScroll(struct Game* game, struct Menu* menu, int *inputKey,
        struct Crosshair* crosshair) { 
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (*inputKey == KEY_W || *inputKey == KEY_UP) {
        if (menu->key == 1) {
            menu->key = 2;
        } else {
            menu->key = 1;
        }
    }
    if (*inputKey == KEY_S || *inputKey == KEY_DOWN) {
        if (menu->key == 1) {
            menu->key = 2;
        } else {
            menu->key = 1;
        }
    }

    if (CheckCollisionRecs(menu->playBox, crosshair->recticle)) {
        menu->key = 1;
    } 

    if (CheckCollisionRecs(menu->exitBox, crosshair->recticle)) {
        menu->key = 2;
    }
    
    if (menu->key == 2 && ((*inputKey == KEY_ENTER) || clicked)) {
        game->status = 1;
    }

    if (menu->key == 1 && ((*inputKey == KEY_ENTER) || clicked)) {
        game->status = 2;
    }
}
// ========== END OF MENU =====================================================



// ========= HUD ==============================================================
typedef struct HUD {
    Rectangle background;
    char* border;
    char* round;
    char* ammo;
    char* hit;
    char* score;

    int backgroundPosX, backgroundPosY,
    borderPosX, borderPosY, borderSize,
    roundPosX, roundPosY, roundSize,
    ammoPosX, ammoPosY, ammoSize,
    hitPosX, hitPosY, hitSize,
    scorePosX, scorePosY, scoreSize;

    Color backgroundColor;
    Color borderColor;
    Color roundColor;
    Color ammoColor;
    Color hitColor;
    Color scoreColor;
} HUD; 


// HUD Initialization
void hudConstructor(struct HUD* hud) {
    hud->background.width = 1280;
    hud->background.height = 195;
    hud->background.x = 0;
    hud->background.y = 535;
    hud->backgroundColor = BLACK;

    hud->border = "===================================================";
    hud->borderPosX = 5;
    hud->borderPosY = 525;
    hud->borderSize = 50;
    hud->borderColor = WHITE;

    hud->round = "R = 1";
    hud->roundPosX = 100;
    hud->roundPosY = 600;
    hud->roundSize = 30;
    hud->roundColor = WHITE;

    hud->ammo = "[*][*][*]\nSHOT";
    hud->ammoPosX = 275;
    hud->ammoPosY = 600;
    hud->ammoSize = 30;
    hud->ammoColor = WHITE;

    hud->hit = "HIT   [  ][  ][  ][  ][  ][  ][  ][  ][  ][  ][  ]";
    hud->hitPosX = 475;
    hud->hitPosY = 600;
    hud->hitSize = 30;
    hud->hitColor = WHITE;

    hud->score = "000000\nSCORE";
    hud->scorePosX = 1100;
    hud->scorePosY = 600;
    hud->scoreSize = 30;
    hud->scoreColor = WHITE;
}


// HUD Functions
// displays the game hud
void DrawHud(struct HUD* hud) {
    DrawRectangleRec(hud->background, hud->backgroundColor);
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
    double spritePosX, spritePosY, spriteSpeedModifier, spriteDirectionX,
           spriteDirectionY;
    Rectangle hitbox;
    Rectangle source;
    Rectangle destination;
    Vector2 origin;
    float rotation;
    Color spriteColor;
} Saucer;


// Sprite Initialization
void spriteConstructor(struct Saucer* saucer) {
    saucer->sprite = LoadTexture("../assets/saucer.png");
    saucer->sprite.width = 75;
    saucer->sprite.height = 75;
    saucer->spriteSpeedModifier = 3;
    saucer->spriteDirectionX = 1;
    saucer->spriteDirectionY = 1;
    saucer->hitbox = (Rectangle){0, 0, 75, 75};
    
    // DrawTexture
    saucer->spritePosX = rand() % 1280;
    saucer->spritePosY = 460;

    // DrawTexturePro
    saucer->source = (Rectangle){0, 0, SAUCER_WIDTH, SAUCER_HEIGHT};
    saucer->destination = (Rectangle){0, 0, 75, 75};
    saucer->origin = (Vector2){0, 0};
    saucer->rotation = 0;
    saucer->spriteColor = WHITE;
}


// Sprite Functions
// Sprite Movement
void move(struct Saucer* saucer, double offSetX, double offSetY) {
    saucer->spritePosX+=offSetX;
    saucer->spritePosY-=offSetY;
}

// Sprite Boundaries
void checkSpriteBoundaries(struct Saucer* saucer) {
    if (saucer->spritePosX < 0) {
        saucer->spritePosX = 0;

        if (saucer->spriteDirectionX < 0) {
            saucer->spriteDirectionX*=-1;
        }
    }

    if (saucer->spritePosX > 1200) {
        saucer->spritePosX = 1200;

        if (saucer->spriteDirectionX > 0) {
            saucer->spriteDirectionX*=-1;
        }
    }

    if (saucer->spritePosY < 0) {
        saucer->spritePosY = 0;

        if (saucer->spriteDirectionY > 0) {
            saucer->spriteDirectionY*=-1;
        }
    }

    if (saucer->spritePosY > 460) {
        saucer->spritePosY = 460;

        if (saucer->spriteDirectionY < 0) {
            saucer->spriteDirectionY*=-1;
        }
    }
}

// Sprite Hitbox
void updateSpriteHitbox(struct Saucer* saucer) {
    saucer->hitbox.x = (saucer->spritePosX);
    saucer->hitbox.y = (saucer->spritePosY);
}

// Sprite Spawn Point
void resetSpriteSpawn(struct Saucer* saucer) {
    saucer->spritePosX = rand() % 1280;
    saucer->spritePosY = 460;
}

// Sprite X Direction
void resetSpriteXDirection(struct Saucer* saucer) {
    int angle = rand();
    double orientation = cos(angle);
    saucer->spriteDirectionX = orientation;
}

// Sprite Y Direction
void resetSpriteYDirection(struct Saucer* saucer) {
    int angle = rand();
    double orientation = sin(angle);
    saucer->spriteDirectionY = orientation;
}
// ========== END OF SPRITE ===================================================



// ========== TIMER ===========================================================
typedef struct Timer {
    float spawnDelay;
    float xMovementDelay;
    float yMovementDelay;
    float despawnDelay;
    float roundDelay;
    double currentTime;
} Timer;


// Timer Initialization
void timerConstructor(struct Timer* timer) {
    timer->spawnDelay = 3.0;
    timer->despawnDelay = 8.0;
    timer->xMovementDelay = 1;
    timer->yMovementDelay = 1;
    timer->roundDelay = 5;
    timer->currentTime = 0;
}


// Timer Functions
// start spawnDelay timer
void startSpawnDelay(struct Timer* timer) {
    if (timer->spawnDelay >= 0) {
        timer->spawnDelay-=timer->currentTime;
    }
}

// restart spawnDelay timer
void restartSpawnDelay(struct Timer* timer) {
    if (timer->spawnDelay <= 0) {
        timer->spawnDelay = 3.0;
    }
}


// start despawnTime timer
void startDespawnDelay(struct Timer* timer) {
    if (timer->despawnDelay >= 0) {
        timer->despawnDelay-=timer->currentTime;
    }
}

// restart despawnTime timer
void restartDespawnDelay(struct Timer* timer) {
    if (timer->despawnDelay <= 0) {
        timer->despawnDelay = 8.0;
    }
}

// start xMovementDelay
void startXMovementDelay(struct Timer* timer) {
    if (timer->xMovementDelay >= 0) {
        timer->xMovementDelay-=timer->currentTime;
    }
} 

// restart xMovementDelay
void restartXMovementDelay(struct Timer* timer) {
    if (timer->xMovementDelay <= 0) {
        timer->xMovementDelay = 2;
    }
} 

// start yMovementDelay
void startYMovementDelay(struct Timer* timer) {
    if (timer->yMovementDelay >= 0) {
        timer->yMovementDelay-=timer->currentTime;
    }
} 

// restart yMovementDelay
void restartYMovementDelay(struct Timer* timer) {
    if (timer->yMovementDelay <= 0) {
        timer->yMovementDelay = 2;
    }
} 
// ========== END OF TIMER ====================================================
// ========== END OF SETUP ====================================================



int main(void) {
    // ========== SETUP =======================================================
    // Window (Declaration and intialization)
    printf("[SYSTEM]: Setting up window...\n");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(FPS_CAP);
    srand(time(NULL));
    printf("[SYSTEM]: Window setup complete.\n");

    // Initialization
    printf("[SYSTEM]: Setting up game elements...\n");
    Menu* menu = (Menu*)malloc(sizeof(Menu));
    menuConstructor(menu);
    HUD* hud = (HUD*)malloc(sizeof(HUD));
    hudConstructor(hud);
    Saucer* saucer = (Saucer*)malloc(sizeof(Saucer));
    spriteConstructor(saucer);
    Crosshair* crosshair = (Crosshair*)malloc(sizeof(Crosshair));
    crosshairConstructor(crosshair);
    Game* game = (Game*)malloc(sizeof(Game));
    gameConstructor(game);
    Timer* timer = (Timer*)malloc(sizeof(Timer));
    timerConstructor(timer);

    int inputKey;
    printf("[SYSTEM]: Game setup complete.\n");
    // =========== END OF SETUP ===============================================



    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // Update
        //---------------------------------------------------------------------

        //---------------------------------------------------------------------

        // Draw
        //---------------------------------------------------------------------
        BeginDrawing();

            if (game->status == 0) {
                //printf("[SYSTEM]: The menu is now queued.\n");
                ClearBackground(BLACK);
                inputKey = GetKeyPressed();
                eventMenuScroll(game, menu, &inputKey, crosshair);
                eventMenuHighlight(menu);
                DrawMenu(menu);
                updateCrosshairPosition(crosshair);
                DrawRectangleRec(crosshair->recticle, crosshair->reticleColor);
                //printf("[SYSTEM]: The menu is now generated.\n");
            } else if (game->status == 1) {
                //printf("[SYSTEM]: Enabled early exit of program.\n");
                break;
            } else {
                //printf("[SYSTEM]: Currently in-game.\n");
                ClearBackground(BLACK);
                DrawTexture(game->background, game->backgroundPosX,
                        game->backgroundPosY, game->backgroundColor);
                inputKey = GetKeyPressed();
                eventGameOptions(game, &inputKey);
                DrawHud(hud);

                // Debug Print Statements
                //-------------------------------------------------------------
                //
                //-------------------------------------------------------------

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                    CheckCollisionRecs(saucer->hitbox, crosshair->recticle) &&
                    game->paused == false) {
                    crosshair->clickedUFO = true;
                }

                if (game->paused == false) {
                    startSpawnDelay(timer);
                    startDespawnDelay(timer);
                    startXMovementDelay(timer);
                    startYMovementDelay(timer);
                    timer->currentTime = GetFrameTime();
                } else {
                    DrawText(PAUSE, PAUSE_POS_X, PAUSE_POS_Y, PAUSE_SIZE,
                            PINK);
                }
                
                if (!crosshair->clickedUFO && timer->spawnDelay <= 0) {
                    DrawRectangleRec(saucer->hitbox, BLANK);
                    DrawTexture(saucer->sprite, saucer->spritePosX,
                            saucer->spritePosY, saucer->spriteColor);

                    if (game->paused == false) {
                        updateSpriteHitbox(saucer);
                        checkSpriteBoundaries(saucer);
                        move(saucer, saucer->spriteSpeedModifier *
                                saucer->spriteDirectionX,
                                saucer->spriteSpeedModifier *
                                saucer->spriteDirectionY);

                        if (timer->xMovementDelay <= 0) {
                            resetSpriteXDirection(saucer);
                            restartXMovementDelay(timer);
                        }

                        if (timer->yMovementDelay <= 0) {
                            resetSpriteYDirection(saucer);
                            restartYMovementDelay(timer);
                        }
                    } else {
                        DrawText(PAUSE, PAUSE_POS_X, PAUSE_POS_Y, PAUSE_SIZE,
                            PINK);
                    }   
                }

                if (crosshair->clickedUFO || timer->despawnDelay <= 0) {
                    restartSpawnDelay(timer);
                    restartDespawnDelay(timer);
                    resetSpriteSpawn(saucer);
                    restartXMovementDelay(timer);
                    restartYMovementDelay(timer);
                    saucer->spriteDirectionX = 1;
                    saucer->spriteDirectionY = 1;
                    crosshair->clickedUFO = false;
                }

                updateCrosshairPosition(crosshair);
                DrawRectangleRec(crosshair->recticle, crosshair->reticleColor);
            }

        EndDrawing();
        //---------------------------------------------------------------------
    }



    // De-Initialization
    //-------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //-------------------------------------------------------------------------

    printf("[SYSTEM]: The window has been closed.\n");
    free(menu);
    free(hud);
    free(saucer);
    free(crosshair);
    free(game);
    free(timer);
    printf("[SYSTEM]: The program has been terminated successfully.\n");
    return 0;
}
