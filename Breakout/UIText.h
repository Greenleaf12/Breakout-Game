#pragma once

void ScoreRender()
{
    SDL_Rect pscore1 = { 720, 10, 60, 42 };
    SDL_Rect pscore2 = { 740, 10, 60, 42 };
    SDL_Rect pscore4 = { 700, 10, 60, 42 };

    // Player Score Render 10s

   //for (int i = 0; i < 10; i++) 
   // {
   //     if (playerScore / 10 == i || playerScore / 10 % 10 == i)
   //         SDL_RenderCopy(renderer, scoretexture1, NULL, &pscore2);
   // }
   
   if (playerScore / 10 == 1 || playerScore / 10 % 10 == 1) {
       SDL_RenderCopy(renderer, scoretexture1, NULL, &pscore2);
   }
   if (playerScore / 10 == 2 || playerScore / 10 % 10 == 2) {
       SDL_RenderCopy(renderer, scoretexture2, NULL, &pscore2);
   }
   if (playerScore / 10 == 3 || playerScore / 10 % 10 == 3) {
       SDL_RenderCopy(renderer, scoretexture3, NULL, &pscore2);
   }
   if (playerScore / 10 == 4 || playerScore / 10 % 10 == 4) {
       SDL_RenderCopy(renderer, scoretexture4, NULL, &pscore2);
   }
   if (playerScore / 10 == 5 || playerScore / 10 % 10 == 5) {
       SDL_RenderCopy(renderer, scoretexture5, NULL, &pscore2);
   }
   if (playerScore / 10 == 6 || playerScore / 10 % 10 == 6) {
       SDL_RenderCopy(renderer, scoretexture6, NULL, &pscore2);
   }
   if (playerScore / 10 == 7 || playerScore / 10 % 10 == 7) {
       SDL_RenderCopy(renderer, scoretexture7, NULL, &pscore2);
   }
   if (playerScore / 10 == 8 || playerScore / 10 % 10 == 8) {
       SDL_RenderCopy(renderer, scoretexture8, NULL, &pscore2);
   }
   if (playerScore / 10 == 9 || playerScore / 10 % 10 == 9) {
       SDL_RenderCopy(renderer, scoretexture9, NULL, &pscore2);
   }
   if (playerScore / 10 == 10 || playerScore / 10 % 10 == 0) {
       SDL_RenderCopy(renderer, scoretexture0, NULL, &pscore2);
   }

    // Player Score Render 100s
    if (playerScore / 100 == 1 || playerScore / 100 % 10 == 1) {
        SDL_RenderCopy(renderer, scoretexture1, NULL, &pscore1);
    }
    if (playerScore / 100 == 2 || playerScore / 100 % 10 == 2) {
        SDL_RenderCopy(renderer, scoretexture2, NULL, &pscore1);
    }
    if (playerScore / 100 == 3 || playerScore / 100 % 10 == 3) {
        SDL_RenderCopy(renderer, scoretexture3, NULL, &pscore1);
    }
    if (playerScore / 100 == 4 || playerScore / 100 % 10 == 4) {
        SDL_RenderCopy(renderer, scoretexture4, NULL, &pscore1);
    }
    if (playerScore / 100 == 5 || playerScore / 100 % 10 == 5) {
        SDL_RenderCopy(renderer, scoretexture5, NULL, &pscore1);
    }
    if (playerScore / 100 == 6 || playerScore / 100 % 10 == 6) {
        SDL_RenderCopy(renderer, scoretexture6, NULL, &pscore1);
    }
    if (playerScore / 100 == 7 || playerScore / 100 % 10 == 7) {
        SDL_RenderCopy(renderer, scoretexture7, NULL, &pscore1);
    }
    if (playerScore / 100 == 8 || playerScore / 100 % 10 == 8) {
        SDL_RenderCopy(renderer, scoretexture8, NULL, &pscore1);
    }
    if (playerScore / 100 == 9 || playerScore / 100 % 10 == 9) {
        SDL_RenderCopy(renderer, scoretexture9, NULL, &pscore1);
    }
    if (playerScore / 100 == 10 || playerScore / 100 % 10 == 0) {
        SDL_RenderCopy(renderer, scoretexture0, NULL, &pscore1);
    }

    // Player Score Render 1000s
    if (playerScore / 1000 == 1 || playerScore / 1000 % 10 == 1) {
        SDL_RenderCopy(renderer, scoretexture1, NULL, &pscore4);
    }
    if (playerScore / 1000 == 2 || playerScore / 1000 % 10 == 2) {
        SDL_RenderCopy(renderer, scoretexture2, NULL, &pscore4);
    }
    if (playerScore / 1000 == 3 || playerScore / 1000 % 10 == 3) {
        SDL_RenderCopy(renderer, scoretexture3, NULL, &pscore4);
    }
    if (playerScore / 1000 == 4 || playerScore / 1000 % 10 == 4) {
        SDL_RenderCopy(renderer, scoretexture4, NULL, &pscore4);
    }
    if (playerScore / 1000 == 5 || playerScore / 1000 % 10 == 5) {
        SDL_RenderCopy(renderer, scoretexture5, NULL, &pscore4);
    }
    if (playerScore / 1000 == 6 || playerScore / 1000 % 10 == 6) {
        SDL_RenderCopy(renderer, scoretexture6, NULL, &pscore4);
    }
    if (playerScore / 1000 == 7 || playerScore / 1000 % 10 == 7) {
        SDL_RenderCopy(renderer, scoretexture7, NULL, &pscore4);
    }
    if (playerScore / 1000 == 8 || playerScore / 1000 % 10 == 8) {
        SDL_RenderCopy(renderer, scoretexture8, NULL, &pscore4);
    }
    if (playerScore / 1000 == 9 || playerScore / 1000 % 10 == 9) {
        SDL_RenderCopy(renderer, scoretexture9, NULL, &pscore4);
    }
    if (playerScore / 1000 == 10 || playerScore / 1000 % 10 == 0) {
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
