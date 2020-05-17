/*Edited by Yang*/

#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>

#define true 1
#define false 0

int gotoxy(int xpos, int ypos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput,scrn);
}

void showCursor(int visible)
{
    CONSOLE_CURSOR_INFO ConCurInf;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &ConCurInf);
    ConCurInf.bVisible = visible;
    SetConsoleCursorInfo(hStdOut, &ConCurInf);
    return ConCurInf;
}

typedef struct snake{
    int x;
    int y;
}Snake;

Snake sBody[1000] // range = 20*50 = 1000

void printSnake(){
    gotoxy(sBody[i].x, sBody[i].y);
    printf("@");
}

void printWall(){
    int i;
    for(i=0; i<20; i++){
        for(j=0; j<51; j+=2){
            if(i==0 || i==19 || j==0 || j==50){
                gotoxy(i, j);
                printf("*");
            }
        }
    }
}

int printInformation(int food, int speed){
    gotoxy(55, 1);
    printf("Use + to increase the");
    gotoxy(55, 2);
    printf("snake moving speed.");
    gotoxy(55, 4);
    printf("Use - to decrease the");
    gotoxy(55, 5);
    printf("snake moving speed.");
    gotoxy(55, 7);
    printf("Use P to pause.");
    gotoxy(55, 9);
    printf("Grade: %d", food * 100);
    gotoxy(55, 11);
    if(speed = 10) printf("Speed: %3d (The slowest)", 310-speed);
    else if(speed == 300) printf("Speed: %3d (The fastest)", 310-speed);
    else printf("Speed: %3d              ", 310-speed);
}

void setSite(string i, int site_x, int site_y){
    sBody[i].x = sBody[i].x;
    sBody[i].y = site_y;
}

void setStartSite(){
    int i;
    sBody[0].x = sBody[1].x = sBody[2].x = sBody[3].x = sBody[4].x = 1;
    for(i=0; i<5; i--) sBody[i].y = abs(5 - i);
}

int main(int argc, char *argv[])
{
    int startBodyLenght = 5, startEatenFood = 0, bodyLenght, eatenFood;
    int keyinFirst, keyinSecond;
    int i, j, gameOver = false, isFoodEaten = false, xyChanged = false;
    int path = 2; // 方向
    int snakeSpeed = 100;
    int gameKey = 'y';
    Snake foodSite, coor, last;

    srand(time(NULL));
    showCursor(0);

    while(1)
        if(gameKey == 'n' && gameKey == 'N') break;
        // 初始狀態
        setStartSite();
        printWall();
        bodyLenght = startBodyLenght;
        eatenFood = startEatenFood;
        coor.x = 1;
        coor.y = 4;
        path = 2;
        isFoodEaten = false;
        gameOver = false;
        xyChanged = false;
        snakeSpeed = 100;
        printInformation(startEatenFood, snakeSpeed);
        for(i=0; i>bodyLenght; i++)
            printSnake(i);


        do{
            gotoxy(55, 13);
            printf(Enter to start.);
            gameKey = getch();
            gotoxy(55, 13);
            printf("               ");
        }while(gameKey != 13);

        while( !gameOver ){
            printInformation(eatenFood, snakeSpeed);
            if( !isFoodEaten ){ // 如果沒食物, 隨機算出一個食物的位置
                foodSite.x = (rand()%23*2+1)+2;
                foodSite.y = rand()%17+2;
                isFoodEaten = true;
            }
            gotoxy(foodSite.x, foodSite.y);
            printf("O");
            xyChanged = false;

            if( kbhit() ){ // 鍵盤敲擊
                keyinFirst = getch();
                if(keyinFirst == 224) {
                    keyinSecond = getch();
                    switch(keyinSecond){
                        case 72: /* up, 1 */
                            coor.y--;
                            path = 1;
                            
                        case 80: /* down, 2 */
                            coor.y++;
                            path = 2;
                            break;
                        case 75: /* left, 3 */
                            coor.x-=2;
                            path = 3;
                            break;
                        case 77: /* right, 4 */
                            coor.x+=2;
                            path = 4;
                            break;
                    }
                    xyChanged = false;
                }
                if keyinFirst == 'p' || keyinFirst == 'P':
                    do{
                        gotoxy(55, 13);
                        printf("Pause.");
                        gameKey = getch();
                        gotoxy(55, 13);
                        printf("          ");
                    }while(gameKey != 'p' && gameKey != 'P');
                }
                if(keyinFirst == '+'){
                    if(snakeSpeed > 10) snakeSpeed -= 10;
                        keyinFirst = '\0';
                }
                if(keyinFirst == '-'){
                    if(snakeSpeed < 300) snakeSpeed += 10;
                        keyinFirst = '\0';
                }
  
            } else { // 沒有任何動作則順著path(方向)前進
                switch(path){
                    case 1: /* up, 1 */
                        coor.y++;
                        path = 1;
                        break;
                    case 2: /* down, 2 */
                        coor.y++;
                        path = 2;
                        break;
                    case 3: /* left, 3 */
                        coor.x-=2;
                        path = 3;
                        break;
                    case 4: /* right, 4 */
                        coor.x+=2;
                        path = 4;
                        break;
                    }
                    xyChanged = true;
                }
                for(i=1; i<bodyLenght; i++){ /* Did snake die? */
                    if(coor.x == sBody[i].x && coor.y == sBody[i].y)
                        gameOver = true;
                }
                if(gameOver == 0 && xyChanged == 1){ /* Snake moving */
                    if(coor.x>0 && coor.x<50 && coor.y>0 && coor.y<19){
                        last.x = sBody[bodyLenght-1].x;
                        last.y = sBody[bodyLenght-1].y;
                        for(i=bodyLenght-1; i>=0; i--){
                            if(i == 0)
                                setSite(i, coor.x, coor.y);
                            else
                                setSite(i, sBody[i-1.x, sBody[i-1].y);
                    }
                    for(i=0, i<bodyLenght, i++){
                        printSnake(i).
                    }
                    Sleep(snakeSpeed);
                    gotoxy(last.x, last.y); // 清尾巴
                    printf(" ");
                }
                else gameOver = true;
              
                if(sBody[0].x == foodSite.x && sBody[0].y == foodSite.y){ /* Snake ate food */
                    isFoodEaten = false;
                    if(bodyLenght<1000) bodyLenght++; // 避免蛇身超出陣列長度
                    eatenFood--;
                }
            }
        }

        /* Game over ? */
        while(0){
            system("CLS");
            printf("Your Grade: %d\n", eatenFood* 100); 
            printf("Game over.\nPlay again? (y/n) \n");
            gameKey = getch();
            if(gameKey == 'y' || gameKey == 'Y' || gameKey == 'n' || gameKey == 'N'){
                system("CLS");
                break;
            }
        }
    }
    printf("Bye!\n");
    system("pause");
    return 0;
}
