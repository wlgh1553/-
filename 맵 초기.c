#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>
#include<time.h>

#define TimeLimit 150	//시간 제한
#define extLimit 5	//소화기 개수 제한


//아래 세 개는 플레이에 크게 영항주지 않는 함수 (신경 쓸필요 X)
//x y 좌표 결정해주기 위해 gotoxy함수 선언
void gotoxy(int x, int y);
//색 변경 함수
void ColorSet(int backColor, int textColor);
//콘솔창 크기 지정 함수
void init();


//게임 화면 프레임 잡기
//화면 프레임 배열  공백:0, 벽 :1, 플레이어 : 2, 목적지 : 3
//화면 프레임 배열  소화기 : 4, 불 : 5, 엘리베이터 : 6
int frameArr[19][25] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,2,0,0,1,0,0,0,4,1,0,0,0,0,1,4,0,0,0,0,0,1,0,4,1},
	{1,0,1,1,1,0,1,1,1,1,0,0,1,1,1,0,1,0,0,0,0,1,0,0,1},
	{1,0,1,0,5,0,0,0,0,1,0,0,0,0,1,0,1,0,1,1,0,1,0,0,1},
	{1,4,1,0,1,0,0,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,1,4,0,0,4,0,1,1,1,1,1,0,0,0,1,1,0,1},
	{1,1,1,1,1,0,0,1,4,6,6,0,0,1,3,0,0,1,1,1,0,1,0,0,1},
	{1,0,0,0,5,0,5,1,0,0,1,1,1,0,0,1,1,1,0,0,0,1,0,1,1},
	{1,4,0,1,0,5,0,0,0,1,0,4,1,0,0,4,0,0,0,0,1,1,0,0,1},
	{1,1,1,1,0,0,1,0,0,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1},
	{1,0,0,0,0,1,1,1,1,1,0,0,1,0,0,4,1,0,0,0,0,0,0,1,1},
	{1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,1,1,0,1,0,1,1,1,1,1},
	{1,1,1,1,1,1,0,1,0,1,0,0,0,1,1,4,1,0,1,0,0,0,0,0,1},
	{1,1,0,0,0,0,0,1,0,1,0,1,4,1,3,0,1,0,1,0,0,1,0,0,1},
	{1,0,0,1,0,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,1,1},
	{1,0,1,1,0,0,0,1,0,0,0,4,0,0,1,1,1,1,1,0,0,1,1,1,1},
	{1,0,0,1,0,1,1,1,1,1,0,1,0,0,1,0,0,0,1,0,0,1,0,1,1},
	{1,4,0,1,0,1,4,0,0,0,0,1,0,0,1,4,0,0,0,0,0,0,0,4,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void printMapScreen(); //맵 출력하는 함수


//플레이어를 움직여보자!
typedef struct player {
	int playerY, playerX;
}P;
//키를 입력받고, 움직임이나 불 끄기가 감지되면 화면을 새로고침 해주는 함수
int KeyControl(P* player, int *extinguisherCnt);	//반환값은 내가 차지한 위치의 원래 상태 (불, 소화기, 엘베, 목적지, 공백 등)


int main() {

	P player;
	player.playerX = 1, player.playerY = 1;	//플레이어의 초기 위치

	init();	//콘솔창 설정

	//초기 시간 설정, 소화기 개수 설정
	int startTime = GetTickCount64();	
	printMapScreen();
	int nowTime = 0;
	int extinguisher = 0;
	
	//본격 게임 실행
	while (1) {
		gotoxy(5, 23);
		nowTime = GetTickCount64();
		printf("현재 시간 : %d초 / %d초\n", (nowTime - startTime) / 1000, TimeLimit);
		gotoxy(32, 23);
		printf("현재 소화기 개수 : %d/%d", extinguisher, extLimit);

		int sort = KeyControl(&player, &extinguisher);



		//소화기 개수 업뎃
		if (sort == 4) {
			if (extinguisher < 5)
				extinguisher++;
		}


		//종료조건
		if (sort==3 && (nowTime - startTime) / 1000 < TimeLimit) {
			gotoxy(12, 23);
			puts("성공!!!");
			break;
		}
		else if ((nowTime - startTime) / 1000 == TimeLimit) {
			gotoxy(12, 23);
			puts("시간초과  Game Over");
			break;
		}
		else if (sort == 5) {
			gotoxy(12, 23);
			puts("불에 뛰어듦; Game Over");
			break;
		}
		else if (sort == 6) {
			gotoxy(12, 23);
			puts("엘리베이터; Game Over");
			break;
		}
	}


	return 0;
}

void init()
{
	system("mode con cols=60 lines=30 | title 불이야~!!");   //콘솔창 사이즈 조정

	//깜박이는 커서 지우기
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

//gotoxy함수
void gotoxy(int x, int y) {
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

//색 지정 함수
void ColorSet(int backColor, int textColor) {

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, (backColor << 4) + textColor);
}

//맵 출력하는 함수
void printMapScreen() {
	//콘솔창의 시작 지점과 맵 사이의 공백을 채우기 위해서 x와 y를 사용
	int x = 5, y = 3;	//맵이 시작하는 가장 왼쪽 위 끝점의 좌표

	for (int i = 0; i < 19; i++) {
		for (int j = 0; j < 25; j++) {
			gotoxy(x + j * 2, y + i);

			if (frameArr[i][j] == 2) {	//플레이어
				ColorSet(0, 10);
				printf("◎");
			}
			else if (frameArr[i][j] == 3) {	//도착지점
				ColorSet(0, 14);
				printf("★");
			}

			else if (frameArr[i][j] == 1) {	//벽
				ColorSet(0, 7);
				printf("▩");
			}

			else if (frameArr[i][j] == 4) {	//소화기
				ColorSet(0, 11);
				printf("§");
			}

			else if (frameArr[i][j] == 5) {	//불
				ColorSet(0, 12);
				printf("♨");
			}

			else if (frameArr[i][j] == 6) {	//엘베
				ColorSet(0, 14);
				printf("▥");
			}

			else if (frameArr[i][j] == 0)	//공백
				printf("  ");
		}
	}
}



//키를 입력받고, 움직임이나 불 끄기가 감지되면 화면을 새로고침 해주는 함수
int KeyControl(P* player, int *extinguisherCnt) {

	char pressKey;
	int flag_press_spacebar = 0;

	//키가 입력되면 잡아준다
	if (_kbhit()) {
		int tmpX = player->playerX, tmpY = player->playerY;	//플레이어 좌표의 초기값 기억
		int remember_sort = 0;	//스페이스바가 눌렸는지 확인하기 위한 플래그

		pressKey = _getch();

		if (pressKey == 32 && *extinguisherCnt > 0) {
			int extinguish_cnt = 0;	//불을 몇 개나 껐는지 확인

			if (frameArr[player->playerY + 1][player->playerX] == 5) {
				frameArr[player->playerY + 1][player->playerX] = 0;
				extinguish_cnt++;
			}
			if (frameArr[player->playerY - 1][player->playerX] == 5) {
				frameArr[player->playerY - 1][player->playerX] = 0;
				extinguish_cnt++;
			}
			if (frameArr[player->playerY][player->playerX + 1] == 5) {
				frameArr[player->playerY][player->playerX + 1] = 0;
				extinguish_cnt++;
			}
			if (frameArr[player->playerY][player->playerX - 1] == 5) {
				frameArr[player->playerY][player->playerX - 1] = 0;
				extinguish_cnt++;
			}
			
			if (extinguish_cnt > 0) {
				flag_press_spacebar = 1;
				(*extinguisherCnt)--;
			}
		}

		switch (pressKey) {

		case 72:   //위쪽방향
			if (frameArr[(player->playerY) - 1][player->playerX] != 1) {  //배열 밖으로 벗어나지 않도록!
				remember_sort = frameArr[(player->playerY) - 1][player->playerX];
				(player->playerY)--;
			}
			break;


		case 75:   //왼쪽방향
			if (frameArr[player->playerY][player->playerX - 1] != 1) {  //배열 밖으로 벗어나지 않도록!
				remember_sort = frameArr[player->playerY][player->playerX - 1];
				(player->playerX)--;
			}
			break;


		case 77:   //오른쪽방향
			if (frameArr[player->playerY][player->playerX + 1] != 1) {   //배열 밖으로 벗어나지 않도록!
				remember_sort = frameArr[player->playerY][player->playerX + 1];
				(player->playerX)++;
			}
			break;


		case 80:   //아래쪽방향
			if (frameArr[player->playerY + 1][player->playerX] != 1) {   //배열 밖으로 벗어나지 않도록!
				remember_sort = frameArr[player->playerY + 1][player->playerX];
				(player->playerY)++;
			}
			break;

		}
		

		//움직였거나 불을 껐다면 화면 재출력
		if (player->playerX != tmpX || player->playerY != tmpY || flag_press_spacebar == 1) {
			//지워주고
			frameArr[tmpY][tmpX] = 0;

			//움직이고
			frameArr[player->playerY][player->playerX] = 2;	//플레이어 좌표

			//출력하고
			printMapScreen();

			return remember_sort;
		}

		//움직이지 않는다면, -1 반환
		return -1;
	}	

}