#include "game.h"
#include "util.h"


void printMapScreen(int frameArr[][25])
{
    int x = 5, y = 3;   //맵이 시작하는 가장 왼쪽 위 끝점의 좌표

    for (int i = 0; i < frameArrsizei; i++) {
        for (int j = 0; j < frameArrsizej; j++) {
            gotoxy(x + j * 2, y + i);

            if (frameArr[i][j] == 2) {   //플레이어1
                ColorSet(0, 10);
                printf("◎");
            }
            else if (frameArr[i][j] == 8) {   //플레이어2
                ColorSet(0, 13);
                printf("◎");
            }
            else if (frameArr[i][j] == 3) {   //도착지점
                ColorSet(0, 10);
                printf("★");
            }
            else if (frameArr[i][j] == 10) {   //도착지점
                ColorSet(0, 13);
                printf("★");
            }
            else if (frameArr[i][j] == 11) {   //도착지점
                ColorSet(0, 6);
                printf("★");
            }
            else if (frameArr[i][j] == 1) {   //벽
                ColorSet(0, 7);
                printf("▩");
            }

            else if (frameArr[i][j] == 4) {   //소화기
                ColorSet(0, 11);
                printf("§");
            }

            else if (frameArr[i][j] == 5) {   //불
                ColorSet(0, 12);
                printf("♨");
            }

            else if (frameArr[i][j] == 6) {   //엘베
                ColorSet(0, 14);
                printf("▥");
            }
            else if (frameArr[i][j] == 7) {   //FireSpread용 불
                ColorSet(0, 12);
                printf("♨");
            }
            else if (frameArr[i][j] == 9) {   //소화전
                ColorSet(0, 11);
                printf("㉿");
            }
            else if (frameArr[i][j] == 12) {   //소화전
                ColorSet(0, 14);
                printf("＊");
            }
            else if (frameArr[i][j] == 0)   //공백
                printf("  ");
        }
    }

    char* back = "뒤로 가기 : B";
    ColorSet(0, 8);
    gotoxy(23, 28);
    printf("%s", back);
    ColorSet(0, 7);
}

void KeyControl(int frameArr[][25], P* player1, P* player2, int* sort, int* player_who, char* presskb, int startTime,
    int exit_player1_X, int exit_player1_Y, int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y) {

    //플레이어1은 오른쪽 사람 : 오른쪽 키보드로 움직여줌 (소화==0번 누르기)
    //플레이어2는 왼쪽 사람 : awds키보드로 움직여줌 (소화==탭버튼 누르기)
    //플레이어1 키값 : 위(119,87) 왼쪽(97,65) 오른쪽(100,68) 아래(115,83) 소화(9)
    //플레이어2 키값 : 위(72) 왼쪽(75) 오른쪽(77) 아래(80) 소화(48)

    char pressKey;   //키 값을 입력받아 저장할 변수

    //키가 입력되면 잡아준다
    if (_kbhit()) {

        pressKey = _getch();
        *presskb = pressKey;
        if (pressKey == 'b' || pressKey == 'B') {
            system("cls");
            gotoxy(22, 12);
            printf("메뉴창 로딩중..");
            return;
        }
        //플레이어 1인지, 2인지 알아보기
        if (pressKey >= 97 && pressKey <= 119 || pressKey >= 65 && pressKey <= 68 ||
            pressKey >= 83 && pressKey <= 87 || pressKey == 9) {   //플레이어 1의 입력값인 경우
            *player_who = 1;
            *sort = key_p1(frameArr, player1, pressKey, exit_player1_X, exit_player1_Y, exit_player2_X, exit_player2_Y,
                exit_player3_X, exit_player3_Y);
            if (pressKey == 9) {
                if (player1->fireplug == 1) {
                    fireplug_func(frameArr, player1);
                }
                else {
                    extinguisher_func(frameArr, player1);
                }
            }
            printMapScreen(frameArr);
        }

        else if (pressKey >= 72 && pressKey <= 80 || pressKey == 48) {   //플레이어 2의 입력값인 경우
            *player_who = 2;
            *sort = key_p2(frameArr, player2, pressKey, exit_player1_X, exit_player1_Y, exit_player2_X, exit_player2_Y,
                exit_player3_X, exit_player3_Y);
            if (pressKey == 48) {
                if (player2->fireplug == 1) {
                    fireplug_func(frameArr, player2);
                }
                else {
                    extinguisher_func(frameArr, player2);
                }
            }
            printMapScreen(frameArr);
        }

    }
}

