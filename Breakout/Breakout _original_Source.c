#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdio.h> 
#include <stdlib.h>
#include "SDL_mixer.h"

// Player Variables //

int life = 3;
int playerScore = 0;
int level = 1;
int bricksAlive = 130;

// Power up variables //

int r; // Random number
bool laserOn = true;
bool bonusballOn = false;

// Functions //

void BallLogic();
void KeyboardControls();
void PaddleCollision();
void BallMotion();
void ScoreRender();
void LevelText();
void LifeText();
void ExtraBall();
void LaserBeam();
void BrickRenders();
void LoadTextures();

// Collision Detection //

/*source based on Luka Horvat: ~ https://pastebin.com/jqnGJRfR */

bool checkCollision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh)
{
    if (Ay + Ah < By) return false;
    else if (Ay > By + Bh) return false;
    else if (Ax + Aw < Bx) return false;
    else if (Ax > Bx + Bw) return false;

    return true;
}

/*source based on Luka Horvat ends here */

// Brick Structure //

struct Brick01
{

    int brickposX;
    int brickposY;
    int brickX;
    int brickY;
    bool alive;
};

// Brick Elements //

const int BRICKS01 = 130; // Number of bricks 
const int BRICKS02 = 126;
const int BRICKS03 = 126;

int brickStructure;

// Paddle Variables //

const float SPEED = 0.2f; // Speed of paddle

float paddlex = 360.0f; // X Start position
float paddley = 570.0f; // Y Start position

int paddleWidth = 80; // Paddle width
int paddleHeight = 18; // Paddle height

// Ball variables //

float ballX = 440.0f; // X start position
float ballY = 570.0f; // Y start position
const int ballWH = 14; // Width and height

float vellX = -0.03f; // Ball X speed
float vellY = -0.08f; // Ball Y speed

bool ballMotion = false;

// Extra ball variables //

float ballX2 = 400; // X start position
float ballY2 = 550; // Y start position
const int ballWH2 = 24; // Width and height

float vellX2 = 0.03f; // Ball X speed
float vellY2 = 0.06f; // Ball Y speed

bool ballMotion2 = false;

// Laser Variables //

float laserX = 400.0f; // X start position
float laserY = 550.0f; // Y start position

int laserH = 40; // Height of laser
int laserW = 4;  // Width of laser

float laserVellX = 0.3f; // Laser X speed
float laserVellY = 0.3f; // Laser Y speed

// Handle Events 
SDL_Event event;

// Music
Mix_Music* music = NULL;

// Sound Effects
Mix_Chunk* ballpaddlehit = NULL;
Mix_Chunk* powerup       = NULL;
Mix_Chunk* game_over     = NULL;
Mix_Chunk* laser_sound   = NULL;
Mix_Chunk* brickhit      = NULL;
Mix_Chunk* win_level     = NULL;
Mix_Chunk* lose_life = NULL;

// Load Renderer
SDL_Renderer* renderer = NULL;

// Press Space Text
SDL_Surface* pressSpace = NULL;
SDL_Texture* pressSpacetexture = NULL;

// Score Number Text
SDL_Surface* score = NULL;
SDL_Texture* scoretexture = NULL;
SDL_Surface* score0 = NULL;
SDL_Texture* scoretexture0 = NULL;
SDL_Surface* score1 = NULL;
SDL_Texture* scoretexture1 = NULL;
SDL_Surface* score2 = NULL;
SDL_Texture* scoretexture2 = NULL;
SDL_Surface* score3 = NULL;
SDL_Texture* scoretexture3 = NULL;
SDL_Surface* score4 = NULL;
SDL_Texture* scoretexture4 = NULL;
SDL_Surface* score5 = NULL;
SDL_Texture* scoretexture5 = NULL;
SDL_Surface* score6 = NULL;
SDL_Texture* scoretexture6 = NULL;
SDL_Surface* score7 = NULL;
SDL_Texture* scoretexture7 = NULL;
SDL_Surface* score8 = NULL;
SDL_Texture* scoretexture8 = NULL;
SDL_Surface* score9 = NULL;
SDL_Texture* scoretexture9 = NULL;

// Level Text
SDL_Surface* level1 = NULL;
SDL_Texture* leveltexture1 = NULL;
SDL_Surface* level2 = NULL;
SDL_Texture* leveltexture2 = NULL;
SDL_Surface* level3 = NULL;
SDL_Texture* leveltexture3 = NULL;

