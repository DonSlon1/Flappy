#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <math.h>



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
Vector2 Center;
void CenterCalculate(float sx,float sy,float rotation);
void FullPipeGen();
void PipeGen(Texture2D Pipe,Texture2D Top);
bool collision(float PtakX,float PtakY,float PtakR);

int main() {

    SetRandomSeed(time(NULL));
    int MaxScore=0;
    int score=0;
    Rectangle Button={(1024.0f/2),340,100,30};


    const int screenWidth = 1024;
    const int screenHeight = 768;
    float move=0;
    int dir=1;
    bool down = false;
    bool start = false;
    bool end = false,Restart=false;
    float d=0;
    Bird ptak ;
    ptak.x=200;
    ptak.y=364;
    ptak.Rotation=0;
    Vector2 mousePoint = { 0.0f, 0.0f };
    FullPipeGen();
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
            mousePoint = GetMousePosition();
            if(CheckCollisionPointRec(mousePoint,Button) && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){

                Restart=true;
            }
            if (IsKeyPressed(KEY_SPACE)) {
                Restart=true;
            }
            if(Restart){
                score=0;
                d=0;
                dir=1;
                FullPipeGen();
                ptak.x=200;
                ptak.y=364;
                ptak.Rotation=0;
                down = false;
                start = false;
                end = false;
                Restart=false;
            }
        } else {
            move += -0.5f;
            if (move <= -(float) Ground.width) move = 0;

            if (IsKeyPressed(KEY_SPACE)) {
                start = true;
                up = 70;

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
                CenterCalculate(ptak.x,ptak.y+40,ptak.Rotation);
                if(Pipes[0].x == 200-50 || Pipes[1].x == 200-50){
                    score++;
                    if(score>=MaxScore){
                        MaxScore=score;
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
        PipeGen(Pipe,Top);


        if(!end){
            Vector2 FontSize=MeasureTextEx(GetFontDefault(),TextFormat("%d",score),50,8);
            DrawTextEx(GetFontDefault(),TextFormat("%d",score), (Vector2){1024.0f/2-FontSize.x/2, 150},50,8,WHITE);
        }
        if(!start){

            DrawTextureEx(FlappyStart, (Vector2) {200, ptak.y}, 0.0f, 1.0f, WHITE);
        }
        else if(down && d<=0 ) {

            DrawTextureEx(FlappyStart, (Vector2) {200, ptak.y}, ptak.Rotation, 1.0f, WHITE);
        }
        else  {
            DrawTextureEx(FlappyUp, (Vector2) {200, ptak.y}, 0.0f, 1.0f, WHITE);
        }
        if(end){

            DrawRectangleRounded((Rectangle){(1024.0f/2)-0.2f,150-0.2f,100+2,150+2},0.2f,1, (Color){222,216,149,255});
            DrawRectangleRoundedLines((Rectangle){1024.0f/2,150,100,150},0.2f,1,5,BLACK);
            Vector2 FontC= MeasureTextEx(GetFontDefault(),"SCORE",10,5);
            DrawTextEx(GetFontDefault(),"SCORE",(Vector2){1024.0f/2+50-FontC.x/2,150+60-FontC.x/2},10,5,(Color){252, 120, 88,255});

            FontC= MeasureTextEx(GetFontDefault(), TextFormat("%d",score),25,5);
            DrawTextEx(GetFontDefault(),TextFormat("%d",score),(Vector2){1024.0f/2+50-FontC.x/2,150+60-FontC.x/2},25,5,WHITE);

            FontC= MeasureTextEx(GetFontDefault(),"MAX SCORE",10,5);
            DrawTextEx(GetFontDefault(),"MAX SCORE",(Vector2){1024.0f/2+50-FontC.x/2,150+50-FontC.x/2+80},10,5,(Color){252, 120, 88,255});

            FontC= MeasureTextEx(GetFontDefault(), TextFormat("%d",MaxScore),25,5);
            DrawTextEx(GetFontDefault(),TextFormat("%d",MaxScore),(Vector2){1024.0f/2+50-FontC.x/2,150+50+60-FontC.x/2},25,5,WHITE);
            DrawRectangleRec((Rectangle){(1024.0f/2)-6,340-6,114,46},BLACK);
            DrawRectangleRec((Rectangle){(1024.0f/2)-4,340-4,108,38},WHITE);
            DrawRectangleRec((Rectangle){(1024.0f/2),340,100,30},(Color){232, 97, 1,255});

            FontC= MeasureTextEx(GetFontDefault(),"RESTART",17,3);
            DrawTextEx(GetFontDefault(),"RESTART",(Vector2){(1024.0f/2)+50-FontC.x/2    ,340+15-FontC.y/2},17,3,WHITE);

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

    if(PtakY+40 >= 704){
        return true;
    }
    if(CheckCollisionCircleRec(Center,16,(Rectangle){Pipes[0].x,Pipes[0].y,48,768})|| CheckCollisionCircleRec(Center,16,(Rectangle){Pipes[1].x,Pipes[1].y,48,768})){
        return true;
    }
    if(CheckCollisionCircleRec(Center,16,(Rectangle){Pipes[0].x,0,48,Pipes[0].y-120}) || CheckCollisionCircleRec(Center,16,(Rectangle){Pipes[1].x,0,48,Pipes[1].y-120})){
        return true;
    }
    if(PtakY<0){

        if(CheckCollisionCircleRec(Center,16,(Rectangle){Pipes[0].x,PtakY-100,48,-1*(PtakY-100)}) ||CheckCollisionCircleRec(Center,16,(Rectangle){Pipes[1].x,PtakY-100,48,-1*(PtakY-100)})){
            return true;
        }
    }
    return false;
}
void CenterCalculate(float sx,float sy,float rotation){


    //stupně
    double alfa=rotation*(PI/180);
    double beta=(180-(alfa*(180/PI)+90))*(PI/180);

    //delka strran
    double b=(sin(beta)/ sin(90*(PI/180)))*40;
    double a=(sin(alfa)/ sin(beta))*b;

    Vector2 B={sx+b,sy-a};
    Vector2 C={sx-a,sy-b};
    Center.x = (B.x+C.x)/2;
    Center.y = ((B.y+C.y)/2);
}

void FullPipeGen(){
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
}