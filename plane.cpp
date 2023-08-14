#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define High 25
#define Width 50

//全局变量
int position_x, position_y; //飞机位置
int enemy_x, enemy_y;
int canvas[High][Width] = { 0 };//0为空格，1为飞机

int score;


void gotoxy(int x, int y) {     //清屏
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}

void HideCursor() {
    CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

void startup()                   //数据初始化
{
    position_x = High / 2;
    position_y = Width / 2;
    canvas[position_x][position_y] = 1;
    enemy_x = 0;
    enemy_y = position_y;
    canvas[enemy_x][enemy_y] = 3;
    score = 0;
}

void show()                     //显示画面
{
    gotoxy(0,0);
    int i, j;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (canvas[i][j] == 0)
                printf(" ");
            else if (canvas[i][j] == 1)//输出飞机
                printf("*");            
            else if (canvas[i][j] == 2) //输出子弹
                printf("|");
            else if (canvas[i][j] == 3)
                printf("@");
        }
        printf("\n");
    }   
}

void updateWithoutInput()     //与用户输入无关的更新
{
    int i, j;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (canvas[i][j] == 2)
            {
                canvas[i][j] = 0;
                if (i > 0)
                    canvas[i - 1][j] = 2;
            }
        }
    }

    if ((position_x == enemy_x) && (position_y == enemy_y)) //敌机撞到我机
    {
        printf("失败！\n");
        Sleep(3000);
        system("pause");
        exit(0);
    }
}

    void updateWithInput()
    {
        char input;
        if (kbhit())
        {
            input = getch();
            if (input == 0x4b)//左
            {
                canvas[position_x][position_y] = 0;
                position_y--;
                canvas[position_x][position_y] = 1;

            }
            if (input == 0x4d)//右
            {
                canvas[position_x][position_y] = 0;
                position_y++;
                canvas[position_x][position_y] = 1;
            }

            if (input == 0x48)//上
            {
                canvas[position_x][position_y] = 0;
                position_x--;
                canvas[position_x][position_y] = 1;
            }

            if (input == 0x50)//下
            {
                canvas[position_x][position_y] = 0;
                position_x++;
                canvas[position_x][position_y] = 1;
            }

            if (input == ' ')  //发射子弹
            {
                canvas[position_x - 1][position_y] = 2;
            }

        }
    }


int main()
{
    startup();
    HideCursor();
    while (1) 
    {
        show();
        updateWithoutInput();
        updateWithInput();
    }    
    return 0;
}