//움직임 기능 함수
//플레이어1의 키 움직여주는 함수 (반환값 : 내가 먹은 자리의 원래 상태 ex. 불, 소화기, 공백 등등)
int key_p1(int frameArr[][frameArrsizej], P* player, int pressKey, int exit_player1_X, int exit_player1_Y,
    int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y) {
    int tmpX = player->playerX, tmpY = player->playerY;   //플레이어 좌표의 초기값 기억
    int remember_sort = 0;

    //플레이어1 키값 : 위(119,87) 왼쪽(97,65) 오른쪽(100,68) 아래(115,83) 소화(9)
    if (pressKey == 87) pressKey = 119;
    if (pressKey == 65) pressKey = 97;
    if (pressKey == 68) pressKey = 100;
    if (pressKey == 83) pressKey = 115;

    switch (pressKey) {

    case 119:   //위쪽방향
        if (frameArr[(player->playerY) - 1][player->playerX] != 1 &&
            frameArr[(player->playerY) - 1][player->playerX] != 8) {  //배열 밖으로 벗어나지 않도록!
            remember_sort = frameArr[(player->playerY) - 1][player->playerX];
            (player->playerY)--;
        }
        break;


    case 97:   //왼쪽방향
        if (frameArr[player->playerY][player->playerX - 1] != 1 &&
            frameArr[player->playerY][player->playerX - 1] != 8) {  //배열 밖으로 벗어나지 않도록!
            remember_sort = frameArr[player->playerY][player->playerX - 1];
            (player->playerX)--;
        }
        break;


    case 100:   //오른쪽방향
        if (frameArr[player->playerY][player->playerX + 1] != 1 &&
            frameArr[player->playerY][player->playerX + 1] != 8) {   //배열 밖으로 벗어나지 않도록!
            remember_sort = frameArr[player->playerY][player->playerX + 1];
            (player->playerX)++;
        }
        break;


    case 115:   //아래쪽방향
        if (frameArr[player->playerY + 1][player->playerX] != 1 &&
            frameArr[player->playerY + 1][player->playerX] != 8) {   //배열 밖으로 벗어나지 않도록!
            remember_sort = frameArr[player->playerY + 1][player->playerX];
            (player->playerY)++;
        }
        break;

    }

    //출구 2개인 경우 (학정, 광토)
    if (exit_player3_Y == 0) {
        //움직였다면 화면 재출력
        if (player->playerX != tmpX || player->playerY != tmpY) {
            //지워주고
            if (frameArr[exit_player2_Y][exit_player2_X] == frameArr[tmpY][tmpX])
                frameArr[tmpY][tmpX] = 10;
            else if (frameArr[exit_player1_Y][exit_player1_X] == frameArr[tmpY][tmpX])
                frameArr[tmpY][tmpX] = 3;
            else
                frameArr[tmpY][tmpX] = 0;

            //움직이고
            frameArr[player->playerY][player->playerX] = 2;   //플레이어 좌표

            //출력하고
            printMapScreen(frameArr);

            return remember_sort;
        }
    }

    //출구 3개인 경우 (대양ai, 대양홀)
    else if (exit_player3_Y != 0) {
        if (player->playerX != tmpX || player->playerY != tmpY) {
            //지워주고
            if (frameArr[tmpY][tmpX] == frameArr[exit_player1_Y][exit_player1_X] ||
                frameArr[tmpY][tmpX] == frameArr[exit_player2_Y][exit_player2_X] ||
                frameArr[tmpY][tmpX] == frameArr[exit_player3_Y][exit_player3_X])
                frameArr[tmpY][tmpX] = 11;
            else
                frameArr[tmpY][tmpX] = 0;

            //움직이고
            frameArr[player->playerY][player->playerX] = 2;   //플레이어 좌표

            //출력하고
            printMapScreen(frameArr);

            return remember_sort;
        }
    }

    //움직이지 않는다면, -1 반환
    return -1;
}

