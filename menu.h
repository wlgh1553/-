#include "util.h"
#include "main.h"

void BGMplayer(int sort, int turn_on);

//선택시에 필요한 키 컨트롤
int menuKeyControl();

//메뉴 선택, 단계 선택
int menuDraw(int sort);
int map_sel_Draw();

//시작 인트로 담당 (순서 : 화재시 유의사항-게임제목 애니-컨셉설명)
void print_caution_sen();
void print_game_concept();
void introDraw(int introArr[][25]);
void intro_animation_total();

//게임 방법 자세한 설명
void infoprint(int n);

//선택하고, 그 값을 메인함수에게 전달하는 함수
int menu_main(int* is_bgm_on);

void person_info();