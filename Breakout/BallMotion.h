#pragma once

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