// Life Text
SDL_Surface* lifes3 = NULL;
SDL_Texture* lifestexture3 = NULL;
SDL_Surface* lifes2 = NULL;
SDL_Texture* lifestexture2 = NULL;
SDL_Surface* lifes1 = NULL;
SDL_Texture* lifestexture1 = NULL;
SDL_Surface* lifes0 = NULL;
SDL_Texture* lifestexture0 = NULL;

// Ball Textures
SDL_Surface* ball = NULL;
SDL_Texture* balltexture = NULL;
SDL_Surface* ball2 = NULL;
SDL_Texture* balltexture2 = NULL;

// Bonus Laser
SDL_Surface* laser = NULL;
SDL_Texture* lasertexture = NULL;

// Extra Ball Text
SDL_Surface* bonusball = NULL;
SDL_Texture* bonusballtexture = NULL;

// Laser Text
SDL_Surface* bonuslaser = NULL;
SDL_Texture* bonuslasertexture = NULL;

// Lifelost
SDL_Surface* lifelost = NULL;
SDL_Texture* lifelosttexture = NULL;

// Brick1
SDL_Surface* brick1 = NULL;
SDL_Texture* bricktexture1 = NULL;

// Brick2
SDL_Surface* brick2 = NULL;
SDL_Texture* bricktexture2 = NULL;

// Winner
SDL_Surface* winner = NULL;
SDL_Texture* winnertexture = NULL;

// Gameover
SDL_Surface* gameover = NULL;
SDL_Texture* gameovertexture = NULL;

// Next Level
SDL_Surface* nextlevel = NULL;
SDL_Texture* nextleveltexture = NULL;

// Paddle
SDL_Surface* paddle = NULL;
SDL_Texture* paddletexture = NULL;

// Background
SDL_Surface* background = NULL;
SDL_Texture* backgroundtexture = NULL;

// Size and position of images //
SDL_Rect pscore = { 600, 10, 120, 42 };
SDL_Rect pgameover = { 280, 280, 240, 100 };
SDL_Rect pscore3 = { 760, 10, 60, 42 };
SDL_Rect pwinner = { 280, 280, 240, 100 };

int main(int agrc, char* args[])

