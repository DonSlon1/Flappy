#include "raylib.h"
#include <stdio.h>

typedef struct bird{
    float x;
    float y;
    float SpeadX;
    float SpeadY;
}
Bird;
int main() {
    const int screenWidth = 996;
    const int screenHeight = 450;
    float move=0;
    Bird ptak ;
    ptak.x=200;
    ptak.y=200;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");
    Texture2D City = LoadTexture("src/City.png");
    SetTargetFPS(60);
    while (!WindowShouldClose()){
        move += -1.0f;
        if(move<= -(float )City.width) move = 0;
        BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));

        DrawTextureEx(City,(Vector2){move , 0.0f},0.0f,1.0f,WHITE);
        DrawTextureEx(City,(Vector2){(float )City.width+move,0.0f},0.0f,1.0f,WHITE);

        DrawRectanglePro((Rectangle){0,0,40,40},(Vector2){ptak.x,ptak.y},0.0f,BLACK) ;

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(City);
    return 0;
}
