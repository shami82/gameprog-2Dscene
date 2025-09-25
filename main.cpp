/**
* Author: Nishat Shamiha
* Assignment: Simple 2D Scene
* Date due: 2025-09-27, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/

#include "raylib.h"
#include <math.h>
#include <stdio.h>

// Global Constants
enum AppStatus { TERMINATED, RUNNING };
constexpr int   SCREEN_WIDTH  = 1000,
                SCREEN_HEIGHT = 600,
                FPS           = 60,
                SIZE          = 200,
                FRAME_LIMIT   = 100;
constexpr float MAX_AMP       = 10.0f;

constexpr char    BG_COLOUR[] = "#000000";
constexpr Vector2 ORIGIN      = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
constexpr Vector2 BASE_SIZE   = { (float) SIZE, (float) SIZE };

constexpr char POKE[] = "assets/alakazam.png";
constexpr char BALL[] = "assets/pokeball.png";
constexpr char PSYCHIC[] = "assets/psychic.png";

// Global Variables
AppStatus gAppStatus     = RUNNING;
float     gScaleFactor   = SIZE,
          gAngle         = 0.0f,
          gPulseTime     = 0.0f,
          gPreviousTicks = 0.0f,
          changeClock = 0.0f;
Vector2   gPosition      = ORIGIN;
Vector2   gScale         = BASE_SIZE;
int frame = 0;

//variables for textures
Texture2D gPokeTexture;
Texture2D gBallTexture;
Texture2D gPsychicTexture;

Rectangle gPokeArea;
Rectangle gBallArea;
Rectangle gPsychicArea;

Vector2 gPokeScale;
Vector2 gBallPosition;

float gBallAngle;
float gBallRotation;

Vector2 ballSize = {25, 25};
Vector2 gPsychicPosition = {SCREEN_WIDTH - 100, ORIGIN.y};

// Function Declarations
Color ColorFromHex(const char *hex);
void initialise();
void processInput();
void update();
void render();
void shutdown();

// Function Definitions
Color ColorFromHex(const char *hex)
{
    // Skip leading '#', if present
    if (hex[0] == '#') hex++;
    // Default alpha = 255 (opaque)
    unsigned int r = 0, 
                 g = 0,
                 b = 0,
                 a = 255;
    // 6‑digit form: RRGGBB
    if (sscanf(hex, "%02x%02x%02x", &r, &g, &b) == 3) {
        return (Color){ (unsigned char) r,
                        (unsigned char) g,
                        (unsigned char) b,
                        (unsigned char) a };
    }
    // 8‑digit form: RRGGBBAA
    if (sscanf(hex, "%02x%02x%02x%02x", &r, &g, &b, &a) == 4) {
        return (Color){ (unsigned char) r,
                        (unsigned char) g,
                        (unsigned char) b,
                        (unsigned char) a };
    }
    // Fallback – return white so you notice something went wrong
    return RAYWHITE;
}

void initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures");

    gPokeTexture = LoadTexture(POKE);
    gBallTexture = LoadTexture(BALL);
    gPsychicTexture  = LoadTexture(PSYCHIC);

    gPokeArea = {
        // top-left corner
        0.0f, 0.0f,
        //bottom-right
        (float)gPokeTexture.width,
        (float)gPokeTexture.height
    };

    gBallArea = {
        // top-left corner
        0.0f, 0.0f,
        //bottom-right
        (float)gBallTexture.width,
        (float)gBallTexture.height
    };

    gPsychicArea = {
        // top-left corner
        0.0f, 0.0f,
        //bottom-right
        (float)gPsychicTexture.width,
        (float)gPsychicTexture.height
    };

    SetTargetFPS(FPS);
}

void processInput() 
{
    if (WindowShouldClose()) gAppStatus = TERMINATED;
}

void update() 
{
    /**
     * @todo Apply delta time to the time-dependent logic
     */
    // delta time
    float ticks = (float) GetTime();
    float deltaTime = ticks - gPreviousTicks;
    gPreviousTicks = ticks;

    gPulseTime += deltaTime;
    gAngle += 50.0f * deltaTime;  // rotation angle for poke

    // pulsing size for alakazam
    gPokeScale = {
        BASE_SIZE.x + MAX_AMP * cos(gPulseTime),
        BASE_SIZE.y + MAX_AMP * cos(gPulseTime)
    };

    // sin wave movement for alakaam
    gPosition.x = 150 + 50*sin(gPulseTime);
    gPosition.y = ORIGIN.y + 30*sin(gPulseTime * 0.5f);

    // ball orbit
    float orbitRadius = 150.0f;
    float orbitSpeed = 1.5f;

    gBallAngle += orbitSpeed * deltaTime;

    gBallPosition = {
        gPosition.x + orbitRadius * cos(gBallAngle),
        gPosition.y + orbitRadius * sin(gBallAngle)
    };

    gBallRotation += -180.0f * deltaTime; //spin ball

    gPsychicPosition.x = SCREEN_WIDTH - 100;
    gPsychicPosition.y = ORIGIN.y + 100 * cos(gPulseTime);

    frame++;

    /**
     * @todo Switch member every 100 fames
     */

     /**
     * @todo NONE MOVE ONLY UP AND DOWN
     */


    /**
     * @todo EACH TRANSLATE DIFFERENTLY
     */


    /**
     * @todo Rotating
     */


    /**
     * @todo Scaling
     */ 
}

void render()
{
    BeginDrawing();
    ClearBackground(ColorFromHex(BG_COLOUR));

    // DrawCircleV(gBallPosition, 5, RED);

    // BACKGROUND WITH THE PSYCHIC SYMBOL --------------------------------
    Rectangle psychDestinationArea = {
        gPsychicPosition.x, gPsychicPosition.y,
        50, 50
    };

    // Origin inside the source texture (centre of the texture)
    Vector2 psychObjectOrigin = {
        25, 25
    };

    // Destination rectangle – centred on gPosition
    DrawTexturePro(
        gPsychicTexture,
        gPsychicArea,
        psychDestinationArea,
        psychObjectOrigin,
        gAngle,
        WHITE
    );

    // POKEBALL TEXTURE THINGS -------------------------------------------
    Rectangle ballDestinationArea = {
        gBallPosition.x, gBallPosition.y,
        ballSize.x, ballSize.y
    };

    Vector2 ballObjectOrigin = {
        ballSize.x / 2.0f, ballSize.y / 2.0f
    };
    
    DrawTexturePro(
        gBallTexture,
        gBallArea,
        ballDestinationArea,
        ballObjectOrigin,
        gBallRotation,
        WHITE
    );

    // ALAKAZAM TECTURE THINGS -------------------------------------------
    Rectangle pokeDestinationArea = {
        gPosition.x, gPosition.y,
        gPokeScale.x, gPokeScale.y
    };

    Vector2 pokeObjectOrigin = {
        gPokeScale.x / 2.0f, gPokeScale.y / 2.0f
    };

    DrawTexturePro(
        gPokeTexture,
        gPokeArea,
        pokeDestinationArea,
        pokeObjectOrigin,
        0.0f,
        WHITE
    );

    EndDrawing();
}

void shutdown() { CloseWindow(); }

int main(void)
{
    initialise();

    while (gAppStatus == RUNNING)
    {
        processInput();
        update();
        render();
    }

    shutdown();

    return 0;
}