{
    // Intialize SDL //

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    // Intialize IMG //

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags)
        printf("IMG_Init: Failed to init required jpg and png support!\n");
    printf("IMG_Init: %s\n", IMG_GetError());

    // Initialize Mixer //

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 8, 4096) == -1)
    {
        return false;
    }

    // Load the sound effects //

    ballpaddlehit = Mix_LoadWAV("Sounds/ballpaddlehit.wav");
    powerup = Mix_LoadWAV("Sounds/bonus.wav");
    game_over = Mix_LoadWAV("Sounds/game_over.wav");
    laser_sound = Mix_LoadWAV("Sounds/laser.mp3");
    brickhit = Mix_LoadWAV("Sounds/jump_coin.wav"); 
    win_level = Mix_LoadWAV("Sounds/win_level.wav");
    lose_life = Mix_LoadWAV("Sounds/lose_life.wav");
    
    music = Mix_LoadMUS("Sounds/Retro_Future_Nights.mp3");

    SDL_Window* window = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_OPENGL);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_SetWindowResizable(window, SDL_FALSE);

    // Load Renderer //

    renderer = SDL_CreateRenderer(window, -1, 0);

    // Brick Struture //

   struct Brick01 lvl1[BRICKS01];

    // Image Loading //

    LoadTextures();

    // OpenGL memory usage //
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    bool isRunning = true;
   
    /*source based on Luka Horvat: ~ https://pastebin.com/jqnGJRfR */

    // Level one brick structure //

    if (level == 1)
    {
        for (int i = 0, x = 64, y = 80; i < BRICKS01; i++, x += 67)
        {
            if (x > 720) // New row
            {
                {
                    x = 64; // Reset X
                    y += 20; // Move Y down
                }
       
            }
            lvl1[i].brickposX = x; // X position
            lvl1[i].brickposY = y; // Y position
            lvl1[i].brickX = 64; // Width
            lvl1[i].brickY = 16; // Height
            lvl1[i].alive = true; // Set alive
        }
    }

    /*source based on Luka Horvat ends here */

    // PlayMusic //

    Mix_PlayMusic(music, -1);

    // Main Events //

    while (isRunning == true)

    {
        // Mixer Levels //

        Mix_Volume(0, 20);
        Mix_Volume(1, 20);
        Mix_Volume(2, 20);
        Mix_Volume(3, 20);
        Mix_Volume(4, 20);
        Mix_Volume(5, 20);
        Mix_Volume(6, 20);
        Mix_Volume(7, 20);
        Mix_Volume(8, 20);

        // SDL Events //

        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
        {
            break;
        }

        // Paddle and ball positions //

        SDL_Rect ppaddle = { (int)paddlex, (int)paddley, paddleWidth, paddleHeight };
        SDL_Rect pball = { (int)ballX, (int)ballY, ballWH, ballWH };

        // Image Renders //

        SDL_RenderCopy(renderer, backgroundtexture, NULL, NULL);
        SDL_RenderCopy(renderer, paddletexture, NULL, &ppaddle);
        SDL_RenderCopy(renderer, balltexture, NULL, &pball);
        SDL_RenderCopy(renderer, scoretexture, NULL, &pscore);
        SDL_RenderCopy(renderer, scoretexture0, NULL, &pscore3);
        
        // Functions //

        KeyboardControls();
        ScoreRender();
        LevelText();
        LifeText();
        ExtraBall();
        LaserBeam();
        BallLogic();

        ////////////////// Level Change ////////////////////////

        if (bricksAlive <= 0)
            {
                if (level == 4)
                {
                    SDL_RenderCopy(renderer, winnertexture, NULL, &pwinner);
                    SDL_RenderPresent(renderer);
                    Mix_PlayChannel(-1, win_level, 0);
                    SDL_Delay(2000);
                    break;
                }
                else if (level == 1 || level == 2 || level == 3)
                {
                    laserOn = false;
                    bonusballOn = false;
                    ballMotion = false;
                    ballY = 550;
                    ballY2 = 550;
                    Mix_PlayChannel(-1, win_level, 0);
                    SDL_Delay(500);
                    level += 1;
                    if (level == 1 || level == 2 || level == 3)
                        SDL_RenderCopy(renderer, nextleveltexture, NULL, &pwinner);
                    SDL_RenderPresent(renderer);
                    SDL_Delay(2000);
                    
                }

                if (level == 2)
                {
                    bricksAlive = BRICKS02;
                }

                // Level two brick structure

                if (level == 2)
                {
                    for (int i = 0, x = 64, y = 60; i < BRICKS02; i++, x += 67)
                    {
                        if (x > 720)
                        {
                            if (y == 60 || y == 100 || y == 140 || y == 180 || y == 220 || y == 260 || y == 300)
                            {
                                x = 33.5; // 33.5 for brick bond pattern
                                y += 20;
                            }
                            else if (y == 80 || y == 120 || y == 160 || y == 200 || y == 240 || y == 280 || y == 320)
                            {
                                x = 64;
                                y += 20;
                            }
                        }
                        lvl1[i].brickposX = x;
                        lvl1[i].brickposY = y;
                        lvl1[i].brickX = 64;
                        lvl1[i].brickY = 16;
                        lvl1[i].alive = true;
                    }
                }

                if (level == 3)
                {
                    bricksAlive = BRICKS03;
                }

                // Level three brick structure

                if (level == 3)
                {
                    for (int i = 0, x = 32, y = 60; i < BRICKS03; i++, x += 134)
                    {
                        if (x > 740)
                        {
                            if (y == 60 || y == 100 || y == 140 || y == 180 || y == 220 || y == 260 || y == 300 || y == 340 || y == 380 || y == 420 || y == 460)
                            {
                          
                                    x = 16;
                                    y += 20;
                            }
                            else if (y == 80 || y == 120 || y == 160 || y == 200 || y == 240 || y == 280 || y == 320 || y == 360 || y == 400 || y == 440 || y == 480)
                            {
                                x = 32;
                                y += 20;
                            }
                        }
                        lvl1[i].brickposX = x;
                        lvl1[i].brickposY = y;
                        lvl1[i].brickX = 64;
                        lvl1[i].brickY = 16;
                        lvl1[i].alive = true;
                    }
                }
            }

        ////////////////// Level Change End //////////////////// 
        
        // Brick Renders //

        if (level == 1)
            {
                for (int i = 0; i < BRICKS01; i++)
                {
                    if (lvl1[i].alive)
                    {
                        // Set rectangle positions
                        SDL_Rect pbrick = { lvl1[i].brickposX, lvl1[i].brickposY, lvl1[i].brickX, lvl1[i].brickY };

                        if (lvl1[i].brickposX % 134 == 0 || lvl1[i].brickposY % 80 == 0)
                        {
                            // Spawn blue bricks
                            SDL_RenderCopy(renderer, bricktexture1, NULL, &pbrick);
                        }
                        else if (lvl1[i].alive == true)
                        {
                            // Spawn yellow bricks
                            SDL_RenderCopy(renderer, bricktexture2, NULL, &pbrick);
                        }
                    }
                }
            }

        if (level == 2)
            {
                for (int i = 0; i < BRICKS02; i++)
                {
                    if (lvl1[i].alive)
                    {
                        // Set rectangle positions
                        SDL_Rect pbrick = { lvl1[i].brickposX, lvl1[i].brickposY, lvl1[i].brickX, lvl1[i].brickY };

                        // Spawn blue bricks
                        if (lvl1[i].brickposY % 40 == 0)

                        {
                            SDL_RenderCopy(renderer, bricktexture1, NULL, &pbrick);
                        }
                        // Spawn yellow bricks
                        else if (lvl1[i].brickposY % 20 == 0)

                        {
                            SDL_RenderCopy(renderer, bricktexture2, NULL, &pbrick);
                        }
                    }
                }
            }

        if (level == 3)
            {
                for (int i = 0; i < BRICKS03; i++)
                {
                    if (lvl1[i].alive)
                    {
                        // Set brick positions
                        SDL_Rect pbrick = { lvl1[i].brickposX, lvl1[i].brickposY, lvl1[i].brickX, lvl1[i].brickY };

                        // Spawn blue bricks
                        if (lvl1[i].brickposY % 40 == 0)

                        {
                            SDL_RenderCopy(renderer, bricktexture1, NULL, &pbrick);
                        }
                        // Spawn yellow bricks
                        else if (lvl1[i].brickposY % 20 == 0)

                        {
                            SDL_RenderCopy(renderer, bricktexture2, NULL, &pbrick);
                        }
                    }
                }
            }
        
        // Brick Collision //

        if (level == 1)
            {
                brickStructure = BRICKS01;
            }

        else if (level == 2)
            {
                brickStructure = BRICKS02;
            }

        else if (level == 3)
            {
                brickStructure = BRICKS03;
            }

        /*source based on Luka Horvat: ~ https://pastebin.com/jqnGJRfR */
        
        for (int i = 0; i < brickStructure; i++)
            {
                if (lvl1[i].alive == true) // Check if alive
                {
                    // Main ball Collision

                    if (checkCollision(ballX, ballY, ballWH, ballWH, (float)lvl1[i].brickposX, (float)lvl1[i].brickposY, (float)lvl1[i].brickX, (float)lvl1[i].brickY) == true) //Check for collision
                    {
                        Mix_PlayChannel(2, brickhit, 0);
                        vellY = -vellY; // Change Y velocity
                        playerScore += 10; // Adjust player score
                        bricksAlive -= 1;  // Update bricks alive

                        printf("Bricks remaining %d\n", bricksAlive);
                        printf("Score %d\n", playerScore);

                        lvl1[i].alive = false; // Remove Brick

                        // Generate random number
                        {
                            r = (int)rand() / (int)(RAND_MAX / 20);
                        }

                        break;
                    }

                    // Extra ball Collision

                    if (checkCollision(ballX2, ballY2, ballWH2, ballWH2, (float)lvl1[i].brickposX, (float)lvl1[i].brickposY, (float)lvl1[i].brickX, (float)lvl1[i].brickY) == true) //Check for collision
                    {
                        Mix_PlayChannel(2, brickhit, 0);
                        vellY2 = -vellY2;
                        playerScore += 10;
                        bricksAlive -= 1;
                        printf("Bricks remaining %d\n", bricksAlive);
                        printf("Score %d\n", playerScore);

                        lvl1[i].alive = false;
                        break;
                    }

                    // Laser Collision

                    if (checkCollision(laserX, laserY, (float)laserW, (float)laserH, (float)lvl1[i].brickposX, (float)lvl1[i].brickposY, (float)lvl1[i].brickX, (float)lvl1[i].brickY) == true) //Check for collision
                    {

                        laserY = paddley - 30;
                        laserX = paddlex + 40;
                        Mix_PlayChannel(5, laser_sound, 0);
                        playerScore += 10;
                        bricksAlive -= 1;
                        printf("Bricks remaining %d\n", bricksAlive);
                        printf("Score %d\n", playerScore);

                        lvl1[i].alive = false;

                        break;
                    }
                }
            }
        
        /*source based on Luka Horvat ends here */

        BallMotion();
        PaddleCollision();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        // Game over //

        if (life < 0 )

        {
            SDL_RenderCopy(renderer, gameovertexture, NULL, &pgameover);
            SDL_RenderPresent(renderer);
            Mix_PlayChannel(2, game_over, 0);
            SDL_Delay(3000);
            break;
        }

    }

    // Cleanup //

    SDL_DestroyTexture(backgroundtexture);
    SDL_DestroyTexture(balltexture);
    SDL_DestroyTexture(bricktexture1);
    SDL_DestroyTexture(bricktexture2);
    SDL_DestroyTexture(paddletexture);
    SDL_DestroyTexture(balltexture2);
    SDL_DestroyTexture(lifestexture3);
    SDL_DestroyTexture(lifestexture2);
    SDL_DestroyTexture(lifestexture1);
    SDL_DestroyTexture(lifestexture0);
    SDL_DestroyTexture(leveltexture1);
    SDL_DestroyTexture(leveltexture2);
    SDL_DestroyTexture(leveltexture3);
    SDL_DestroyTexture(scoretexture);
    SDL_DestroyTexture(scoretexture0);
    SDL_DestroyTexture(scoretexture1);
    SDL_DestroyTexture(scoretexture2);
    SDL_DestroyTexture(scoretexture3);
    SDL_DestroyTexture(scoretexture4);
    SDL_DestroyTexture(scoretexture5);
    SDL_DestroyTexture(scoretexture6);
    SDL_DestroyTexture(scoretexture7);
    SDL_DestroyTexture(scoretexture8);
    SDL_DestroyTexture(scoretexture9);
    SDL_DestroyTexture(winnertexture);
    SDL_DestroyTexture(gameovertexture);
    SDL_DestroyTexture(bonusballtexture);
    SDL_DestroyTexture(bonuslasertexture);
    SDL_DestroyTexture(lasertexture);
    SDL_DestroyTexture(lifelosttexture);
    SDL_DestroyTexture(nextleveltexture);
    SDL_DestroyTexture(pressSpacetexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}

