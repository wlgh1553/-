#include "game.h"
#include "main.h"
void GameStart_Map1(int frameArr[][frameArrsizej], int TimeLimit, int extLimit, int exit_player1_X, int exit_player1_Y,
    int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y, int map_num)  //학정6층
{
    int is_game_over;
    //구조체 초기화
    P player[2];
    struct_first(player, map_num);

    //콘솔창 설정
    init();

    //초기 시간 설정, 소화기 개수 설정
    int startTime = GetTickCount64();

    //맵출력
    printMapScreen(frameArr);

    //본격 게임 실행
    while (1) {
        //소화기, 현재 시간 등의 정보를 출력해주는 함수 
        print_time_and_extinguisher_info(player, clock(startTime) / 1000, TimeLimit, extLimit);

        int sort = 0, player_who = 0;
        char presskb;
        KeyControl(frameArr, &player[0], &player[1], &sort, &player_who, &presskb, startTime,
            exit_player1_X, exit_player1_Y, exit_player2_X, exit_player2_Y, exit_player3_X, exit_player3_Y);
        if (presskb == 'b' || presskb == 'B')
            break;

        //소화기, 소화전 개수 업뎃 함수
        player_ex_info_update(frameArr, player, sort, clock(startTime), player_who);

        //10초마다 불번지게 해주는 함수
        main_fire_spread(frameArr, clock(startTime) / 1000);


        //종료조건에 부합하는지 확인. 부합하면 반복문 탈출
        if (is_game_over = game_over(frameArr, player, startTime, sort, TimeLimit, extLimit, exit_player1_X, exit_player1_Y,
            exit_player2_X, exit_player2_Y, exit_player3_X, exit_player3_Y)) {
            //game_over반환값이 1이면 성공, 2면 실패
            game_over_screen(is_game_over);
            break;
        }
    }
    if (is_game_over == 1)
    {
        pass_map_arr[map_num] = 1;
    }
}

void GameStart_Map2(int frameArr[][frameArrsizej], int TimeLimit, int extLimit, int exit_player1_X, int exit_player1_Y,
    int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y, int map_num)
{
    int is_game_over;
    //구조체 초기화
    P player[2];
    struct_first(player, map_num);

    //콘솔창 설정
    init();

    //초기 시간 설정, 소화기 개수 설정
    int startTime = GetTickCount64();

    //맵출력
    printMapScreen(frameArr);

    //본격 게임 실행
    while (1) {
        //소화기, 현재 시간 등의 정보를 출력해주는 함수 
        print_time_and_extinguisher_info(player, clock(startTime) / 1000, TimeLimit, extLimit);

        int sort = 0, player_who = 0;
        char presskb;
        KeyControl(frameArr, &player[0], &player[1], &sort, &player_who, &presskb, startTime,
            exit_player1_X, exit_player1_Y, exit_player2_X, exit_player2_Y, exit_player3_X, exit_player3_Y);
        if (presskb == 'b' || presskb == 'B')
            break;

        //소화기, 소화전 개수 업뎃 함수
        player_ex_info_update(frameArr, player, sort, clock(startTime), player_who);

        //10초마다 불번지게 해주는 함수
        main_fire_spread(frameArr, clock(startTime) / 1000);


        //종료조건에 부합하는지 확인. 부합하면 반복문 탈출
        if (is_game_over = game_over(frameArr, player, startTime, sort, TimeLimit, extLimit, exit_player1_X, exit_player1_Y,
            exit_player2_X, exit_player2_Y, exit_player3_X, exit_player3_Y)) {
            //game_over반환값이 1이면 성공, 2면 실패
            game_over_screen(is_game_over);
            break;
        }
    }
    if (is_game_over == 1)
    {
        pass_map_arr[map_num] = 1;
    }

}

