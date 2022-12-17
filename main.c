#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <math.h>

Rectangle RotateRec(Rectangle rec, float angle)
{
    Rectangle result = { 0 };

    float c = cosf(angle);
    float s = sinf(angle);

    Vector2 tl = { rec.x, rec.y };
    Vector2 tr = { rec.x + rec.width, rec.y };
    Vector2 bl = { rec.x, rec.y + rec.height };
    Vector2 br = { rec.x + rec.width, rec.y + rec.height };

    Vector2 tl_ = { tl.x*c - tl.y*s, tl.x*s + tl.y*c };
    Vector2 tr_ = { tr.x*c - tr.y*s, tr.x*s + tr.y*c };
    Vector2 bl_ = { bl.x*c - bl.y*s, bl.x*s + bl.y*c };
    Vector2 br_ = { br.x*c - br.y*s, br.x*s + br.y*c };

    result.x = tl_.x;
    result.y = tl_.y;
    result.width = tr_.x - tl_.x;
    result.height = bl_.y - tl_.y;

    return result;
}

typedef struct bird{
    float x;
    float y;
    float Rotation;
}
Bird;

typedef struct pip{
    float x;
    float y;
    float height;
}pipe;

pipe Pipes[10];
void PipeGen(Texture2D Pipe,Texture2D Top);
bool collision(float PtakX,float PtakY,float PtakR);

int main() {

    SetRandomSeed(time(NULL));
    int randomnum;
    Pipes[0].y=350;
    Pipes[0].x=1024;
    for (int i = 1; i < 10; ++i) {
        if(Pipes[i-1].y-150>=42+64 && Pipes[i-1].y+150<=768-42-64){
            randomnum = GetRandomValue((int )Pipes[i-1].y-150,(int )Pipes[i-1].y+150);

        }else if(Pipes[i-1].y-150>=42+64){
            randomnum = GetRandomValue((int )Pipes[i-1].y-150,768-42-64);
        }else {
            randomnum = GetRandomValue(42+64,(int )Pipes[i-1].y+150);
        }
        Pipes[i].y=(float )randomnum;
        Pipes[i].x=Pipes[i-1].x+200;
    }




    const int screenWidth = 1024;
    const int screenHeight = 768;
    float move=0;
    int dir=1;
    bool down = false;
    bool start = false;
    bool end = false;
    float d=0;
    Bird ptak ;
    ptak.x=200;
    ptak.y=364;
    ptak.Rotation=0;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera");
    Texture2D Background = LoadTexture("src/Pozadi.png");
    Texture2D Ground = LoadTexture("src/Spodek.png");
    Texture2D FlappyStart = LoadTexture("src/Flappy_Start.png");
    Texture2D FlappyUp = LoadTexture("src/Flappy_Up.png");
    Texture2D Pipe = LoadTexture("src/pipe48x10.png");
    Texture2D Top = LoadTexture("src/Vrch48x22.png");

    SetTargetFPS(120);
    float up=0;
    while (!WindowShouldClose()){
        if(end){

        } else {
            move += -0.5f;
            if (move <= -(float) Ground.width) move = 0;

            if (IsKeyPressed(KEY_SPACE)) {
                start = true;
                up += 70;

            }
            if (start) {
                for (int i = 0; i < 10; ++i) {
                    Pipes[i].x=Pipes[i].x-2;
                }


                if (up >= 0) {
                    ptak.y -= 3.0f;
                    up -= 3.0f;
                    d = 30;
                    down = false;
                    ptak.Rotation = 0;

                }
                if (up < 0) {
                    ptak.y = ptak.y + 3;
                    d -= 3.0f;
                    down = true;
                    if (d <= 0) {
                        if (ptak.Rotation < 50) {
                            ptak.Rotation += 1.0f;
                        }
                        if (ptak.Rotation >= 50 && ptak.Rotation <= 90) {
                            ptak.Rotation += 3;
                        }

                    }

                }
                if(collision(ptak.x,ptak.y,ptak.Rotation)){
                    end=true;

                }
            } else{
                if(ptak.y>=364+25){
                    ptak.y=364+25;
                    dir=-1;
                } else if(ptak.y<=364-25){
                    ptak.y=364-25;
                    dir=1;
                }
                ptak.y = ptak.y + (float )dir*0.8f;
            }
        }

        BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));

        DrawTexture(Background,0,0,WHITE);

        DrawRectanglePro((Rectangle){ptak.x,ptak.y,40,40},(Vector2){0,0},0,WHITE);
        PipeGen(Pipe,Top);



        if(!start){

            DrawTextureEx(FlappyStart, (Vector2) {200, ptak.y}, 0.0f, 1.0f, WHITE);
        }
        else if(down && d<=0 ) {

            DrawTextureEx(FlappyStart, (Vector2) {200, ptak.y}, ptak.Rotation, 1.0f, WHITE);
        }
        else  {
            DrawTextureEx(FlappyUp, (Vector2) {200, ptak.y}, 0.0f, 1.0f, WHITE);
        }
        DrawTextureEx(Ground, (Vector2){move , 704.0f}, 0.0f, 1.0f, WHITE);
        DrawTextureEx(Ground, (Vector2){(float )Ground.width + move, 704.0f}, 0.0f, 1.0f, WHITE);

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(Background);
    UnloadTexture(FlappyStart);
    UnloadTexture(FlappyUp);
    UnloadTexture(Ground);
    UnloadTexture(Pipe);
    UnloadTexture(Top);
    return 0;
}

