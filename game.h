#include "util.h"
#include "main.h"


typedef struct player {
    int playerY, playerX;
    int extinguisher;   //소화기 개수도 구조체에 저장!
    int fireplug;   //소화전 사용가능 여부
    int fireplug_get_time;  //소화전 줍줍한 시간 저장
}P;

void printMapScreen(int frameArr[][25]);
void KeyControl(int frameArr[][25], P* player1, P* player2, int* sort, int* player_who, char* presskb, int startTime,
    int exit_player1_X, int exit_player1_Y, int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y);


int key_p1(int frameArr[][25], P* player, int pressKey, int exit_player1_X, int exit_player1_Y,
    int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y);
int key_p2(int frameArr[][25], P* player, int pressKey, int exit_player1_X, int exit_player1_Y,
    int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y);

//소화전으로 불꺼주는 함수
void fireplug_func(int frameArr[][25], P* player);
//소화기로 불꺼주는 함수
void extinguisher_func(int frameArr[][25], P* player);

//불 번짐
void FireSpread(int frameArr[][25]);


//메인함수 내용 줄이기위해 함수로 만들어 따로 빼냈음
//1. 현재시간 반환해주는 함수
int clock(int startTime);
//2. 구조체 초기화해주는 함수
void struct_first(P player[2], int map_num);
//3. 소화기, 현재 시간 등의 정보를 출력해주는 함수 
void print_time_and_extinguisher_info(P player[2], int nowTime, int TimeLimit, int extLimit);
//4. 소화기, 소화전 개수 업뎃 함수
void player_ex_info_update(int frameArr[][25], P player[2], int sort, int nowTime, int player_who);
//5. 10초마다 불번지게 해주는 함수
void main_fire_spread(int frameArr[][25], int nowTime);
//6. 종료조건 함수
int game_over(int frameArr[][25], P player[2], int startTime, int sort, int TimeLimit, int extLimit, int exit_player1_X, int exit_player1_Y,
    int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y);
//7. 게임 오버 화면 출력함수
void game_over_screen(int is_game_over);
//8. 게임 모든 맵 클리어시 출력함수
void print_all_pass();