void BallLogic()

{
    SDL_Rect plifelost = { 280, 280, 240, 100 };

    // Bottom edge collision for extra ball

    if (ballY2 > 640)
    {
        bonusballOn = false;
    }

    // Bottom edge collision

    if (ballY >= 640)
    {
        laserOn = false;
        bonusballOn = false;
        ballMotion = false;
        Mix_PlayChannel(-1, lose_life, 0);
        if (life > 0) SDL_RenderCopy(renderer, lifelosttexture, NULL, &plifelost);
        SDL_RenderPresent(renderer);
        life -= 1;
        SDL_Delay(2000);
    }

    // Screen edge collision

    if (ballX <= 1)
    {
        vellX = -vellX;
    }

    if (ballX >= 786)
    {
        vellX = -vellX;
    }

    if (ballY <= 1)
    {
        vellY = -vellY;
    }

    // Out of bounds Reset

    if (ballX < 0 || ballX > 800)
    {
        ballX = paddlex;
    }

    // Screen edge collision extra ball

    if (ballX2 <= 1)
    {
        vellX2 = -vellX2;
    }

    if (ballX2 >= 786)
    {
        vellX2 = -vellX2;
    }

    if (ballY2 <= 1)
    {
        vellY2 = -vellY2;
    }

    // Out of bounds Reset

    if (ballX2 < 0 || ballX2 > 800)
    {
        ballX2 = paddlex;
    }
}

