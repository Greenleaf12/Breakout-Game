#pragma once

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