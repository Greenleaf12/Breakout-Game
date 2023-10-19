#pragma once

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