void KeyboardControls()

{
    // Keyboard controls

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_LEFT:
            paddlex -= SPEED;
            break;

        case SDLK_RIGHT:
            paddlex += SPEED;
            break;

        case SDLK_SPACE:
            ballMotion = true;
            ballMotion2 = true;
            break;
        }
        // Screen edge collision
        if (paddlex < 0) { paddlex = 0; }
        if (paddlex > 720) { paddlex = 720; }
    }
}

void PaddleCollision()
{
    // Paddle Collision Main Ball

    if (checkCollision(ballX, ballY, ballWH, ballWH, paddlex, paddley, (float)paddleWidth, (float)paddleHeight) == true)
    {
        vellY = 0.08f; //Ball Y speed
        Mix_PlayChannel(6, ballpaddlehit, 0);
    }
    if (checkCollision(ballY, ballX, ballWH, ballWH, paddley, paddlex, (float)paddleWidth, (float)paddleHeight) == true)
    {
        // Random ball X speed
        vellX = -(float)rand() / (float)(RAND_MAX / 0.08f) - 0.02f;
    }

    // Paddle Collision Extra Ball

    if (checkCollision(ballX2, ballY2, ballWH2, ballWH2, paddlex, paddley, (float)paddleWidth, (float)paddleHeight) == true)
    {
        Mix_PlayChannel(6, ballpaddlehit, 0);
        vellY2 = -vellY2; //Ball Y speed
    }
    if (checkCollision(ballY2, ballX2, ballWH2, ballWH2, paddley, paddlex, (float)paddleWidth, (float)paddleHeight) == true)
    {
        // Random ball X speed
        vellX2 = (float)rand() / (float)(RAND_MAX / 0.09f);
    }
}

