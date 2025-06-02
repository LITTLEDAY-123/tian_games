#include <raylib.h>
#include <iostream>
using namespace std;

int player1_score=0;
int player2_score=0;

class Ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, BLUE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;
        if(y + radius>=GetScreenHeight()|| y-radius<=0)
        {
            speed_y *=-1;
        }
        if(x+radius>=GetScreenWidth())
        {
            player2_score++;
            ReSetBall();
        }
        if( x-radius <=0)

        {
            player1_score++; 
            ReSetBall();
        }
    }
    void ReSetBall()
{
    x=GetScreenWidth()/2;
    y=GetScreenHeight()/2;

    int speed_choices[2]={-1,1};
    speed_x=7*speed_choices[GetRandomValue(0,1)];
    speed_y=7*speed_choices[GetRandomValue(0,1)];
}
};


class Paddle{
    public:
    float x,y;
    float width,height;
    int speed;
    void Draw(){
 DrawRectangle(x,y,width,height ,BLACK);

 }


  
    void  Update1(){
        if(IsKeyDown(KEY_UP))
        {
            y=y-speed;
        }
        if(IsKeyDown(KEY_DOWN))
        {
            y=y+speed;
        }
        if (y < 0) y = 0;
        if (y + height > GetScreenHeight()) y = GetScreenHeight() - height;
       
    }
     void  Update2(){
        if(IsKeyDown(KEY_W))
        {
            y=y-speed;
        }
        if(IsKeyDown(KEY_S))
        {
            y=y+speed;
        }
        if (y < 0) y = 0;
        if (y + height > GetScreenHeight()) y = GetScreenHeight() - height;
}
};




Ball ball;
Paddle player1;
Paddle player2;

int main() {
    InitWindow(1280, 800, "GAME");
    SetTargetFPS(60);

    
    ball.radius = 20;
    ball.x = 1280 / 2;
    ball.y = 800 / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player1.width=25;
    player1.height=120;
    player1.x=1280-player1.width-10;
    player1.y=800/2-player1.height/2;
    player1.speed= 6;

    player2.width=25;
    player2.height=120;
    player2.x=10;
    player2.y=800/2-player2.height/2;
    player2.speed= 6;
    
   
    while (!WindowShouldClose()) {

        ball.Update();
        player1.Update1();
        player2.Update2();

        BeginDrawing();
        ClearBackground(WHITE);

        ball.Draw();
        
        DrawCircle(1280 / 2, 800 / 2, 50, BLUE);
        DrawLine(1280 / 2, 0, 1280 / 2, 800, BLACK);
       
        
player1.Draw();
player2.Draw();
DrawText(TextFormat("%i",player2_score),1280/4,20,80,PINK);
DrawText(TextFormat("%i",player1_score),1280/4+680,20,80,PINK);
if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player1.x,player1.y,player1.width,player1.height}))
        {
            ball.speed_x*=-1;
        }
       
        if (CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player2.x,player2.y,player2.width,player2.height}))
        {
            ball.speed_x*=-1;
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
