#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include<time.h>
#include<math.h>
int j;
#define WIDTH 160                  //170 40
#define HEIGHT 40
#define MAX_BULLETS 100
int jet_health;
char jet[5][9];
char enemy1[3][13];
char air_bomb[4][5];
char aidplane[3][13];
char missilee[4][5];
char missilee2[2][1];
char enemyjet[4][5];
char name [20];
void start()
{
    printf("\e[?25l");
    system("cls");
    gotoxy(WIDTH/2 - 11, HEIGHT/2 );
    printf("\033[0;35menter your name : \033[0m");
    gets(name);
    int result;
    do
    {
        int gameoverr;
        result = menu();
        if(result == 1)
        {
            gameoverr = startgame4();
            if(gameoverr==0)
            {
                printf("\033[0;35m\nPress any key to go back to the main menu...\033[0m");
                getch();    
            }
        }
        else if(result == 2)
        {
            int second_result = second_menu();
            if(second_result == 1)
            {
                gameoverr = startgame4();
                if(gameoverr==0)
                {
                    printf("\033[0;35m\nPress any key to go back to the main menu...\033[0m");
                    getch();    
                }
            }
            else if(second_result == 2)
            {  
                gameoverr = startgame3();
                if(gameoverr==0)
                {
                    printf("\033[0;35m\nPress any key to go back to the main menu...\033[0m");
                    getch();    
                }
            }
            else if(second_result == 3)
            {
                gameoverr = startgame2();
                if(gameoverr==0)
                {
                    printf("\033[0;35m\nPress any key to go back to the main menu...\033[0m");
                    getch();    
                }
            }
            else if(second_result == 4)
            {
                gameoverr = startgame1();
                if(gameoverr==0)
                {
                    printf("\033[0;35m\nPress any key to go back to the main menu...\033[0m");
                    getch();    
                }
            }
        }
        else if(result == 3)
        {
            char filename[] = "temp.txt";
            system("cls");
            printFileInReverse(filename);
        }
        else if(result == 4)
        {
            system("cls");
            gotoxy(WIDTH/2 , HEIGHT/2);
            printf("\033[0;35mBYE %s \033[0m", name);
        }
    } while (result != 4);
}
struct tm * timeeee()
{
    time_t currentTime;
    currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    return localTime;
}
void timeee()
{
        COORD coord;
        coord.X = WIDTH/2-7;
        coord.Y = HEIGHT + 1;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
        printf("\033[0;33mtime : %d\033[0m",j/10);
}
void printhealth()
{
	COORD coord;
    coord.X = WIDTH -14;
    coord.Y = HEIGHT + 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("\033[0;32mhealth : %d\033[0m",jet_health);
}
void printscore()
{
    COORD coord;
    coord.X = 1;
    coord.Y = HEIGHT + 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    printf("\033[0;32mscore : %d\033[0m",j/4);
}
typedef struct bullet
{
    int x;
    int y;
    int active;
} bullet;
typedef struct airbomb
{
    int x;
    int y;
    int active;
} airbomb;
typedef struct enemy
{
    int x;
    int y;
    int health;
    int active;
} enemy;
enemy enemies[3];
bullet bullets[MAX_BULLETS];
airbomb bomb;
airbomb missile;
airbomb missile2;
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void draw(int x, int y, char ch)
{
    gotoxy(x,y);
    printf("%c", ch);
}
int gameover()
{
    struct tm * localtime=timeeee();
    FILE *ftemp;
    ftemp=fopen("temp.txt","a");
    fprintf(ftemp ,"the latest lost : %02d:%02d:%02d\t", localtime->tm_hour, localtime->tm_min, localtime->tm_sec);
    fprintf(ftemp ,"score : %d\t", j/4);
    fprintf(ftemp ,"time:%d s\t\t" ,j/10 );
    fprintf(ftemp , "name : %s\n",name);
    fclose(ftemp);
    system("cls");
    gotoxy(WIDTH/2 , HEIGHT/2);
    printf("\033[0;31mGAME OVER %s!\033[0m",name);
    gotoxy(WIDTH/2 , HEIGHT/2 + 1);
    printf("\033[0;31myour score : %d\033[0m",j/10);
    return 0;
}
void makeenemy2()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<5;j++)
        {
            enemyjet[i][j]=' ';
        }
    }
    enemyjet[0][0]='/';enemyjet[0][1]='-';enemyjet[0][2]='-';enemyjet[0][3]='-';enemyjet[0][4]='\\';
    enemyjet[1][0]='\\';enemyjet[1][4]='/';
    enemyjet[2][1]='\\';enemyjet[2][2]='+';enemyjet[2][3]='/';
    enemyjet[3][2]='*';
}
void makeenemy1()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<13;j++)
        {
            enemy1[i][j]=' ';
        }
    }
    enemy1[0][0]=' ';enemy1[0][1]=' ';enemy1[0][2]='-';enemy1[0][3]='-';enemy1[0][4]='-';enemy1[0][5]='-';enemy1[0][6]='-';enemy1[0][7]='+';enemy1[0][8]='-';enemy1[0][9]='-';enemy1[0][10]='-';enemy1[0][11]='-';enemy1[0][12]='-';
    enemy1[1][0]='*';enemy1[1][1]='\\';enemy1[1][2]='=';enemy1[1][3]='=';enemy1[1][4]='=';enemy1[1][5]='<';enemy1[1][6]='[';enemy1[1][7]='_';enemy1[1][8]=']';enemy1[1][9]='L';enemy1[1][10]=')';
    enemy1[2][0]=' ';enemy1[2][1]=' ';enemy1[2][2]=' ';enemy1[2][3]=' ';enemy1[2][4]=' ';enemy1[2][5]=' ';enemy1[2][6]='\'';enemy1[2][7]=' ';enemy1[2][8]='\'';enemy1[2][9]=' ';enemy1[2][10]=' ';
}
void makemissile2()
{
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<1;j++)
        {
            missilee2[i][j]=' ';
        }
    }
    missilee2[0][0]='!';
    missilee2[1][0]='*';
}
void makemissile()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<5;j++)
        {
            missilee[i][j]=' ';
        }
    }
    missilee[0][0]='\\';missilee[0][1]='+';missilee[0][2]='+';missilee[0][3]='+';missilee[0][4]='/';
    missilee[1][1]='|';missilee[1][2]='+';missilee[1][3]='|';
    missilee[2][1]='\\';missilee[2][2]='+';missilee[2][3]='/';
    missilee[3][2]='*';
}
void makeairbomb()
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<5;j++)
        {
            air_bomb[i][j]=' ';
        }
    }
    air_bomb[0][1]='_';air_bomb[0][2]='!';air_bomb[0][3]='_';
    air_bomb[1][0]='(';air_bomb[1][1]='_';air_bomb[1][2]='o';air_bomb[1][3]='_';air_bomb[1][4]=')';
    air_bomb[2][1]='\'';air_bomb[2][2]='\'';air_bomb[2][3]='\'';
}
void makeaidplane()
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<13;j++)
        {
            aidplane[i][j]=' ';
        }
    }
    aidplane[0][4]='_';aidplane[0][5]='_';aidplane[0][6]='!';aidplane[0][7]='_';aidplane[0][8]='_';
    aidplane[1][0]='_';aidplane[1][1]='_';aidplane[1][2]='_';aidplane[1][3]='_';aidplane[1][4]='_';aidplane[1][5]='(';aidplane[1][6]='_';aidplane[1][7]=')';aidplane[1][8]='_';aidplane[1][9]='_';aidplane[1][10]='_';aidplane[1][11]='_';aidplane[1][12]='_';
    aidplane[2][3]='!';aidplane[2][6]='!';aidplane[2][9]='!';
}
void makejet()
{
    jet_health=20;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            jet[i][j] = ' ';
        }
    }

    jet[0][3] = '/';jet[0][4] = '-';jet[0][5] = '\\';
    jet[1][2] = '/';jet[1][3] = '/';jet[1][4] = '-';jet[1][5] = '\\';jet[1][6] = '\\';
    jet[2][1] = '/';jet[2][2] = '\'';jet[2][3] = '\\';jet[2][4] = '0';jet[2][5] = '/';jet[2][6] = '\'';jet[2][7] = '\\';
    jet[3][0] = '/';jet[3][1] = ' ';jet[3][2] = '/';jet[3][3] = ' ';jet[3][4] = '-';jet[3][5] = ' ';jet[3][6] = '\\';jet[3][7] = ' ';jet[3][8] = '\\';
    jet[4][0] = '\\';jet[4][1] = '_';jet[4][2] = '/';jet[4][3] = '-';jet[4][4] = '-';jet[4][5] = '-';jet[4][6] = '\\';jet[4][7] = '_';jet[4][8] = '/';
}
void init_bullets()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        bullets[i].x = 0;
        bullets[i].y = 0;
        bullets[i].active = 0;
    }
}
void fire_bullet(int x, int y)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active == 0)
        {
            bullets[i].active = 1;
            bullets[i].x = x + 4;
            bullets[i].y = y - 1;
            break;
        }
    }
}
void airbomb_activating()
{
    makeairbomb();
    srand(j+19);
    bomb.x = rand() % WIDTH + 1;
    bomb.y=1;
    bomb.active=1;
}
void missile_activating()
{
    makemissile();
    missile.x=enemies[1].x;
    missile.y=enemies[1].y;
    missile.active=1;
}
void missile2_activating()
{
    makemissile2();
    missile2.x=enemies[0].x+2;
    missile2.y=enemies[0].y;
    missile2.active=1;
}
void aidplane_activating()
{
    makeaidplane();
    srand(2*j);
    enemies[2].x = rand() % WIDTH + 13;
    enemies[2].y=1;
    enemies[2].active=1;
    enemies[2].health=3;
}
void enemy1_activating()
{
    makeenemy1();
    srand(3*j);
    enemies[1].x = 1;
    enemies[1].y = rand() %(HEIGHT/2 + 3) + 3;
    enemies[1].health=2;
    enemies[1].active=1;
}
void enemy2_activating()
{
    makeenemy2();
    srand(9*j+1);
    enemies[0].x=rand()% WIDTH + 1;
    enemies[0].y=1;
    enemies[0].active=1;
    enemies[0].health=2;
}
void update_missile2()
{
    if(missile2.active==1)
    {
        for(int i=0;i<2;i++)
        {
            for(int j=0;j<1;j++)
            {
                erase_bullet(missile2.x+j , missile2.y+i);
            }
        }
        missile2.y+=2;
        if(missile2.y >=HEIGHT)
        {
            missile2.active=0;
            missile2_activating();
        }
        else
        {
            for(int i=0;i<2;i++)
            {
                for(int j=0;j<1;j++)
                {
                    draw(missile2.x+j , missile2.y+i  , missilee2[i][j]);
                }
            }
        }
    }
}
void update_missile()
{
    if(missile.active==1)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<5;j++)
            {
                erase_bullet(missile.x+j , missile.y+i);
            }
        }
        missile.y++;
        if(missile.y >=HEIGHT)
        {
            missile.active=0;
            missile_activating();
        }
        else
        {
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<5;j++)
                {
                    draw(missile.x+j , missile.y+i  , missilee[i][j]);
                }
            }
        }
    }
}
void update_airbomb()
{
    if(bomb.active==1)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<5;j++)
            {
                erase_bullet(bomb.x+j , bomb.y+i);
            }
        }
        bomb.y++;
        if(bomb.y >HEIGHT)
        {
            bomb.active=0;
            airbomb_activating();
        }
        else
        {
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<5;j++)
                {
                    draw(bomb.x+j , bomb.y+i  , air_bomb[i][j]);
                }
            }
        }
    }
    else if(bomb.active==0)
    {
        airbomb_activating();
    }
}
void update_enemy2()
{
    if(enemies[0].active==1)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<5;j++)
            {
                erase_bullet(enemies[0].x+j , enemies[0].y+i);
            }
        }
        enemies[0].y+=2;
        if(enemies[0].y >HEIGHT)
        {
            enemies[0].active=0;
            enemy2_activating();
            missile2_activating();
        }
        else
        {
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<5;j++)
                {
                    draw(enemies[0].x+j , enemies[0].y+i  , enemyjet[i][j]);
                }
            }
        }
    }
}
void update_enemy()
{
    if(enemies[1].active==1)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<13;j++)
            {
                erase_bullet(enemies[1].x+j , enemies[1].y+i);
            }
        }
        enemies[1].x+=2;
        if(enemies[1].x + 14 >WIDTH)
        {
            enemies[1].active=0;
            enemy1_activating();
            missile_activating();
        }
        else
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<13;j++)
                {
                    draw(enemies[1].x+j , enemies[1].y+i  , enemy1[i][j]);
                }
            }
        }
    }
}
void update_aidplane()
{
    if(enemies[2].active==1)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<13;j++)
            {
                erase_bullet(enemies[2].x+j , enemies[2].y+i);
            }
        }
        enemies[2].y+=2;
        if(enemies[2].y + 4>HEIGHT)
        {
            enemies[2].active=0;
            aidplane_activating();
        }
        else
        {
            for(int i=0;i<3;i++)
            {
                for(int j=0;j<13;j++)
                {
                    draw(enemies[2].x+j , enemies[2].y+i  , aidplane[i][j]);
                }
            }
        }
    }
}
void erase_bullet(int x, int y)
{
    draw(x, y, ' ');
}
void update_bullets()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (bullets[i].active == 1)
        {
            erase_bullet(bullets[i].x, bullets[i].y);
            bullets[i].y-=6;
            if (bullets[i].y < 0)
            {
                bullets[i].active = 0;
            }
            else
            {
                draw(bullets[i].x, bullets[i].y, '!');
            }
        }
    }
}
void check_collision_with_jet()
{
    if (bullets[0].active == 1)
    {
        int e_top = enemies[0].y - 4;
        int e_bottom = enemies[0].y+4;
        int e_left = enemies[0].x;
        int e_right = enemies[0].x + 14;
        for(int k=0;k<MAX_BULLETS;k++)
        {
            if(bullets[k].active==1)
            {
                if (bullets[k].y >= e_top && bullets[k].y <= e_bottom &&bullets[k].x >= e_left && bullets[k].x <= e_right)
                {
                    enemies[0].health--;
                    if(enemies[0].health==0)
                    {
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<5;j++)
                            {
                                enemyjet[i][j]=' ';
                            }
                        }
                        missile2.active=0;
                    }
                    bullets[k].active=0;
                }
            }
        }
    }
}
void check_collision_with_helicopter()
{
    if (bullets[0].active == 1)
    {
        int e_top = enemies[1].y - 4;
        int e_bottom = enemies[1].y + 4;
        int e_left = enemies[1].x-4;
        int e_right = enemies[1].x + 18;
        for(int k=0;k<MAX_BULLETS;k++)
        {
            if(bullets[k].active==1)
            {
                if (bullets[k].y >= e_top && bullets[k].y <= e_bottom &&bullets[k].x >= e_left && bullets[k].x <= e_right)
                {
                    enemies[1].health--;
                    if(enemies[1].health==0)
                    {
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<13;j++)
                            {
                                enemy1[i][j]=' ';
                            }
                        }
                        missile.active=0;
                    }
                    bullets[k].active=0;
                }
            }
        }
    }
}
void check_collision_with_aidplane(int x, int y)
{
    if (bullets[0].active == 1)
    {
        int e_top = enemies[2].y - 4;
        int e_bottom = enemies[2].y + 4;
        int e_left = enemies[2].x;
        int e_right = enemies[2].x + 14;
        for(int k=0;k<MAX_BULLETS;k++)
        {
            if(bullets[k].active==1)
            {
                if (bullets[k].y >= e_top && bullets[k].y <= e_bottom &&bullets[k].x >= e_left && bullets[k].x <= e_right)
                {
                    enemies[2].health--;
                    if(enemies[2].health==0)
                    {
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<13;j++)
                            {
                                aidplane[i][j]=' ';
                            }
                        }
						aidplane[0][0]=' ';aidplane[0][1]='_';aidplane[0][2]='_';aidplane[0][3]=' ';
						aidplane[1][0]='|';aidplane[1][1]='_';aidplane[1][2]='_';aidplane[1][3]='|';
						/*if(e_top<y && e_bottom>y+5 && e_left>x && e_right<x+12)
						{
							jet_health++;
						}*/
                        jet_health++;
                        if(jet_health==11)
                        {
                            jet_health--;
                        }
                    }
                    bullets[k].active=0;
                }
            }
        }
    }
}
void check_collision_with_bomb(int x , int y)
{
    if (bomb.active == 1)
    {
        int jet_top = y-3;
        int jet_bottom = y + 5 ;
        int jet_left = x-5;
        int jet_right = x + 15;
        int bomb_top=bomb.y-4;
        int bomb_bottom=bomb.y;
        int bomb_left=bomb.x;
        int bomb_right=bomb.x+6;
        if (jet_top <= bomb_top && jet_bottom >= bomb_bottom && jet_left <= bomb_left && jet_right >= bomb_right)
        {
            jet_health-=5;
            if(jet_health<=0)
            {
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<5;j++)
                    {
                        air_bomb[i][j]=' ';
                    }
                }
            }
            bomb.active=0;
        }
    }
}
void check_jet_collision_with_helicopter(int x , int y)
{
    if (enemies[1].active == 1)
    {
        int jet_top = y - 5;
        int jet_bottom = y + 6 ;
        int jet_left = x -1;
        int jet_right = x + 10;
        int helicopter_top=enemies[1].y-3;
        int helicopter_bottom=enemies[1].y;
        int helicopter_left=enemies[1].x;
        int helicopter_right=enemies[1].x+2;
        if (jet_top <= helicopter_top && jet_bottom >= helicopter_bottom && jet_left <= helicopter_left && jet_right >= helicopter_right)
        {
            jet_health-=3;
            if(jet_health<=0)
            {
                for(int i=0;i<3;i++)
                {
                    for(int j=0;j<13;j++)
                    {
                        enemy1[i][j]=' ';
                    }
                }
                enemies[1].active=0;
            }
        }
    }
}
void check_jet_collision_with_aidplane(int x , int y)
{
    if (enemies[2].active == 1)
    {
        int jet_top = y - 5;
        int jet_bottom = y + 6 ;
        int jet_left = x -2;
        int jet_right = x + 12;
        int aidplane_top=enemies[2].y-3;
        int aidplane_bottom=enemies[2].y;
        int aidplane_left=enemies[2].x;
        int aidplane_right=enemies[2].x+13;
        if (jet_top <= aidplane_top && jet_bottom >= aidplane_bottom && jet_left <= aidplane_left && jet_right >= aidplane_right)
        {
            jet_health--;
            if(jet_health<=0)
            {
                for(int i=0;i<3;i++)
                {
                    for(int j=0;j<13;j++)
                    {
                        aidplane[i][j]=' ';
                    }
                }
                enemies[2].active=0;
            }
        }
    }
}
void check_jet_collision_with_enemyjet(int x , int y)
{
    if (enemies[0].active == 1)
    {
        int jet_top = y;
        int jet_bottom = y + 6 ;
        int jet_left = x -2;
        int jet_right = x + 10;
        int enemyjet_top=enemies[0].y-4;
        int enemyjet_bottom=enemies[0].y;
        int enemyjet_left=enemies[0].x;
        int enemyjet_right=enemies[0].x+5;
        if (jet_top <= enemyjet_top && jet_bottom >= enemyjet_bottom && jet_left <= enemyjet_left && jet_right >= enemyjet_right)
        {
            jet_health-=2;
            if(jet_health<=0)
            {
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<5;j++)
                    {
                        enemyjet[i][j]=' ';
                    }
                }
                enemies[0].active=0;
            }
        }
    }
}
void check_collision_with_missile2(int x , int y)
{
    if (missile2.active == 1)
    {
        int jet_top = y;
        int jet_bottom = y + 5 ;
        int jet_left = x;
        int jet_right = x + 10;
        int missile2_top=missile2.y-2;
        int missile2_bottom=missile2.y;
        int missile2_left=missile2.x;
        int missile2_right=missile2.x+2;
        if (jet_top <= missile2_top && jet_bottom >= missile2_bottom && jet_left <= missile2_left && jet_right >= missile2_right)
        {
            jet_health-=2;
            if(jet_health<=0)
            {
                for(int i=0;i<2;i++)
                {
                    for(int j=0;j<1;j++)
                    {
                        missilee2[i][j]=' ';
                    }
                }
            }
            missile2.active=0;
        }
    }
}
void check_collision_with_missile(int x , int y)
{
    if (missile.active == 1)
    {
        int jet_top = y;
        int jet_bottom = y + 5 ;
        int jet_left = x-5;
        int jet_right = x + 15;
        int missile_top=missile.y-4;
        int missile_bottom=missile.y;
        int missile_left=missile.x;
        int missile_right=missile.x+6;
        if (jet_top <= missile_top && jet_bottom >= missile_bottom && jet_left <= missile_left && jet_right >= missile_right)
        {
            jet_health-=5;
            if(jet_health<=0)
            {
                for(int i=0;i<4;i++)
                {
                    for(int j=0;j<5;j++)
                    {
                        missilee[i][j]=' ';
                    }
                }
            }
            missile.active=0;
        }
    }
}
int startgame1()
{
    makejet();
    init_bullets();
    airbomb_activating();
    makeenemy1();
    enemy1_activating();
    missile_activating();
    enemy2_activating();
    missile2_activating();
    aidplane_activating();
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    char c;
    int jj=0;
    while (1)
    {
        timeee();
        printscore();
        printhealth();
        jj++;
        j=jj;
        if (_kbhit())
        {
            c = getch();
            switch (c)
            {
            case 'w':
                y-=3;
                break;
            case 's':
                y+=3;
                break;
            case 'a':
                x-=3;
                break;
            case 'd':
                x+=3;
                break;
            case ' ':
                fire_bullet(x, y);
                break;
            default:
                break;
            }
        }
        system("cls");
        if (y < 0)
            y = 0;
        if (y >= HEIGHT-5)
            y = HEIGHT - 5;
        if (x < 0)
            x = 0;
        if (x >= WIDTH-12)
            x = WIDTH - 12;
        int tempX = x;
        int tempY = y;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                draw(tempX++, tempY, jet[i][j]);
            }
            printf("\n");
            tempY++;
            tempX = x;
        }
        update_bullets();
        if(j/10 > 3)
        {
            update_airbomb();
            check_collision_with_bomb(x,y);
            update_aidplane();
            check_jet_collision_with_aidplane(x , y);
            check_collision_with_aidplane(x , y);
            update_enemy();
            update_missile();
            check_collision_with_helicopter();
            check_collision_with_missile(x , y);
            check_jet_collision_with_helicopter(x , y);
            update_enemy2();
            update_missile2();
            check_collision_with_jet();
            check_jet_collision_with_enemyjet(x , y);
            check_collision_with_missile2(x , y);
        }
        if(jet_health<=0)
        {
            int gameoverr=gameover();
            return gameoverr;
        }
    }
}
int startgame2()
{
    makejet();
    init_bullets();
    airbomb_activating();
    makeenemy1();
    enemy1_activating();
    missile_activating();
    enemy2_activating();
    missile2_activating();
    aidplane_activating();
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    char c;
    int jj=0;
    while (1)
    {
        timeee();
        printscore();
        printhealth();
        jj++;
        j=jj;
        if (_kbhit())
        {
            c = getch();
            switch (c)
            {
            case 'w':
                y-=4;
                break;
            case 's':
                y+=4;
                break;
            case 'a':
                x-=4;
                break;
            case 'd':
                x+=4;
                break;
            case ' ':
                fire_bullet(x, y);
                break;
            default:
                break;
            }
        }
        system("cls");
        if (y < 0)
            y = 0;
        if (y >= HEIGHT-5)
            y = HEIGHT - 5;
        if (x < 0)
            x = 0;
        if (x >= WIDTH-12)
            x = WIDTH - 12;
        int tempX = x;
        int tempY = y;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                draw(tempX++, tempY, jet[i][j]);
            }
            printf("\n");
            tempY++;
            tempX = x;
        }
        update_bullets();
        if(j/10 >3)
        {
            update_airbomb();
            check_collision_with_bomb(x,y);
            update_aidplane();
            check_jet_collision_with_aidplane(x , y);
            check_collision_with_aidplane(x , y);
            update_enemy();
            update_missile();
            check_collision_with_helicopter();
            check_collision_with_missile(x , y);
            check_jet_collision_with_helicopter(x , y);
        }
        if(j/10 > 15)
        {
            update_enemy2();
            update_missile2();
            check_collision_with_jet();
            check_jet_collision_with_enemyjet(x , y);
            check_collision_with_missile2(x , y);
        }
        if(jet_health<=0)
        {
            int gameoverr=gameover();
            return gameoverr;
        }
    }
}
int startgame3()
{
    makejet();
    init_bullets();
    airbomb_activating();
    makeenemy1();
    enemy1_activating();
    missile_activating();
    enemy2_activating();
    missile2_activating();
    aidplane_activating();
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    char c;
    int jj=0;
    while (1)
    {
        timeee();
        printscore();
        printhealth();
        jj++;
        j=jj;
        if (_kbhit())
        {
            c = getch();
            switch (c)
            {
            case 'w':
                y-=5;
                break;
            case 's':
                y+=5;
                break;
            case 'a':
                x-=5;
                break;
            case 'd':
                x+=5;
                break;
            case ' ':
                fire_bullet(x, y);
                break;
            default:
                break;
            }
        }
        system("cls");
        if (y < 0)
            y = 0;
        if (y >= HEIGHT-5)
            y = HEIGHT - 5;
        if (x < 0)
            x = 0;
        if (x >= WIDTH-12)
            x = WIDTH - 12;
        int tempX = x;
        int tempY = y;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                draw(tempX++, tempY, jet[i][j]);
            }
            printf("\n");
            tempY++;
            tempX = x;
        }
        update_bullets();
        if(j/10 >3)
        {
            update_airbomb();
            check_collision_with_bomb(x,y);
            update_aidplane();
            check_jet_collision_with_aidplane(x , y);
            check_collision_with_aidplane(x , y);
        }
        if(j/10 >15)
        {
            update_enemy();
            update_missile();
            check_collision_with_helicopter();
            check_collision_with_missile(x , y);
            check_jet_collision_with_helicopter(x , y);
        }
        if(j/10 > 30)
        {
            update_enemy2();
            update_missile2();
            check_collision_with_jet();
            check_jet_collision_with_enemyjet(x , y);
            check_collision_with_missile2(x , y);
        }
        if(jet_health<=0)
        {
            int gameoverr=gameover();
            return gameoverr;
        }
    }
}
int startgame4()
{
    makejet();
    init_bullets();
    airbomb_activating();
    makeenemy1();
    enemy1_activating();
    missile_activating();
    enemy2_activating();
    missile2_activating();
    aidplane_activating();
    int x = WIDTH / 2;
    int y = HEIGHT / 2;
    char c;
    int jj=0;
    while (1)
    {
        timeee();
        printscore();
        printhealth();
        jj++;
        j=jj;
        if (_kbhit())
        {
            c = getch();
            switch (c)
            {
            case 'w':
                y-=5;
                break;
            case 's':
                y+=5;
                break;
            case 'a':
                x-=5;
                break;
            case 'd':
                x+=5;
                break;
            case ' ':
                fire_bullet(x, y);
                break;
            default:
                break;
            }
        }
        system("cls");
        if (y < 0)
            y = 0;
        if (y >= HEIGHT-5)
            y = HEIGHT - 5;
        if (x < 0)
            x = 0;
        if (x >= WIDTH-12)
            x = WIDTH - 12;
        int tempX = x;
        int tempY = y;
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                draw(tempX++, tempY, jet[i][j]);
            }
            printf("\n");
            tempY++;
            tempX = x;
        }
        update_bullets();
        if(j/10 > 3)
        {
            update_airbomb();
            check_collision_with_bomb(x,y);
        }
        if(j/10 >15)
        {
            update_aidplane();
            check_jet_collision_with_aidplane(x , y);
            check_collision_with_aidplane(x , y);
        }
        if(j/10 >30)
        {
            update_enemy();
            update_missile();
            check_collision_with_helicopter();
            check_collision_with_missile(x , y);
            check_jet_collision_with_helicopter(x , y);
        }
        if(j/10 > 45)
        {
            update_enemy2();
            update_missile2();
            check_collision_with_jet();
            check_jet_collision_with_enemyjet(x , y);
            check_collision_with_missile2(x , y);
        }
        if(jet_health<=0)
        {
            int gameoverr=gameover();
            return gameoverr;
        }
    }
}
int menu()
{
    int arrowpos = 1;
    int keypress;
    while (keypress != 13)
    {
        system("cls");
        gotoxy(WIDTH/2 - 4, HEIGHT/2 - 2); arrow(1, arrowpos); printf(arrowpos == 1 ? "\033[1;32m Start\n\033[0m" : "Start\n");
        gotoxy(WIDTH/2 - 4, HEIGHT/2 - 1); arrow(2, arrowpos); printf(arrowpos == 2 ? "\033[1;32m Difficulty\n\033[0m" : "Difficulty\n");
        gotoxy(WIDTH/2 - 4, HEIGHT/2); arrow(3, arrowpos); printf(arrowpos == 3 ? "\033[1;32m Game records\n\033[0m" : "Game records\n");
        gotoxy(WIDTH/2 - 4, HEIGHT/2 + 1); arrow(4, arrowpos); printf(arrowpos == 4 ? "\033[1;32m Exit\n\033[0m" : "Exit\n");
        keypress = getch();
        fflush(stdin);
        if (keypress == 80 && arrowpos != 4){arrowpos += 1;}
        else if (keypress == 72 && arrowpos != 1){arrowpos -= 1;}
        else{arrowpos = arrowpos;}
    }
    return arrowpos;
}
int second_menu()
{
    system("cls");
    int arrowpos = 1;
    int keypress=0;
    while (keypress != 13)
    {
        system("cls");
        gotoxy(WIDTH/2 - 4, HEIGHT/2 - 2); arrow(1, arrowpos); printf(arrowpos == 1 ? "\033[1;32m>>>Grade 1\n\033[0m" : "Grade 1\n");
        gotoxy(WIDTH/2 - 4, HEIGHT/2 - 1); arrow(2, arrowpos); printf(arrowpos == 2 ? "\033[1;32m>>>Grade 2\n\033[0m" : "Grade 2\n");
        gotoxy(WIDTH/2 - 4, HEIGHT/2); arrow(3, arrowpos); printf(arrowpos == 3 ? "\033[1;32m>>>Grade 3\n\033[0m" : "Grade 3\n");
        gotoxy(WIDTH/2 - 4, HEIGHT/2 + 1); arrow(4, arrowpos); printf(arrowpos == 4 ? "\033[1;32m>>>Grade 4\n\033[0m" : "Grade 4\n");
        keypress = getch();
        fflush(stdin);
        if (keypress == 80 && arrowpos != 4){arrowpos += 1;}
        else if (keypress == 72 && arrowpos != 1){arrowpos -= 1;}
        else{arrowpos = arrowpos;}
    }
    return arrowpos;
}
void arrow(int realpos, int arrowpos)
{
    if (realpos == arrowpos)
    {
        printf("\033[1;32m");
        printf(" ");
        printf("\033[0m");
    }
    else
    {
        printf(" ");
    }
}
void printFileInReverse(char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file \n");
        return;
    }
    int MAX_LINES=500;
    int MAX_LINE_LENGTH=200;
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int numLines = 0;
    while (fgets(lines[numLines], MAX_LINE_LENGTH, file)) 
    {
        numLines++;
    }
    int j=0;
    for (int i = numLines - 1; i >= 0; i--) {
        gotoxy(WIDTH/2 - 15, HEIGHT/2 - numLines + j);
        printf("\033[0;36m%s\n\033[0m", lines[i]);
        j++;
    }
    fclose(file);
    gotoxy(WIDTH/2 - 15, HEIGHT/2 + numLines + 1);
    printf("\033[0;36m\nPress any key to go back to the main menu...\033[0m");
    getch();
}