void BallMotion()
{
    
    SDL_Rect ppressSpace = { 280, 600, 240, 40 };

    if (ballMotion == true)
    {
        ballX -= vellX;
        ballY -= vellY;
    }
    else if (ballMotion == false)
    {
        laserOn = false;
        bonusballOn = false;
        SDL_RenderCopy(renderer, pressSpacetexture, NULL, &ppressSpace);
        SDL_RenderPresent(renderer);
        ballX = paddlex + 32;
        ballY = paddley - 16;
    }
}

void ScoreRender()
{
    SDL_Rect pscore1 = { 720, 10, 60, 42 };
    SDL_Rect pscore2 = { 740, 10, 60, 42 };
    SDL_Rect pscore4 = { 700, 10, 60, 42 };

// Player Score Render 10s

if (playerScore / 10 == 1 || playerScore / 10 % 10 == 1) {
    SDL_RenderCopy(renderer, scoretexture1, NULL, &pscore2);
}
else if (playerScore / 10 == 2 || playerScore / 10 % 10 == 2) {
    SDL_RenderCopy(renderer, scoretexture2, NULL, &pscore2);
}
else if (playerScore / 10 == 3 || playerScore / 10 % 10 == 3) {
    SDL_RenderCopy(renderer, scoretexture3, NULL, &pscore2);
}
else if (playerScore / 10 == 4 || playerScore / 10 % 10 == 4) {
    SDL_RenderCopy(renderer, scoretexture4, NULL, &pscore2);
}
else if (playerScore / 10 == 5 || playerScore / 10 % 10 == 5) {
    SDL_RenderCopy(renderer, scoretexture5, NULL, &pscore2);
}
else if (playerScore / 10 == 6 || playerScore / 10 % 10 == 6) {
    SDL_RenderCopy(renderer, scoretexture6, NULL, &pscore2);
}
else if (playerScore / 10 == 7 || playerScore / 10 % 10 == 7) {
    SDL_RenderCopy(renderer, scoretexture7, NULL, &pscore2);
}
else if (playerScore / 10 == 8 || playerScore / 10 % 10 == 8) {
    SDL_RenderCopy(renderer, scoretexture8, NULL, &pscore2);
}
else if (playerScore / 10 == 9 || playerScore / 10 % 10 == 9) {
    SDL_RenderCopy(renderer, scoretexture9, NULL, &pscore2);
}
else if (playerScore / 10 == 10 || playerScore / 10 % 10 == 0) {
    SDL_RenderCopy(renderer, scoretexture0, NULL, &pscore2);
}

// Player Score Render 100s

if (playerScore / 100 == 1 || playerScore / 100 % 10 == 1) {
    SDL_RenderCopy(renderer, scoretexture1, NULL, &pscore1);
}
else if (playerScore / 100 == 2 || playerScore / 100 % 10 == 2) {
    SDL_RenderCopy(renderer, scoretexture2, NULL, &pscore1);
}
else if (playerScore / 100 == 3 || playerScore / 100 % 10 == 3) {
    SDL_RenderCopy(renderer, scoretexture3, NULL, &pscore1);
}
else if (playerScore / 100 == 4 || playerScore / 100 % 10 == 4) {
    SDL_RenderCopy(renderer, scoretexture4, NULL, &pscore1);
}
else if (playerScore / 100 == 5 || playerScore / 100 % 10 == 5) {
    SDL_RenderCopy(renderer, scoretexture5, NULL, &pscore1);
}
else if (playerScore / 100 == 6 || playerScore / 100 % 10 == 6) {
    SDL_RenderCopy(renderer, scoretexture6, NULL, &pscore1);
}
else if (playerScore / 100 == 7 || playerScore / 100 % 10 == 7) {
    SDL_RenderCopy(renderer, scoretexture7, NULL, &pscore1);
}
else if (playerScore / 100 == 8 || playerScore / 100 % 10 == 8) {
    SDL_RenderCopy(renderer, scoretexture8, NULL, &pscore1);
}
else if (playerScore / 100 == 9 || playerScore / 100 % 10 == 9) {
    SDL_RenderCopy(renderer, scoretexture9, NULL, &pscore1);
}
else if (playerScore / 100 == 10 || playerScore / 100 % 10 == 0) {
    SDL_RenderCopy(renderer, scoretexture0, NULL, &pscore1);
}

// Player Score Render 1000s

if (playerScore / 1000 == 1 || playerScore / 1000 % 10 == 1) {
    SDL_RenderCopy(renderer, scoretexture1, NULL, &pscore4);
}
else if (playerScore / 1000 == 2 || playerScore / 1000 % 10 == 2) {
    SDL_RenderCopy(renderer, scoretexture2, NULL, &pscore4);
}
else if (playerScore / 1000 == 3 || playerScore / 1000 % 10 == 3) {
    SDL_RenderCopy(renderer, scoretexture3, NULL, &pscore4);
}
else if (playerScore / 1000 == 4 || playerScore / 1000 % 10 == 4) {
    SDL_RenderCopy(renderer, scoretexture4, NULL, &pscore4);
}
else if (playerScore / 1000 == 5 || playerScore / 1000 % 10 == 5) {
    SDL_RenderCopy(renderer, scoretexture5, NULL, &pscore4);
}
else if (playerScore / 1000 == 6 || playerScore / 1000 % 10 == 6) {
    SDL_RenderCopy(renderer, scoretexture6, NULL, &pscore4);
}
else if (playerScore / 1000 == 7 || playerScore / 1000 % 10 == 7) {
    SDL_RenderCopy(renderer, scoretexture7, NULL, &pscore4);
}
else if (playerScore / 1000 == 8 || playerScore / 1000 % 10 == 8) {
    SDL_RenderCopy(renderer, scoretexture8, NULL, &pscore4);
}
else if (playerScore / 1000 == 9 || playerScore / 1000 % 10 == 9) {
    SDL_RenderCopy(renderer, scoretexture9, NULL, &pscore4);
}
else if (playerScore / 1000 == 10 || playerScore / 1000 % 10 == 0) {
    SDL_RenderCopy(renderer, scoretexture0, NULL, &pscore4);
}
}