//플레이어2의 키 움직여주는 함수 (반환값 : 내가 먹은 자리의 원래 상태 ex. 불, 소화기, 공백 등등)
int key_p2(int frameArr[][frameArrsizej], P* player, int pressKey, int exit_player1_X, int exit_player1_Y,
    int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y) {

    int tmpX = player->playerX, tmpY = player->playerY;   //플레이어 좌표의 초기값 기억
    int remember_sort = 0;

    switch (pressKey) {

    case 72:   //위쪽방향
        if (frameArr[(player->playerY) - 1][player->playerX] != 1 &&
            frameArr[(player->playerY) - 1][player->playerX] != 2) {  //배열 밖으로 벗어나지 않도록!
            remember_sort = frameArr[(player->playerY) - 1][player->playerX];
            (player->playerY)--;
        }
        break;


    case 75:   //왼쪽방향
        if (frameArr[player->playerY][player->playerX - 1] != 1 &&
            frameArr[player->playerY][player->playerX - 1] != 2) {  //배열 밖으로 벗어나지 않도록!
            remember_sort = frameArr[player->playerY][player->playerX - 1];
            (player->playerX)--;
        }
        break;


    case 77:   //오른쪽방향
        if (frameArr[player->playerY][player->playerX + 1] != 1 &&
            frameArr[player->playerY][player->playerX + 1] != 2) {   //배열 밖으로 벗어나지 않도록!
            remember_sort = frameArr[player->playerY][player->playerX + 1];
            (player->playerX)++;
        }
        break;


    case 80:   //아래쪽방향
        if (frameArr[player->playerY + 1][player->playerX] != 1 &&
            frameArr[player->playerY + 1][player->playerX] != 2) {   //배열 밖으로 벗어나지 않도록!
            remember_sort = frameArr[player->playerY + 1][player->playerX];
            (player->playerY)++;
        }
        break;

    }

    if (exit_player3_Y == 0) {
        //움직였다면 화면 재출력
        if (player->playerX != tmpX || player->playerY != tmpY) {
            //지워주고
            if (frameArr[exit_player1_Y][exit_player1_X] == frameArr[tmpY][tmpX])
                frameArr[tmpY][tmpX] = 3;
            else if (frameArr[exit_player2_Y][exit_player2_X] == frameArr[tmpY][tmpX])
                frameArr[tmpY][tmpX] = 10;
            else
                frameArr[tmpY][tmpX] = 0;

            //움직이고
            frameArr[player->playerY][player->playerX] = 8;   //플레이어 좌표

            //출력하고
            printMapScreen(frameArr);

            return remember_sort;
        }
    }

    else if (exit_player3_Y != 0) {
        //움직였다면 화면 재출력
        if (player->playerX != tmpX || player->playerY != tmpY) {
            //지워주고
            if (frameArr[tmpY][tmpX] == frameArr[exit_player1_Y][exit_player1_X] ||
                frameArr[tmpY][tmpX] == frameArr[exit_player2_Y][exit_player2_X] ||
                frameArr[tmpY][tmpX] == frameArr[exit_player3_Y][exit_player3_X])
                frameArr[tmpY][tmpX] = 11;
            else
                frameArr[tmpY][tmpX] = 0;

            //움직이고
            frameArr[player->playerY][player->playerX] = 8;   //플레이어 좌표

            //출력하고
            printMapScreen(frameArr);

            return remember_sort;
        }
    }
    //움직이지 않는다면, -1 반환
    return -1;
}