void GameStart_Map3(int frameArr[][frameArrsizej], int TimeLimit, int extLimit, int exit_player1_X, int exit_player1_Y,
    int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y, int map_num)
{
    int is_game_over;
    //구조체 초기화
    P player[2];
    struct_first(player, map_num);

    //콘솔창 설정
    init();

    //초기 시간 설정, 소화기 개수 설정
    int startTime = GetTickCount64();

    //맵출력
    printMapScreen(frameArr);

    //본격 게임 실행
    while (1) {
        //소화기, 현재 시간 등의 정보를 출력해주는 함수 
        print_time_and_extinguisher_info(player, clock(startTime) / 1000, TimeLimit, extLimit);

        int sort = 0, player_who = 0;
        char presskb;
        KeyControl(frameArr, &player[0], &player[1], &sort, &player_who, &presskb, startTime,
            exit_player1_X, exit_player1_Y, exit_player2_X, exit_player2_Y, exit_player3_X, exit_player3_Y);
        if (presskb == 'b' || presskb == 'B')
            break;

        //소화기, 소화전 개수 업뎃 함수
        player_ex_info_update(frameArr, player, sort, clock(startTime), player_who);

        //10초마다 불번지게 해주는 함수
        main_fire_spread(frameArr, clock(startTime) / 1000);


        //종료조건에 부합하는지 확인. 부합하면 반복문 탈출
        if (is_game_over = game_over(frameArr, player, startTime, sort, TimeLimit, extLimit, exit_player1_X, exit_player1_Y,
            exit_player2_X, exit_player2_Y, exit_player3_X, exit_player3_Y)) {
            //game_over반환값이 1이면 성공, 2면 실패
            game_over_screen(is_game_over);
            break;
        }
    }
    if (is_game_over == 1)
    {
        pass_map_arr[map_num] = 1;
    }
}

void GameStart_Map4(int frameArr[][frameArrsizej], int TimeLimit, int extLimit, int exit_player1_X, int exit_player1_Y,
    int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y, int map_num)
{
    int is_game_over;
    //구조체 초기화
    P player[2];
    struct_first(player, map_num);

    //콘솔창 설정
    init();

    //초기 시간 설정, 소화기 개수 설정
    int startTime = GetTickCount64();

    //맵출력
    printMapScreen(frameArr);

    //본격 게임 실행
    while (1) {
        //소화기, 현재 시간 등의 정보를 출력해주는 함수 
        print_time_and_extinguisher_info(player, clock(startTime) / 1000, TimeLimit, extLimit);

        int sort = 0, player_who = 0;
        char presskb;
        KeyControl(frameArr, &player[0], &player[1], &sort, &player_who, &presskb, startTime,
            exit_player1_X, exit_player1_Y, exit_player2_X, exit_player2_Y, exit_player3_X, exit_player3_Y);
        if (presskb == 'b' || presskb == 'B')
            break;

        //소화기, 소화전 개수 업뎃 함수
        player_ex_info_update(frameArr, player, sort, clock(startTime), player_who);

        //10초마다 불번지게 해주는 함수
        main_fire_spread(frameArr, clock(startTime) / 1000);

        //종료조건에 부합하는지 확인. 부합하면 반복문 탈출
        if (is_game_over = game_over(frameArr, player, startTime, sort, TimeLimit, extLimit, exit_player1_X, exit_player1_Y,
            exit_player2_X, exit_player2_Y, exit_player3_X, exit_player3_Y)) {
            //game_over반환값이 1이면 성공, 2면 실패
            game_over_screen(is_game_over);
            break;
        }
    }
    if (is_game_over == 1)
    {
        pass_map_arr[map_num] = 1;
    }
}
void Ready_Map(int map_num) {
    int xadd1 = 12;
    int xadd2 = 2;
    system("cls");
    gotoxy(6 + xadd1, 10);
    printf("맵을 생성 중입니다.");


    gotoxy(xadd2, 16);
    if (map_num == 1)
    {
        gotoxy(2 + xadd2, 16);
        printf("정보: 학술정보원 이름이 동천관 인거 알고 계셨나요???");
    }
    else if (map_num == 2) {
        gotoxy(xadd2, 16);
        printf("정보: 대양ai 건물이 2015년도에 완공된 거 알고 계셨나요???");
    }
    else if (map_num == 3) {
        gotoxy(2 + xadd2, 16);
        printf("정보: 광개토관에서 시계탑을 보면 무언가가 보일지도...?");
    }
    else
    {
        gotoxy(3 + xadd2, 16);
        printf("정보: 대양홀이 교내 명소인 거 알고 계셨나요???");
    }
    for (int j = 0; j < 3; j++)
    {
        if (j == 2) {
            gotoxy(5 + xadd1, 10);
            printf("맵이 거의 다 생성되었습니다");
            gotoxy(5 + xadd1, 11);
            printf("맵을 탈출할 준비를 해주세요!");
        }
        for (int i = 0; i < 3; i++)
        {
            if (j == 2) {
                gotoxy(31 + i + xadd1, 10);
                printf(".");
                Sleep(500);
            }
            else {
                gotoxy(24 + i + xadd1, 10);
                printf(".");
                Sleep(500);
            }
        }
        if (j != 2)
        {
            for (int i = 0; i < 3; i++)
            {
                gotoxy(24 + i + xadd1, 10);
                printf(" ");
            }

        }
        Sleep(500);
    }
    Sleep(1000);

}