void LevelText()
{
// Level Text Render

SDL_Rect plevel = { 350, 10, 120, 42 };

if (level == 1) {
    SDL_RenderCopy(renderer, leveltexture1, NULL, &plevel);
}
else if (level == 2) {
    SDL_RenderCopy(renderer, leveltexture2, NULL, &plevel);
}
else if (level == 3) {
    SDL_RenderCopy(renderer, leveltexture3, NULL, &plevel);
}
}

void LifeText()
{
    // Life Text Render

    SDL_Rect plifes = { 10, 10, 120, 42 };

    if (life == 3) {
        SDL_RenderCopy(renderer, lifestexture3, NULL, &plifes);
    }
    else if (life == 2) {
        SDL_RenderCopy(renderer, lifestexture2, NULL, &plifes);
    }
    else if (life == 1) {
        SDL_RenderCopy(renderer, lifestexture1, NULL, &plifes);
    }
    else {
        SDL_RenderCopy(renderer, lifestexture0, NULL, &plifes);
    }
}

void ExtraBall()
{
    // Extra Ball Spawn

    SDL_Rect pball2 = { (int)ballX2, (int)ballY2, ballWH2, ballWH2 };
    SDL_Rect pbonusBall = { 5, 600, 240, 40 };

    if (r == 10 && laserOn == false && ballMotion == true)
    {
        bonusballOn = true;
        Mix_PlayChannel(-1, powerup, 0);
    }

    if (bonusballOn == true)
    {
        SDL_RenderCopy(renderer, balltexture2, NULL, &pball2);
        SDL_RenderCopy(renderer, bonusballtexture, NULL, &pbonusBall);
    }
    else if (bonusballOn == false)
    {
        ballX2 = paddlex + 32;
        ballY2 = paddley - 35;
    }

    if (ballMotion2 == true)
    {
        ballX2 -= vellX2;
        ballY2 -= vellY2;
    }
    else if (ballMotion2 == false)
    {
        ballX2 = paddlex + 32;
        ballY2 = paddley - 35;
    }
}

void LaserBeam()
{
    // Laser Power Up

    SDL_Rect pbonusLaser = { 560, 600, 240, 40 };
    SDL_Rect plaser = { (int)laserX, (int)laserY, laserW, laserH };

    if (r == 1 && bonusballOn == false && ballMotion == true)
    {
        laserOn = true;
        Mix_PlayChannel(-1, powerup, 0);
    }

    if (laserOn == true)
    {
        laserY -= laserVellY;
        SDL_RenderCopy(renderer, lasertexture, NULL, &plaser);
        SDL_RenderCopy(renderer, bonuslasertexture, NULL, &pbonusLaser);
    }

    if (laserY <= 5)
    {
        Mix_PlayChannel(5, laser_sound, 0);
        laserY = paddley - 30;
        laserX = paddlex + 40;
    }
}

