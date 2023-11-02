#pragma once

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
    if (ballX < -10 || ballX > 900)
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