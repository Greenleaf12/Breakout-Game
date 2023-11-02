#pragma once

void LaserBeam()
{
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