//소화전으로 불꺼주는 함수
void fireplug_func(int frameArr[][frameArrsizej], P* player) {

    if (player->fireplug == 1) {
        int x = player->playerX, y = player->playerY;
        for (int i = 1; i <= 2; i++) {
            if (frameArr[y][x + i] == 5 || frameArr[y][x + i] == 7 || frameArr[y][x + i] == 0)
                frameArr[y][x + i] = 12;
            if (frameArr[y][x - i] == 5 || frameArr[y][x - i] == 7 || frameArr[y][x - i] == 0)
                frameArr[y][x - i] = 12;
            if (frameArr[y + i][x] == 5 || frameArr[y + i][x] == 7 || frameArr[y + i][x] == 0)
                frameArr[y + i][x] = 12;
            if (frameArr[y - i][x] == 5 || frameArr[y - i][x] == 7 || frameArr[y - i][x] == 0)
                frameArr[y - i][x] = 12;
        }
    }

    printMapScreen(frameArr);

    //시간지연 만들기
    Sleep(100);
    for (int i = 1; i < 18; i++) {
        for (int j = 1; j < 24; j++)
            if (frameArr[i][j] == 12)
                frameArr[i][j] = 0;
    }
}

//소화기로 불꺼주는 함수
void extinguisher_func(int frameArr[][frameArrsizej], P* player) {
    if (player->extinguisher > 0) { //소화기가 있다면

        if (frameArr[player->playerY + 1][player->playerX] == 5)
            frameArr[player->playerY + 1][player->playerX] = 0;

        if (frameArr[player->playerY - 1][player->playerX] == 5)
            frameArr[player->playerY - 1][player->playerX] = 0;

        if (frameArr[player->playerY][player->playerX + 1] == 5)
            frameArr[player->playerY][player->playerX + 1] = 0;

        if (frameArr[player->playerY][player->playerX - 1] == 5)
            frameArr[player->playerY][player->playerX - 1] = 0;

        (player->extinguisher)--;
    }
}

//불 번지는 함수, 불을 중심으로 위아래/양옆 불 번짐
void FireSpread(int frameArr[][frameArrsizej])
{
    int save_arr[frameArrsizei][frameArrsizej] = { 0 };

    for (int i = 0; i < frameArrsizei; i++)
        for (int j = 0; j < frameArrsizej; j++)
            save_arr[i][j] = frameArr[i][j];

    for (int i = 1; i < frameArrsizei-1; i++) {
        for (int j = 1; j < frameArrsizej-1; j++) {
            if (save_arr[i][j] == 5)  //불이 있는 위치
            {
                if (save_arr[i][j - 1] == 0)
                    frameArr[i][j - 1] = 7;

                if (save_arr[i][j + 1] == 0)
                    frameArr[i][j + 1] = 7;

                if (save_arr[i - 1][j] == 0)
                    frameArr[i - 1][j] = 7;

                if (save_arr[i + 1][j] == 0)
                    frameArr[i + 1][j] = 7;

            }
        }
    }

    printMapScreen(frameArr);
}

//메인함수 내용 줄이기위해 함수로 만들어 따로 빼냈음
//1. 현재시간 반환해주는 함수
int clock(int startTime) {
    //현재시간을 반환
    int nowTime = GetTickCount64();
    return nowTime - startTime;
}

//2. 구조체 초기화해주는 함수
void struct_first(P player[2], int map_num) {
    player[0].extinguisher = 0, player[1].extinguisher = 0;   //소화기 개수
    player[0].fireplug = 0, player[1].fireplug = 0;   //소화전 사용 가능 여부

    if (map_num == 1) {
        player[0].playerX = 1, player[0].playerY = 1;   //플레이어1의 초기 위치
        player[1].playerX = 18, player[1].playerY = 17;   //플레이어2의 초기 위치
    }
    else if (map_num == 2) {
        player[0].playerX = 1, player[0].playerY = 1;   //플레이어1의 초기 위치
        player[1].playerX = 1, player[1].playerY = 2;   //플레이어2의 초기 위치
    }
    else if (map_num == 3) {
        player[0].playerX = 1, player[0].playerY = 1;	//플레이어1의 초기 위치
        player[1].playerX = 23, player[1].playerY = 17;	//플레이어2의 초기 위치
    }
    else if (map_num == 4) {
        player[0].playerX = 22, player[0].playerY = 7;   //플레이어1의 초기 위치
        player[1].playerX = 22, player[1].playerY = 11;   //플레이어2의 초기 위치
    }
}

