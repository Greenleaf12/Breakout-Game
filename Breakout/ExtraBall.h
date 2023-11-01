#pragma once

void ExtraBall()
{
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