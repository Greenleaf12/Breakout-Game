#pragma once

void PaddleCollision()
{
    // Paddle Collision Main Ball
    if (checkCollision(ballX, ballY, ballWH, ballWH, paddlex, paddley, (float)paddleWidth, (float)paddleHeight) == true)
    {
        vellY = 6.0f; //Ball Y speed
        Mix_PlayChannel(6, ballpaddlehit, 0);
    }
    if (checkCollision(ballY, ballX, ballWH, ballWH, paddley, paddlex, (float)paddleWidth, (float)paddleHeight) == true)
    {
        // Random ball X speed
        vellX = (float)rand() / (float)(RAND_MAX / 4.5f);
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
        vellX2 = (float)rand() / (float)(RAND_MAX / 4.5f);
    }
}