//3. 소화기, 현재 시간 등의 정보를 출력해주는 함수 
void print_time_and_extinguisher_info(P player[2], int nowTime, int TimeLimit, int extLimit) {
    gotoxy(17, 1);
    printf("현재 시간 : %d초 / %d초", nowTime, TimeLimit);

    gotoxy(5, 23);
    printf("p1의 소화기 개수 : %d/%d     p2의 소화기 개수 : %d/%d",
        player[0].extinguisher, extLimit, player[1].extinguisher, extLimit);
}

//4. 소화기, 소화전 개수 업뎃 함수
void player_ex_info_update(int frameArr[][frameArrsizej], P player[2], int sort, int nowTime, int player_who) {
    //소화기, 소화전 개수 업뎃
    if (player_who == 1) {
        if (sort == 4) {
            if (player[0].extinguisher < 5)
                player[0].extinguisher++;
        }
        if (sort == 9) {
            if (player[0].fireplug == 0) {
                player[0].fireplug = 1;
                player[0].fireplug_get_time = nowTime;
            }
            else
                player[0].fireplug_get_time = nowTime;

        }
    }
    if (player_who == 2) {
        if (sort == 4) {
            if (player[1].extinguisher < 5)
                player[1].extinguisher++;
        }
        if (sort == 9) {
            if (player[1].fireplug == 0) {
                player[1].fireplug = 1;
                player[1].fireplug_get_time = nowTime;
            }
            else
                player[1].fireplug_get_time = nowTime;
        }
    }

    if (player[0].fireplug == 1) {
        if (nowTime - player[0].fireplug_get_time > 11000) {  //10초동안 사용 가능하게 만들어줌
            gotoxy(5, 25);
            printf("                     ");
            gotoxy(5, 27);
            printf("                                       ");
            printMapScreen(frameArr);
            player[0].fireplug = 0;
        }
        else {
            gotoxy(5, 25);
            printf("p1소화전 사용가능");
            gotoxy(5, 27);
            printf("사용 가능 시간 : %d초 / 10초", (nowTime - player[0].fireplug_get_time) / 1000);
        }
    }


    if (player[1].fireplug == 1) {
        if (nowTime - player[1].fireplug_get_time > 11000) {  //10초동안 사용 가능하게 만들어줌
            gotoxy(32, 25);
            printf("                     ");
            gotoxy(32, 27);
            printf("                                       ");
            printMapScreen(frameArr);
            player[1].fireplug = 0;
        }
        else {
            gotoxy(32, 25);
            printf("p2소화전 사용가능");
            gotoxy(32, 27);
            printf("사용 가능 시간 : %d초 / 10초", (nowTime - player[1].fireplug_get_time) / 1000);
        }
    }
}

//5. 10초마다 불번지게 해주는 함수
void main_fire_spread(int frameArr[][frameArrsizej], int nowTime) {
    //불 번짐, 10초에 한 번씩
    if (nowTime % 10 == 0 && nowTime != 0) FireSpread(frameArr);
    else {
        for (int i = 0; i < frameArrsizei; i++)
            for (int j = 0; j < frameArrsizej; j++) {
                if (frameArr[i][j] == 7) frameArr[i][j] = 5;   //임시로 저장해둔 숫자에 5 대입
            }
    }
}

