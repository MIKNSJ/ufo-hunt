#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SAUCER_WIDTH 512
#define SAUCER_HEIGHT 512
#define WINDOW_TITLE "UFO Hunt"
#define FPS_CAP 60



// ========== SETUP ===========================================================
// ========== GAME ============================================================
typedef struct Game {
    Texture2D background;
    int backgroundPosX, backgroundPosY;
    Color backgroundColor;
    unsigned int lives, targetAmount, status;
    int score, maxScore;
    bool paused, gameOver;
} Game;


// Game Initialization
void gameConstructor(struct Game* game) {
    game->background = LoadTexture("../assets/game_background.png");
    game->backgroundPosX = 0;
    game->backgroundPosY = 0;
    game->backgroundColor = WHITE;
    game->lives = 20;
    game->score = 0;
    game->maxScore = 0;
    game->targetAmount = 0;
    game->status = 0;
    game->paused = false;
    game->gameOver = false;
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

// updates score based on quickness
void updateScore(struct Game* game, float remainingTime) {
    if (game->score < 1000000) {
        if (remainingTime >= 4.0) {
            game->score+=1000;
        } else if (remainingTime >= 3.0 && remainingTime < 4.0) {
            game->score+=800;
        } else if (remainingTime >= 2.0 && remainingTime < 3.0) {
            game->score+=600;
        } else if (remainingTime >= 1.0 && remainingTime < 2.0) {
            game->score+=400;
        } else if (remainingTime >= 0.5 && remainingTime < 1.0) {
            game->score+=200;
        } else if (remainingTime > 0 && remainingTime < 0.5) {
            game->score+=100;
        } else {
            game->score+=0;
        }
    }
}

// updates max score
void updateMaxScore(struct Game* game) {
    if (game->maxScore < game->score) {
        game->maxScore = game->score;
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
// ========== END OF CROSSHAIR ================================================



// ========== MENU ============================================================
typedef struct Menu {
    Texture2D background;
    const char* title;
    const char* play;
    Rectangle playBox;
    const char* exit;
    Rectangle exitBox;
    char topScore[18];
    const char* copyright;
    int backgroundPosX, backgroundPosY,
        titlePosX, titlePosY, titleSize,
        playPosX, playPosY, playSize,
        exitPosX, exitPosY, exitSize,
        topScorePosX, topScorePosY, topScoreSize,
        copyrightPosX, copyrightPosY, copyrightSize;
    Color titleColor, backgroundColor, playColor, playBoxColor, exitColor,
          exitBoxColor, topScoreColor, copyrightColor;
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
    
    //menu->topScore = "TOP SCORE:";
    strcpy(menu->topScore, "TOP SCORE: ");
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
        struct Crosshair* crosshair, Sound scroll, Sound fire) { 
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    if (*inputKey == KEY_W || *inputKey == KEY_D || *inputKey == KEY_UP) {
        if (menu->key == 1) {
            menu->key = 2;
        } else {
            menu->key = 1;
        }
        PlaySound(scroll);
    }
    if (*inputKey == KEY_S || *inputKey == KEY_A || *inputKey == KEY_DOWN) {
        if (menu->key == 1) {
            menu->key = 2;
        } else {
            menu->key = 1;
        }
        PlaySound(scroll);
    }

    if (CheckCollisionRecs(menu->playBox, crosshair->recticle) &&
            menu->key != 1) {
        menu->key = 1;
        PlaySound(scroll);
    } 

    if (CheckCollisionRecs(menu->exitBox, crosshair->recticle) &&
            menu->key != 2) {
        menu->key = 2;
        PlaySound(scroll);
    }
    
    if (menu->key == 2 && ((*inputKey == KEY_ENTER) || clicked)) {
        game->status = 1;
        PlaySound(fire);
    }

    if (menu->key == 1 && ((*inputKey == KEY_ENTER) || clicked)) {
        game->status = 2;
        PlaySound(fire);
    }
}

// updates the top score per game
void updateTopScore(struct Menu* menu, int maxScore) {
    char scoreText[18];
    sprintf(scoreText, "TOP SCORE: %d", maxScore);
    strcpy(menu->topScore, scoreText);
}
// ========== END OF MENU =====================================================



// ========= HUD ==============================================================
typedef struct HUD {
    Rectangle background;
    char* border;
    char lives[10];
    char speed[10];
    char upgrade[28];
    //char* score;
    char score[13];
    char *status;

    int backgroundPosX, backgroundPosY,
    borderPosX, borderPosY, borderSize,
    livesPosX, livesPosY, livesSize,
    speedPosX, speedPosY, speedSize,
    upgradePosX, upgradePosY, upgradeSize,
    scorePosX, scorePosY, scoreSize,
    statusPosX, statusPosY, statusSize;

    Color backgroundColor, borderColor, livesColor, speedColor, upgradeColor,
          scoreColor, statusColor;
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

    //hud->lives = "L = 100";
    strcpy(hud->lives, "L = 20");
    hud->livesPosX = 50;
    hud->livesPosY = 600;
    hud->livesSize = 30;
    hud->livesColor = WHITE;

    //hud->speed = "S = 1";
    strcpy(hud->speed, "S = 3");
    hud->speedPosX = 275;
    hud->speedPosY = 600;
    hud->speedSize = 30;
    hud->speedColor = WHITE;

    //hud->upgrade = "LEVEL UP UPGRADE IN = 0/10";
    strcpy(hud->upgrade, "LEVEL UP UPGRADE IN = 0/10");
    hud->upgradePosX = 475;
    hud->upgradePosY = 600;
    hud->upgradeSize = 30;
    hud->upgradeColor = WHITE;

    //hud->score = "000000\nSCORE";
    strcpy(hud->score, "000000\nSCORE");
    hud->scorePosX = 1100;
    hud->scorePosY = 600;
    hud->scoreSize = 30;
    hud->scoreColor = WHITE;

    hud->status = "[PAUSED]";
    hud->statusPosX = 525;
    hud->statusPosY = 200;
    hud->statusSize = 50;
    hud->statusColor = PINK;
}


// HUD Functions
// displays the game hud
void DrawHud(struct HUD* hud) {
    DrawRectangleRec(hud->background, hud->backgroundColor);
    DrawText(hud->border, hud->borderPosX, hud->borderPosY, hud->borderSize,
            hud->borderColor);
    DrawText(hud->lives, hud->livesPosX, hud->livesPosY, hud->livesSize,
            hud->livesColor);
    DrawText(hud->speed, hud->speedPosX, hud->speedPosY, hud->speedSize,
            hud->speedColor);
    DrawText(hud->upgrade, hud->upgradePosX, hud->upgradePosY,
            hud->upgradeSize, hud->upgradeColor);
    DrawText(hud->score, hud->scorePosX, hud->scorePosY, hud->scoreSize,
            hud->scoreColor);
}

// converts score to text
void scoreToText(struct HUD* hud, int score) {
   char strScore[13];

   if (score < 10) {
       sprintf(strScore, "00000%d\nSCORE", score);
   } else if (score >= 10 && score < 100) {
       sprintf(strScore, "0000%d\nSCORE", score);
   } else if (score >= 100 && score < 1000) {
       sprintf(strScore, "000%d\nSCORE", score);
   } else if (score >= 1000 && score < 10000) {
       sprintf(strScore, "00%d\nSCORE", score);
   } else if (score >= 10000 && score < 100000) {
       sprintf(strScore, "0%d\nSCORE", score);
   } else {
       sprintf(strScore, "%d\nSCORE", score);
   }

   strcpy(hud->score, strScore);
}

// updates level up indicator
void updateUpgrades(struct HUD* hud, int targetAmount) {
    char str[28];
    sprintf(str, "LEVEL UP UPGRADE IN = %d/10", targetAmount);
    strcpy(hud->upgrade, str);
}

// updates speed indicator
void updateSpeedDisplay(struct HUD* hud, double speed) {
    char str[10];
    sprintf(str, "S = %.2f", speed);
    strcpy(hud->speed, str);
}

// updates lives indicator
void updateLivesDisplay(struct HUD* hud, int lives) {
    char str[10];
    sprintf(str, "L = %d", lives);
    strcpy(hud->lives, str);
}
// ========== END OF HUD ======================================================



// ========== SPRITE ==========================================================
typedef struct Saucer {
    Texture2D sprite, deathMark;
    double spritePosX, spritePosY, spriteSpeedModifier, spriteDirectionX,
           spriteDirectionY, deathMarkPosX, deathMarkPosY;
    Rectangle hitbox, source, destination;
    Vector2 origin;
    float rotation;
    Color spriteColor, deathMarkColor;
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

    // death mark
    saucer->deathMark = LoadTexture("../assets/hitmarker.png");
    saucer->deathMark.width = 35;
    saucer->deathMark.height = 35;
    saucer->deathMarkPosX = saucer->spritePosX + 20;
    saucer->deathMarkPosY = saucer->spritePosY + 20;
    saucer->deathMarkColor = RED;
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
    saucer->hitbox.x = saucer->spritePosX;
    saucer->hitbox.y = saucer->spritePosY;
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

// Sprite Direction Normalization
void normalizeDirection(struct Saucer* saucer) {
    double magnitude = sqrt(pow(saucer->spriteDirectionX, 2.0) +
            pow(saucer->spriteDirectionY, 2.0));
    saucer->spriteDirectionX*=(1.0 / magnitude);
    saucer->spriteDirectionY*=(1.0 / magnitude);
}

// Sprite Death Mark
void updateDeathMark(struct Saucer* saucer) {
    saucer->deathMarkPosX = saucer->spritePosX + 20;
    saucer->deathMarkPosY = saucer->spritePosY + 20;
}
// ========== END OF SPRITE ===================================================



// ========== TIMER ===========================================================
typedef struct Timer {
    float spawnDelay, xMovementDelay, yMovementDelay, despawnDelay,
          roundDelay, scoreDelay, gameOverDelay;
    double currentTime;
} Timer;


// Timer Initialization
void timerConstructor(struct Timer* timer) {
    timer->spawnDelay = 3.0;
    timer->despawnDelay = 5.0;
    timer->xMovementDelay = 1;
    timer->yMovementDelay = 1;
    timer->roundDelay = 5;
    timer->gameOverDelay = 5.0;
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
    timer->despawnDelay = 5.0;
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
        timer->xMovementDelay = 1;
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
        timer->yMovementDelay = 1;
    }
}

// start gameOverDelay
void startGameOverDelay(struct Timer* timer) {
    if (timer->gameOverDelay >= 0) {
        timer->gameOverDelay-=timer->currentTime;
    }
}


// restart gameOverDelay
void restartGameOverDelay(struct Timer* timer) {
    if (timer->gameOverDelay <= 0) {
        timer->gameOverDelay = 5.0;
    }
}
// ========== END OF TIMER ====================================================



// ========= UNIVERSAL FUNCTIONS ==============================================
// resets to default statistics
void reset(struct Game* game, struct Saucer* saucer, struct HUD* hud,
        struct Timer* timer, struct Crosshair* crosshair) {
    game->status = 0;
    game->backgroundPosX = 0;
    game->backgroundPosY = 0;
    game->backgroundColor = WHITE;
    game->lives = 20;
    game->score = 0;
    game->targetAmount = 0;
    game->paused = false;

    strcpy(hud->lives, "L = 20");
    strcpy(hud->speed, "S = 3");
    strcpy(hud->upgrade, "LEVEL UP UPGRADE IN = 0/10");
    strcpy(hud->score, "000000\nSCORE");
    hud->status = "[PAUSED]";
    hud->statusPosX = 525;

    restartSpawnDelay(timer);
    restartDespawnDelay(timer);
    restartXMovementDelay(timer);
    restartYMovementDelay(timer);
    restartGameOverDelay(timer);
    resetSpriteSpawn(saucer);
    updateSpriteHitbox(saucer);
    updateDeathMark(saucer);
    saucer->spriteDirectionX = 1;
    saucer->spriteDirectionY = 1;
    crosshair->clickedUFO = false;
}
// ========= END OF UNIVERSAL FUNCTIONS =======================================
// ========== END OF SETUP ====================================================



int main(void) {
    // Window (Declaration and intialization)
    printf("[SYSTEM]: Setting up window...\n");
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(FPS_CAP);
    srand(time(NULL));
    printf("[SYSTEM]: Window setup complete.\n");

    // Audio
    InitAudioDevice();
    Sound bulletFired = LoadSound("../assets/m700-fire.wav");
    Sound explosion = LoadSound("../assets/explosion.wav");
    Sound menuScroll = LoadSound("../assets/sharp_echo.wav");
    Music menuTheme = LoadMusicStream("../assets/space_station.wav");
    SetMusicVolume(menuTheme, 1.0f);
    menuTheme.looping = true;
    Music gameTheme = LoadMusicStream("../assets/through_space.ogg");
    SetMusicVolume(gameTheme, 1.0f);
    gameTheme.looping = true;
    Music loseTheme = LoadMusicStream("../assets/lose_trumpet.wav");
    SetMusicVolume(loseTheme, 1.0f);
    Music current;

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
    current = menuTheme;
    PlayMusicStream(current);

    int inputKey;
    printf("[SYSTEM]: Game setup complete.\n");



    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // Update
        //---------------------------------------------------------------------
        UpdateMusicStream(current);

        if (game->status == 0 && !IsMusicStreamPlaying(menuTheme)) {
            StopMusicStream(gameTheme);
            current = menuTheme;
            PlayMusicStream(current);
        }

        if (game->status == 2 && !IsMusicStreamPlaying(gameTheme)) {
            StopMusicStream(menuTheme);
            current = gameTheme;
            PlayMusicStream(current);
        }
        //---------------------------------------------------------------------

        // Draw
        //---------------------------------------------------------------------
        BeginDrawing();

            if (game->status == 0) {
                ClearBackground(BLACK);
                reset(game, saucer, hud, timer, crosshair);
                inputKey = GetKeyPressed();
                eventMenuScroll(game, menu, &inputKey, crosshair, menuScroll,
                        bulletFired);
                eventMenuHighlight(menu);
                updateTopScore(menu, game->maxScore);
                DrawMenu(menu);
                updateCrosshairPosition(crosshair);
                DrawRectangleRec(crosshair->recticle, crosshair->reticleColor);
            } else if (game->status == 1) {
                break;
            } else {
                ClearBackground(BLACK);
                DrawTexture(game->background, game->backgroundPosX,
                        game->backgroundPosY, game->backgroundColor);
                inputKey = GetKeyPressed();
                eventGameOptions(game, &inputKey);
                DrawHud(hud);
                timer->currentTime = GetFrameTime();

                // Debug Print Statements
                //-------------------------------------------------------------
                //
                //-------------------------------------------------------------
                
                if (game->lives <= 0) {
                    game->gameOver = true;
                    game->paused = true;
                }

                if (game->gameOver && game->paused) {
                    hud->status = "[GAME OVER]";
                    hud->statusPosX = 500;
                    startGameOverDelay(timer);
                    StopMusicStream(gameTheme);
                    current = loseTheme;
                    PlayMusicStream(current);

                    if (timer->gameOverDelay <= 0) {
                        game->status = 0;
                        restartGameOverDelay(timer);
                        StopMusicStream(current);
                    }
                }

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                    CheckCollisionRecs(saucer->hitbox, crosshair->recticle) &&
                    game->paused == false) {
                    crosshair->clickedUFO = true;
                    PlaySound(bulletFired);
                    PlaySound(explosion);
                    DrawTexture(saucer->deathMark, saucer->deathMarkPosX,
                        saucer->deathMarkPosY, saucer->deathMarkColor);
                }

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                        !CheckCollisionRecs(saucer->hitbox,
                            crosshair->recticle) && game->paused == false) {
                    game->lives--;
                    updateLivesDisplay(hud, game->lives);
                    PlaySound(bulletFired);
                }

                if (crosshair->clickedUFO || timer->despawnDelay <= 0) {
                    if (crosshair->clickedUFO) {
                        game->targetAmount++;
                        updateUpgrades(hud, game->targetAmount);
                    }

                    if (timer->despawnDelay <= 0) {
                        game->lives--;
                        updateLivesDisplay(hud, game->lives);
                    }
                    
                    updateScore(game, timer->despawnDelay);
                    scoreToText(hud, game->score);
                    updateMaxScore(game);
                    restartSpawnDelay(timer);
                    restartDespawnDelay(timer);
                    restartXMovementDelay(timer);
                    restartYMovementDelay(timer);
                    resetSpriteSpawn(saucer);
                    updateSpriteHitbox(saucer);
                    updateDeathMark(saucer);
                    saucer->spriteDirectionX = 1;
                    saucer->spriteDirectionY = 1;
                    crosshair->clickedUFO = false;
                }

                if (game->targetAmount == 10) {
                    game->targetAmount = 0;
                    game->lives+=10;
                    updateLivesDisplay(hud, game->lives);
                    updateUpgrades(hud, game->targetAmount);
                    saucer->spriteSpeedModifier+=1.0;
                    updateSpeedDisplay(hud, saucer->spriteSpeedModifier);
                }

                if (game->paused == false) {
                    startSpawnDelay(timer);
                } else {
                    DrawText(hud->status, hud->statusPosX, hud->statusPosY,
                            hud->statusSize, hud->statusColor);
                    PauseMusicStream(gameTheme);
                }
                
                if (!crosshair->clickedUFO && timer->spawnDelay <= 0) {
                    DrawRectangleRec(saucer->hitbox, BLANK);
                    DrawTexture(saucer->sprite, saucer->spritePosX,
                            saucer->spritePosY, saucer->spriteColor);

                    if (game->paused == false) {
                        startDespawnDelay(timer);
                        startXMovementDelay(timer);
                        startYMovementDelay(timer);
                        
                        updateSpriteHitbox(saucer);
                        updateDeathMark(saucer);
                        checkSpriteBoundaries(saucer);
                        normalizeDirection(saucer);
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
                        DrawText(hud->status, hud->statusPosX, hud->statusPosY,
                            hud->statusSize, hud->statusColor);
                        PauseMusicStream(gameTheme);
                    }   
                }

                updateCrosshairPosition(crosshair);
                DrawRectangleRec(crosshair->recticle, crosshair->reticleColor);
            }

        EndDrawing();
        //---------------------------------------------------------------------
    }



    // De-Initialization
    //-------------------------------------------------------------------------
    UnloadTexture(saucer->sprite);
    UnloadTexture(menu->background);
    UnloadTexture(game->background);
    UnloadSound(bulletFired);
    UnloadSound(explosion);
    UnloadSound(menuScroll);
    UnloadMusicStream(menuTheme);
    UnloadMusicStream(gameTheme);
    UnloadMusicStream(loseTheme);
    CloseWindow();        // Close window and OpenGL context
    //-------------------------------------------------------------------------

    free(menu);
    free(hud);
    free(saucer);
    free(crosshair);
    free(game);
    free(timer);
    return 0;
}
