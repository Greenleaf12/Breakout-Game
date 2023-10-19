#pragma once
#include "SDL_opengl.h"
#include "SDL_image.h"
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

const float SPEED = 9.2f; // Speed of paddle

float paddlex = 360.0f; // X Start position
float paddley = 570.0f; // Y Start position

int paddleWidth = 80; // Paddle width
int paddleHeight = 18; // Paddle height

// Ball variables //

float ballX = 440.0f; // X start position
float ballY = 570.0f; // Y start position
const int ballWH = 14; // Width and height

float vellX = 2.0f; // Ball X speed
float vellY = 6.0f; // Ball Y speed

bool ballMotion = false;

// Extra ball variables //

float ballX2 = 400; // X start position
float ballY2 = 550; // Y start position
const int ballWH2 = 24; // Width and height

float vellX2 = 2.0f; // Ball X speed
float vellY2 = 5.0f; // Ball Y speed

bool ballMotion2 = false;

// Laser Variables //

float laserX = 400.0f; // X start position
float laserY = 550.0f; // Y start position

int laserH = 40; // Height of laser
int laserW = 4;  // Width of laser

float laserVellX = 30.3f; // Laser X speed
float laserVellY = 30.3f; // Laser Y speed

// Handle Events 
SDL_Event event;

// Music
Mix_Music* music = NULL;

// Sound Effects
Mix_Chunk* ballpaddlehit = NULL;
Mix_Chunk* powerup = NULL;
Mix_Chunk* game_over = NULL;
Mix_Chunk* laser_sound = NULL;
Mix_Chunk* brickhit = NULL;
Mix_Chunk* win_level = NULL;
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