//6. 종료조건 함수
int game_over(int frameArr[][25], P player[2], int startTime, int sort, int TimeLimit, int extLimit, int exit_player1_X, int exit_player1_Y,
    int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y) {
    //종료조건
    int p1_x = player[0].playerX, p1_y = player[0].playerY;
    int p2_x = player[1].playerX, p2_y = player[1].playerY;

    if (exit_player3_X == 0 && exit_player3_Y == 0) {
        if ((clock(startTime) / 1000 < TimeLimit) &&
            p1_x == exit_player1_X && p1_y == exit_player1_Y && p2_x == exit_player2_X && p2_y == exit_player2_Y) {
            system("cls"); printMapScreen(frameArr);    //최종 출력할 때 글씨 겹치지 않게 하려고
            gotoxy(26, 23);
            puts("성공!!!");
            return 1;
        }
    }
    else if (exit_player3_X != 0 || exit_player3_Y != 0) {
        if ((clock(startTime) / 1000 < TimeLimit) && (
            //3P2 경우의수 = 6
            (p1_x == exit_player1_X && p1_y == exit_player1_Y && p2_x == exit_player2_X && p2_y == exit_player2_Y) ||
            (p1_x == exit_player1_X && p1_y == exit_player1_Y && p2_x == exit_player3_X && p2_y == exit_player3_Y) ||
            (p1_x == exit_player2_X && p1_y == exit_player2_Y && p2_x == exit_player1_X && p2_y == exit_player1_Y) ||
            (p1_x == exit_player2_X && p1_y == exit_player2_Y && p2_x == exit_player3_X && p2_y == exit_player3_Y) ||
            (p1_x == exit_player3_X && p1_y == exit_player3_Y && p2_x == exit_player1_X && p2_y == exit_player1_Y) ||
            (p1_x == exit_player3_X && p1_y == exit_player3_Y && p2_x == exit_player2_X && p2_y == exit_player2_Y))
            ) {
            system("cls"); printMapScreen(frameArr);    //최종 출력할 때 글씨 겹치지 않게 하려고
            gotoxy(26, 23);
            puts("성공!!!");
            return 1;
        }
    }
    if (clock(startTime) / 1000 == TimeLimit) {
        system("cls"); printMapScreen(frameArr);
        gotoxy(20, 23);
        puts("시간초과  Game Over");
        return 2;
    }
    if (sort == 5 || sort == 7) {
        system("cls"); printMapScreen(frameArr);
        gotoxy(20, 23);
        puts("불에 뛰어듦; Game Over");
        return 2;
    }
    if (sort == 6) {
        system("cls"); printMapScreen(frameArr);
        gotoxy(20, 23);
        puts("엘리베이터; Game Over");
        return 2;
    }
    return 0;
}

