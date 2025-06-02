#include <raylib.h>
#include <iostream>
using namespace std;


int player1_score=0;
int cpu_score=0;

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
            cpu_score++;
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
    speed_x*=speed_choices[GetRandomValue(0,1)];
    speed_y*=speed_choices[GetRandomValue(0,1)];
}

};

class Paddle{
    protected:
    void LimitMovement(){
         if (y < 0)
        {
         y = 0;
        }
        if (y + height > GetScreenHeight()) 
    {
        y = GetScreenHeight() - height;
       
    }
    }
    public:
    float x,y;
    float width,height;
    int speed;
    void Draw(){
 DrawRectangle(x,y,width,height ,BLACK);

 }



  
    void  Update(){
        if(IsKeyDown(KEY_UP))
        {
            y=y-speed;
        }
        if(IsKeyDown(KEY_DOWN))
        {
            y=y+speed;
        }

       LimitMovement();

   
}
};

class CpuPaddle:public Paddle{
    public:
    void Update (int ball_y)
    {
        if(y+height/2>ball_y)
        {
            y=y-speed;
        }
        if(y+height/2<=ball_y)
        {
            y=y+speed;
        }
        LimitMovement();
    }


};

Ball ball;
Paddle player1;
CpuPaddle cpu;


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

    
    cpu.height=120;
    cpu.width=25;
    cpu.x=10;
    cpu.y=800/2-cpu.height/2;
    cpu.speed=6;

    while (!WindowShouldClose()) {

        ball.Update();
        player1.Update();
        cpu.Update(ball.y);
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{player1.x,player1.y,player1.width,player1.height}))
        {
            ball.speed_x*=-1;
        }
       
        if (CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cpu.x,cpu.y,cpu.width,cpu.height}))
        {
            ball.speed_x*=-1;
        }
        

        BeginDrawing();
        ClearBackground(WHITE);

        ball.Draw();
        cpu.Draw();
        DrawCircle(1280 / 2, 800 / 2, 50, BLUE);
        DrawLine(1280 / 2, 0, 1280 / 2, 800, BLACK);
       
        
player1.Draw();
DrawText(TextFormat("%i",cpu_score),1280/4,20,80,PINK);
DrawText(TextFormat("%i",player1_score),640+1280/4,20,80,PINK);


        EndDrawing();
    }

    CloseWindow();
    return 0;
}