void LoadTextures()
{
    // Paddle
    paddle = IMG_Load("Images/paddle.png");
    paddletexture = SDL_CreateTextureFromSurface(renderer, paddle);

    // Background
    background = IMG_Load("Images/background.png");
    backgroundtexture = SDL_CreateTextureFromSurface(renderer, background);

    // Brick1
    brick1 = IMG_Load("Images/brick1.png");
    bricktexture1 = SDL_CreateTextureFromSurface(renderer, brick1);

    // Brick2
    brick2 = IMG_Load("Images/brick2.png");
    bricktexture2 = SDL_CreateTextureFromSurface(renderer, brick2);

    // Ball
    ball = IMG_Load("Images/ball.png");
    balltexture = SDL_CreateTextureFromSurface(renderer, ball);
    ball2 = IMG_Load("Images/ball2.png");
    balltexture2 = SDL_CreateTextureFromSurface(renderer, ball2);

    // Lives
    lifes3 = IMG_Load("Images/lifes3.png");
    lifestexture3 = SDL_CreateTextureFromSurface(renderer, lifes3);
    lifes2 = IMG_Load("Images/lifes2.png");
    lifestexture2 = SDL_CreateTextureFromSurface(renderer, lifes2);
    lifes1 = IMG_Load("Images/lifes1.png");
    lifestexture1 = SDL_CreateTextureFromSurface(renderer, lifes1);
    lifes0 = IMG_Load("Images/lifes0.png");
    lifestexture0 = SDL_CreateTextureFromSurface(renderer, lifes0);

    // Level
    level1 = IMG_Load("Images/level1.png");
    leveltexture1 = SDL_CreateTextureFromSurface(renderer, level1);
    level2 = IMG_Load("Images/level2.png");
    leveltexture2 = SDL_CreateTextureFromSurface(renderer, level2);
    level3 = IMG_Load("Images/level3.png");
    leveltexture3 = SDL_CreateTextureFromSurface(renderer, level3);

    // Score
    score = IMG_Load("Images/Score.png");
    scoretexture = SDL_CreateTextureFromSurface(renderer, score);

    // Score Numbers
    score0 = IMG_Load("Images/Score0.png");
    scoretexture0 = SDL_CreateTextureFromSurface(renderer, score0);
    score1 = IMG_Load("Images/Score1.png");
    scoretexture1 = SDL_CreateTextureFromSurface(renderer, score1);
    score2 = IMG_Load("Images/Score2.png");
    scoretexture2 = SDL_CreateTextureFromSurface(renderer, score2);
    score3 = IMG_Load("Images/Score3.png");
    scoretexture3 = SDL_CreateTextureFromSurface(renderer, score3);
    score4 = IMG_Load("Images/Score4.png");
    scoretexture4 = SDL_CreateTextureFromSurface(renderer, score4);
    score5 = IMG_Load("Images/Score5.png");
    scoretexture5 = SDL_CreateTextureFromSurface(renderer, score5);
    score6 = IMG_Load("Images/Score6.png");
    scoretexture6 = SDL_CreateTextureFromSurface(renderer, score6);
    score7 = IMG_Load("Images/Score7.png");
    scoretexture7 = SDL_CreateTextureFromSurface(renderer, score7);
    score8 = IMG_Load("Images/Score8.png");
    scoretexture8 = SDL_CreateTextureFromSurface(renderer, score8);
    score9 = IMG_Load("Images/Score9.png");
    scoretexture9 = SDL_CreateTextureFromSurface(renderer, score9);

    // Winner
    winner = IMG_Load("Images/winner.png");
    winnertexture = SDL_CreateTextureFromSurface(renderer, winner);

    // Gameover
    gameover = IMG_Load("Images/gameover.png");
    gameovertexture = SDL_CreateTextureFromSurface(renderer, gameover);

    // ExtraBall
    bonusball = IMG_Load("Images/bonusball.png");
    bonusballtexture = SDL_CreateTextureFromSurface(renderer, bonusball);

    // BonusLaser Text
    bonuslaser = IMG_Load("Images/bonuslaser.png");
    bonuslasertexture = SDL_CreateTextureFromSurface(renderer, bonuslaser);

    // BonusLaser
    laser = IMG_Load("Images/laser.png");
    lasertexture = SDL_CreateTextureFromSurface(renderer, laser);

    // Lifelost
    lifelost = IMG_Load("Images/lifelost.png");
    lifelosttexture = SDL_CreateTextureFromSurface(renderer, lifelost);

    // Next Level
    nextlevel = IMG_Load("Images/nextlevel.png");
    nextleveltexture = SDL_CreateTextureFromSurface(renderer, nextlevel);

    // PressSpace
    pressSpace = IMG_Load("Images/pressSpace.png");
    pressSpacetexture = SDL_CreateTextureFromSurface(renderer, pressSpace);
}