void PipeGen(Texture2D Pipe,Texture2D Top){
    int randomnum;
    if (Pipes[0].x+48<0) {
        for (int i = 0; i < 9; ++i) {
            Pipes[i] = Pipes[i+1];
        }
    }
    //rnadom position of pipe
    if(Pipes[8].y-150>=42+120 && Pipes[8].y+150<=768-42-64){
        randomnum = GetRandomValue((int )Pipes[8].y-150,(int )Pipes[8].y+150);

    }else if(Pipes[8].y-150>=42+120){
        randomnum = GetRandomValue((int )Pipes[8].y-150,768-42-64);
    }else {
        randomnum = GetRandomValue(42+120,(int )Pipes[8].y+150);
    }
    Pipes[9].y=(float )randomnum;
    Pipes[9].x=Pipes[8].x+200;
    for (int i = 0; i < 6; ++i) {
        DrawTextureEx(Top, (Vector2){Pipes[i].x , Pipes[i].y}, 0.0f, 1.0f, WHITE);
        for (int j = 0; 768>=Pipes[i].y+(float )(j*10)+22; ++j) {
            DrawTextureEx(Pipe,(Vector2){Pipes[i].x,Pipes[i].y+(float )(j*10)+22},0.0f,1.0f,WHITE);
        }
        DrawTextureEx(Top, (Vector2){Pipes[i].x+48 , Pipes[i].y-120}, 180.0f, 1.0f, WHITE);
        for (int j = 0; -50<=Pipes[i].y-(float )(j*10)-32-120; ++j) {
            DrawTextureEx(Pipe,(Vector2){Pipes[i].x,Pipes[i].y-(float )(j*10)-32-120},0.0f,1.0f,WHITE);
        }
    }

}

bool collision(float PtakX,float PtakY,float PtakR){
    Rectangle Ptak = {PtakX,PtakY,40,40};

    if(PtakY+40 >= 704){
        return true;
    }
    if(CheckCollisionRecs(Ptak,(Rectangle){Pipes[0].x,Pipes[0].y,48,768}) || CheckCollisionRecs(Ptak,(Rectangle){Pipes[1].x,Pipes[1].y,48,768})){
        return true;
    }
    if(CheckCollisionRecs(Ptak,(Rectangle){Pipes[0].x,0,48,Pipes[0].y-120}) || CheckCollisionRecs(Ptak,(Rectangle){Pipes[1].x,0,48,Pipes[1].y-120})){
        return true;
    }
    if(PtakY<0){

        if(CheckCollisionRecs(Ptak,(Rectangle){Pipes[0].x,PtakY-100,48,-1*(PtakY-100)}) ||CheckCollisionRecs(Ptak,(Rectangle){Pipes[1].x,PtakY-100,48,-1*(PtakY-100)})){
            return true;
        }
    }
    return false;
}

