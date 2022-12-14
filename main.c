#include "raylib.h"
#include <stdio.h>


typedef struct bird{
    float x;
    float y;
    float SpeadX;
    float SpeadY;
    float Rotation;
}
Bird;

int main() {
    const int screenWidth = 1024;
    const int screenHeight = 768;
    float move=0;
    bool down = false;
    bool start = false;
    float d=0;
    Bird ptak ;
    ptak.x=200;
    ptak.y=200;
    ptak.Rotation=0;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");
    Texture2D Background = LoadTexture("src/Pozadi.png");
    Texture2D Ground = LoadTexture("src/Spodek.png");
    Texture2D FlappyStart = LoadTexture("src/Flappy_Start.png");
    Texture2D FlappyUp = LoadTexture("src/Flappy_Up.png");
    SetTargetFPS(120);
    float up=0;
    while (!WindowShouldClose()){
        move += -0.5f;
        if(move<= -(float )Ground.width) move = 0;
        if(IsKeyPressed(KEY_SPACE)) {
            start=true;
            up += 80;

        }
        if(start){
            if (up >= 0) {
                ptak.y -= 3.0f;
                up -= 3.0f;
                d=30;
                down = false;
                ptak.Rotation=0;
            }
            if (up < 0) {
                ptak.y += 3.0f;
                d -= 3.0f;
                down = true;
                if(d<=0){
                    if(ptak.Rotation < 50) {
                        ptak.Rotation += 1.0f;
                    }
                    if(ptak.Rotation >= 50 && ptak.Rotation<=90) {
                        ptak.Rotation += 3;
                    }

                }

            }
        }
        BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));

        DrawTextureEx(Ground, (Vector2){move , 704.0f}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(Ground, (Vector2){(float )Ground.width + move, 704.0f}, 0.0f, 1.0f, WHITE);
        DrawTexture(Background,0,0,WHITE);
        if(!start){
            DrawTextureEx(FlappyStart, (Vector2) {200, ptak.y}, 0.0f, 1.0f, WHITE);
        }
        else if(down && d<=0 ) {
            DrawTextureEx(FlappyStart, (Vector2) {200, ptak.y}, ptak.Rotation, 1.0f, WHITE);
        }
        else  {
            DrawTextureEx(FlappyUp, (Vector2) {200, ptak.y}, 0.0f, 1.0f, WHITE);
        }
        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(Background);
    UnloadTexture(FlappyStart);
    UnloadTexture(FlappyUp);
    UnloadTexture(Ground);
    return 0;
}
