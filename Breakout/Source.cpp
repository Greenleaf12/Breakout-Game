
// Breakout Game in C - Written by Rory Gardner - 2020 //

#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <stdio.h> 
#include <stdlib.h>

#include "Variables.h"
#include "TextureLoad.h"
#include "UIText.h"
#include "BallLogic.h"
#include "LaserBeam.h"
#include "ExtraBall.h"
#include "KeyboardControls.h"
#include "BallMotion.h"
#include "PaddleCollision.h"

int main(int agrc, char* args[])

{
    const int FPS = 60;
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

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

    // PlayMusic //
    Mix_PlayMusic(music, -1);

    // Main Events //
    while (isRunning == true)

    {    
        // Frame Limiter //
        frameStart = SDL_GetTicks();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }

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
        LevelText();
        LifeText();
        ExtraBall();
        LaserBeam();
        BallLogic();
        ScoreRender();

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

        BallMotion();
        PaddleCollision();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderPresent(renderer);

        // Game over //
        if (life < 0)
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