void game_over_screen(int is_game_over) {

    Sleep(1500);
    if (is_game_over == 1) {
        //1이면 성공, 2면 실패 화면 출력
        int gameover[frameArrsizei][frameArrsizej] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,2,2,2,2,2,1,2,2,2,2,2,1,2,1,1,1,2,1,2,2,2,2,2,1},
            {1,2,1,1,1,1,1,2,1,1,1,2,1,2,2,1,2,2,1,2,1,1,1,1,1},
            {1,2,1,1,2,2,1,2,2,2,2,2,1,2,1,2,1,2,1,2,2,2,2,2,1},
            {1,2,1,1,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,2,1,1,1,1,1},
            {1,2,2,2,2,2,1,2,1,1,1,2,1,2,1,1,1,2,1,2,2,2,2,2,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,2,2,2,2,1,2,1,1,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1},
            {1,2,1,1,1,1,2,1,1,1,2,1,1,1,1,2,1,1,2,1,2,1,1,2,1},
            {1,2,1,1,1,1,2,1,1,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1},
            {1,2,1,1,1,1,2,1,1,1,2,1,1,1,1,2,1,1,2,1,2,1,2,1,1},
            {1,2,2,2,2,1,2,2,2,1,2,2,2,2,1,2,1,1,2,1,2,1,1,2,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        };

        int x = 5, y = 3;   //맵이 시작하는 가장 왼쪽 위 끝점의 좌표
        for (int j = 0; j < frameArrsizej; j++) {
            for (int i = 0; i < frameArrsizei; i++) {
                gotoxy(x + j * 2, y + i);
                if (gameover[i][j] == 1) {
                    ColorSet(0, 0);
                    printf("■");
                }

                else if (gameover[i][j] == 0) {
                    ColorSet(0, 11);
                    printf("■");
                }

                else {
                    ColorSet(0, 11);
                    printf("■");
                }
            }

            Sleep(30);
        }
    }
    else if (is_game_over == 2) {
        //1이면 성공, 2면 실패 화면 출력
        int gameover[frameArrsizei][frameArrsizej] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,2,2,2,2,2,1,2,2,2,2,2,1,2,1,1,1,2,1,2,2,2,2,2,1},
            {1,2,1,1,1,1,1,2,1,1,1,2,1,2,2,1,2,2,1,2,1,1,1,1,1},
            {1,2,1,1,2,2,1,2,2,2,2,2,1,2,1,2,1,2,1,2,2,2,2,2,1},
            {1,2,1,1,1,2,1,2,1,1,1,2,1,2,1,1,1,2,1,2,1,1,1,1,1},
            {1,2,2,2,2,2,1,2,1,1,1,2,1,2,1,1,1,2,1,2,2,2,2,2,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,2,2,2,2,2,1,2,1,1,1,2,1,2,2,2,2,2,1,2,2,2,2,2,1},
            {1,2,1,1,1,2,1,2,1,1,1,2,1,2,1,1,1,1,1,2,1,1,1,2,1},
            {1,2,1,1,1,2,1,2,1,1,1,2,1,2,2,2,2,2,1,2,2,2,2,2,1},
            {1,2,1,1,1,2,1,1,2,1,2,1,1,2,1,1,1,1,1,2,1,1,2,1,1},
            {1,2,2,2,2,2,1,1,1,2,1,1,1,2,2,2,2,2,1,2,1,1,1,2,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
        };

        int x = 5, y = 3;   //맵이 시작하는 가장 왼쪽 위 끝점의 좌표
        for (int j = 0; j < frameArrsizej; j++) {
            for (int i = 0; i < frameArrsizei; i++) {
                gotoxy(x + j * 2, y + i);
                if (gameover[i][j] == 1) {
                    ColorSet(0, 0);
                    printf("■");
                }

                else if (gameover[i][j] == 0) {
                    ColorSet(0, 12);
                    printf("■");
                }

                else {
                    ColorSet(0, 12);
                    printf("■");
                }
            }

            Sleep(30);
        }
    }
}
void print_all_pass() { //모든 맵 성공시 화면 출력
    int All_pass[frameArrsizei][frameArrsizej] = {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {1,1,1,1,2,1,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
            {1,1,1,2,1,2,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
            {1,1,1,2,1,2,1,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
            {1,1,2,1,1,1,2,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
            {1,1,2,2,2,2,2,1,1,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1},
            {1,2,1,1,1,1,1,2,1,2,2,2,2,2,1,1,2,2,2,2,2,1,1,1,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,2,2,2,2,1,1,1,1,2,1,1,1,1,2,2,2,1,1,1,2,2,2,1,1},
            {1,2,1,1,1,2,1,1,2,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,1},
            {1,2,1,1,1,2,1,1,2,1,2,1,1,2,1,1,1,1,1,2,1,1,1,1,1},
            {1,2,2,2,2,1,1,2,1,1,1,2,1,1,2,2,1,1,1,1,2,2,1,1,1},
            {1,2,1,1,1,1,1,2,2,2,2,2,1,1,1,1,2,1,1,1,1,1,2,1,1},
            {1,2,1,1,1,1,2,1,1,1,1,1,2,2,2,2,1,1,1,2,2,2,1,1,1},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    int x = 5, y = 3;   //맵이 시작하는 가장 왼쪽 위 끝점의 좌표
    for (int i = 0; i < frameArrsizei; i++) {
        for (int j = 0; j < frameArrsizej; j++) {
            gotoxy(x + j * 2, y + i);
            if (All_pass[i][j] == 1) {
                ColorSet(0, 0);
                printf("  ");
            }

            else if (All_pass[i][j] == 0) {
                ColorSet(0, 6);
                printf("■");
            }

            else {
                ColorSet(0, 6);
                printf("■");
            }
        }

        Sleep(30);
    }
    Sleep(2000);
    for (int i = 0; i < frameArrsizei; i++) {
        for (int j = 0; j < frameArrsizej; j++) {
            gotoxy(x + j * 2, y + i);
            printf("  ");
        }
        Sleep(30);
    }
}