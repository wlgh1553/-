#include "menu.h"
#include "util.h"
#pragma comment(lib, "winmm.lib")


//BGM
void BGMplayer(int sort, int turn_on) {

	if (turn_on == 1) {
		switch (sort) {
		case 1:PlaySound(TEXT("mysterious-celesta-114064.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); break;
		case 2:PlaySound(TEXT("let-the-mystery-unfold-122118.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP); break;
		}
	}

	else
		PlaySound(NULL, 0, 0);
	return;
}

//선택시에 필요한 키 컨트롤
int menuKeyControl() {
	char tmp = _getch();
	if (tmp == 72 || tmp == 119 || tmp == 87) {
		return 1;
	}
	else if (tmp == 75 || tmp == 97 || tmp == 65) {
		return 2;
	}
	else if (tmp == 80 || tmp == 115 || tmp == 83)
		return 0;
	else if (tmp == 77 || tmp == 100 || tmp == 68)
		return 3;
	else if (tmp == ' ') {
		return 4;
	}
}

//메뉴 선택, 단계 선택
int menuDraw(int sort) {
	// sort 0 : 게임시작, 1 : 게임방법
	// 2 : 배경음악, 3 : 게임정보

	gotoxy(24 - 2, 12 + sort);
	printf("> ");

	gotoxy(24, 12);
	printf("게 임 시 작");
	gotoxy(24, 13);
	printf("게 임 방 법");
	gotoxy(24, 14);
	printf("배 경 음 악");
	gotoxy(24, 15);
	printf("게 임 정 보");
	gotoxy(24, 16);
	printf("   종 료  ");
	while (1)
	{
		int x = 24;
		int y = 12 + sort;
		while (1) {
			int n = menuKeyControl();
			switch (n) {
			case 1: {
				if (y > 12)
				{
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, --y);
					printf(">");
				}
				break;
			}
			case 0: {
				if (y < 16) {
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, ++y);
					printf(">");
				}
				break;
			}
			case 4: {
				return y - 12;
			}
			}
		}
	}
}
int map_sel_Draw() {
	gotoxy(24 - 2, 12);
	printf("> 학술정보원");
	gotoxy(24, 13);
	printf("대양 AI 센터");
	gotoxy(24, 14);
	printf("광개토관");
	gotoxy(24, 15);
	printf("대양홀");
	ColorSet(0, 8); gotoxy(24, 16); printf("뒤로가기");
	ColorSet(0, 15);  //다시 원래 색으로
	for (int i = 0; i < 5; i++)
	{
		if (pass_map_arr[i] == 1) {
			ColorSet(0, 11);
			gotoxy(40, 12 - 1 + i);
			printf("PASS");
			ColorSet(0, 7);
		}
	}
	while (1)
	{
		int x = 24;
		int y = 12;
		while (1) {
			int n = menuKeyControl();
			switch (n) {
			case 1: {
				if (y > 12)
				{
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, --y);
					printf(">");
				}
				break;
			}
			case 0: {
				if (y < 16) {
					gotoxy(x - 2, y);
					printf(" ");
					gotoxy(x - 2, ++y);
					printf(">");
				}
				break;
			}
			case 4: {
				int map_check = y - 11;

				return map_check;
			}
			}
		}
	}
}


//시작 인트로 담당 (순서 : 화재시 유의사항-게임제목 애니-컨셉설명)
void print_caution_sen() {

	char* sen[] = {
		"1. 소화기의 안전핀을 뽑습니다.","PULL THE PIN" ,
		"2. 한손은 손잡이를, 다른 한 손은 호스를 잡습니다.","AIM AT THE BASE OF THE FIRE" ,
		"3. 호스를 불쪽으로 향하게 합니다." , "SQUEEZE THE LEVER" ,
		"4. 상하 손잡이를 누르고 빗자루 쓸 듯 뿌립니다." ,  "SWEEP FROM SIDE TO SIDE",
		"1. \"불이야\"라고 크게 외치고 119를 부르십시오.","REPORT THE FIRE(DIAL 119)",
		"2. 화재경보 비상벨을 누르십시오.","SOUND THE ALARM",
		"3. 낮은 자세로 신속하게 대피하십시오.", "FOLLOW THE EVACUATION ROUTE IMMEDIATELY"
	};
	char* title1 = "소화기 사용법";
	char* title2 = "화재시 대피방법";

	char* skip = "숫자 5를 눌러 스킵할 수 있습니다.";

	char garbage = NULL;
	char kb = NULL;
	ColorSet(0, 8);
	gotoxy(14, 27);
	printf("%s", skip);
	ColorSet(0, 11);
	gotoxy(6, 5);
	if (_kbhit()) { kb = _getch(); if (kb == '5') return; }
	for (int i = 0; i < strlen(title1); i++) {
		if (_kbhit()) { kb = _getch(); if (kb == '5') return; }
		Sleep(40); printf("%c", title1[i]);
	}
	if (_kbhit()) { kb = _getch(); if (kb == '5') return; }
	for (int i = 0; i < 8; i++) {
		gotoxy(6, 6 + (i + 1) * 2);
		for (int j = 0; j < strlen(sen[i]); j++) {
			if (_kbhit()) { kb = _getch(); if (kb == '5') return; }
			Sleep(50); printf("%c", sen[i][j]);
		}
	}

	if (_kbhit()) { kb = _getch(); if (kb == '5') return; }
	Sleep(2000);
	system("cls");

	ColorSet(0, 8);
	gotoxy(14, 27);
	printf("%s", skip);
	ColorSet(0, 11);
	gotoxy(6, 5);


	for (int i = 0; i < strlen(title2); i++) {
		if (_kbhit()) { kb = _getch(); if (kb == '5') return; }
		Sleep(40); printf("%c", title2[i]);
	}
	for (int i = 8; i < 14; i++) {
		gotoxy(6, 6 + (i - 7) * 2);
		for (int j = 0; j < strlen(sen[i]); j++) {
			if (_kbhit()) { kb = _getch(); if (kb == '5') return; }
			Sleep(50); printf("%c", sen[i][j]);
		}
	}

	if (_kbhit()) { kb = _getch(); if (kb == '5') return; }
	Sleep(3000);
	if (_kbhit()) { kb = _getch(); if (kb == '5') return; }
}
void print_game_concept() {

	char* sen[] = {
		"세종대학교 A건물에 불이 났다...!",
		"소화기와 소화전을 찾아 불을 진압하고",
		"경로를 개척하여 건물에서 탈출해야 한다.",
		"연기를 너무 많이 마셔 위독해지기 전에",
		"건물을 탈출하라!"
	};

	ColorSet(0, 11);
	gotoxy(6, 5);
	for (int i = 0; i < 5; i++) {
		gotoxy(6, 6 + (i + 1) * 2);
		for (int j = 0; j < strlen(sen[i]); j++) {
			Sleep(30); printf("%c", sen[i][j]);
			if (_kbhit()) {
				int trash = _getch();
			}
		}
	}
	Sleep(700);
	ColorSet(0, 7);
	gotoxy(6, 20);
	printf("시작하려면 아무키나 누르세요!!!");
	while (1) {
		if (_kbhit()) {
			int trash = _getch();
			if (trash == 224)trash = _getch();
			system("cls"); return;
		}
	}

	return;
}

void introDraw(int introArr[][frameArrsizej]) {
	system("cls");
	int x = 5, y = 3;   //맵이 시작하는 가장 왼쪽 위 끝점의 좌표
	for (int i = 0; i < frameArrsizei; i++) {
		for (int j = 0; j < frameArrsizej; j++) {
			gotoxy(x + j * 2, y + i);
			if (introArr[i][j] == 1) {  //검은색
				ColorSet(0, 0);
				puts("■");
			}

			else if (introArr[i][j] == 0) {  //흰색
				ColorSet(0, 7);
				puts("■");
			}
		}
		if (i == 0) {	//맨앞 한글 없애려고 일부러 한번더 출력함
			gotoxy(x, y);
			ColorSet(0, 7);
			puts("■");
		}
		Sleep(30);
	}
	Sleep(1000);
	for (int i = 0; i < frameArrsizei + 9; i++) {
		if (i < frameArrsizei) {
			for (int j = 0; j < frameArrsizej; j++) {
				gotoxy(x + j * 2, y + i);
				if (introArr[i][j] == 1) {  //검은색
					ColorSet(0, 0);
					printf("  ");
				}

				else if (introArr[i][j] == 0) {  //불타는 효과
					ColorSet(0, 4);
					printf("♨");
				}
			}
		}

		if (i > 1) {
			int k = i - 9;
			for (int j = 0; j < frameArrsizej; j++) {
				gotoxy(x + j * 2, y + k);
				printf("  ");
			}
			Sleep(50);
		}

	}
	system("cls");
	Sleep(1000);
}
void intro_animation_total() {

	init();
	BGMplayer(1, 1);
	Sleep(2000);
	print_caution_sen();
	BGMplayer(1, 0);

	BGMplayer(2, 1); Sleep(500);
	ColorSet(0, 7);
	int introArr[frameArrsizei][frameArrsizej] = {
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
			{1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1},
			{1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,1},
			{1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,1,1,1},
			{1,0,1,1,1,1,1,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{1,0,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
			{1,0,0,1,0,0,1,0,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,1,1},
			{1,0,1,0,1,0,1,0,0,0,0,0,1,1,1,0,1,1,1,0,0,0,0,0,1},
			{1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,1},
			{1,0,1,1,1,0,1,0,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,1},
			{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
	};
	init();
	introDraw(introArr);

	print_game_concept();
}

//게임 방법 자세한 설명
void infoprint(int n) {
	if (n == 0) {
		system("cls");

		gotoxy(5, 1);
		printf("<아이콘 설명>");

		int exampleArr1[5][5] = {
			{1,1,1,1,1},
			{1,0,0,0,1},
			{1,0,5,0,1},
			{1,0,0,0,1},
			{1,1,1,1,1}
		};
		int exampleArr2[5][5] = {
			{1,1,1,1,1},
			{1,0,5,0,1},
			{1,5,5,5,1},
			{1,0,5,0,1},
			{1,1,1,1,1}
		};
		int exampleArr3[5][5] = {
			{1,1,1,1,1},
			{1,5,5,5,1},
			{1,5,5,5,1},
			{1,5,5,5,1},
			{1,1,1,1,1}
		};

		int x = 5, y = 3;   //맵이 시작하는 가장 왼쪽 위 끝점의 좌표
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				gotoxy(x + j * 2, y + i);
				if (exampleArr1[i][j] == 1) {   //벽
					ColorSet(0, 7);
					printf("▩");
				}
				else if (exampleArr1[i][j] == 5) {   //불
					ColorSet(0, 12);
					printf("♨");
				}
			}
		}
		gotoxy(20, 4);
		printf("1. 불");
		gotoxy(20, 6);
		printf("불은 10초마다 번집니다");

		y = 9;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				gotoxy(x + j * 2, y + i);
				if (exampleArr1[i][j] == 1) {   //벽
					ColorSet(0, 7);
					printf("▩");
				}
				else if (exampleArr1[i][j] == 5) {   //불
					ColorSet(0, 11);
					printf("§");
				}
			}
		}

		gotoxy(20, 10);
		printf("2. 소화기");
		gotoxy(20, 12);
		printf("상하좌우 불을 끌 수 있습니다");

		y = 15;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				gotoxy(x + j * 2, y + i);
				if (exampleArr1[i][j] == 1) {   //벽
					ColorSet(0, 7);
					printf("▩");
				}
				else if (exampleArr1[i][j] == 5) {   //불
					ColorSet(0, 11);
					printf("㉿");
				}
			}
		}

		gotoxy(20, 16);
		printf("3. 소화전");
		gotoxy(20, 18);
		printf("더 넓은 범위로 불을 끌 수 있습니다");

		y = 21;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				gotoxy(x + j * 2, y + i);
				if (exampleArr1[i][j] == 1) {   //벽
					ColorSet(0, 7);
					printf("▩");
				}
				else if (exampleArr1[i][j] == 5) {   //불
					ColorSet(0, 14);
					printf("▥");
				}
			}
		}

		gotoxy(20, 22);
		printf("4. 엘리베이터");
		gotoxy(20, 24);
		printf("화재시에는 엘리베이터를 이용 금지.");

		Sleep(700);
		if (_kbhit()) {
			int trash = _getch();
			if (trash == 224)trash = _getch();
			system("cls"); return;
		}
		x = 5, y = 3;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				gotoxy(x + j * 2, y + i);

				if (exampleArr2[i][j] == 1) {   //벽
					ColorSet(0, 7);
					printf("▩");
				}
				else if (exampleArr2[i][j] == 5 || exampleArr2[i][j] == 7) {   //불
					ColorSet(0, 12);
					printf("♨");
				}
			}
		} Sleep(700);
		if (_kbhit()) {
			int trash = _getch();
			if (trash == 224)trash = _getch();
			system("cls"); return;
			return;
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				gotoxy(x + j * 2, y + i);

				if (exampleArr3[i][j] == 1) {   //벽
					ColorSet(0, 7);
					printf("▩");
				}
				else if (exampleArr3[i][j] == 5 || exampleArr3[i][j] == 7) {   //불
					ColorSet(0, 12);
					printf("♨");
				}
			}
		}

		gotoxy(13, 27);
		printf("PRESS ANYTHING TO NEXT PAGE!!!");
	}
	else if (n == 1) {
		system("cls");
		gotoxy(5, 1);
		printf("<아이콘 설명>");
		int exampleArr1[5][7] = {
			{1,1,1,1,1,1,1},
			{1,0,0,0,0,0,1},
			{1,0,2,0,3,0,1},
			{1,0,0,0,0,0,1},
			{1,1,1,1,1,1,1}
		};
		int exampleArr2[5][7] = {
			{1,1,1,1,1,1,1},
			{1,0,2,0,0,0,1},
			{1,0,0,0,4,0,1},
			{1,0,3,0,0,0,1},
			{1,1,1,1,1,1,1}
		};

		int x = 2, y = 3;   //맵이 시작하는 가장 왼쪽 위 끝점의 좌표
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 7; j++) {
				gotoxy(x + j * 2, y + i);
				if (exampleArr1[i][j] == 1) {   //벽
					ColorSet(0, 7);
					printf("▩");
				}
				else if (exampleArr1[i][j] == 2) {
					ColorSet(0, 10);
					printf("◎");
				}
				else if (exampleArr1[i][j] == 3) {
					ColorSet(0, 10);
					printf("★");
				}
			}
		}
		gotoxy(18, 3);
		printf("5. 플레이어1, 목적지1");
		gotoxy(18, 5);
		printf("플레이어1(◎)은 해당 목적지에 가야함(★)");
		gotoxy(18, 7);
		printf("움직이는 방법 :wasd키");
		gotoxy(18, 9);
		printf("소화 방법 : Tab키");

		y = 12;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 7; j++) {
				gotoxy(x + j * 2, y + i);
				if (exampleArr1[i][j] == 1) {   //벽
					ColorSet(0, 7);
					printf("▩");
				}
				else if (exampleArr1[i][j] == 2) {
					ColorSet(0, 13);
					printf("◎");
				}
				else if (exampleArr1[i][j] == 3) {
					ColorSet(0, 13);
					printf("★");
				}
			}
		}
		gotoxy(18, 12);
		printf("6. 플레이어2, 목적지2");
		gotoxy(18, 14);
		printf("플레이어2(◎)는 해당 목적지에 가야함(★)");
		gotoxy(18, 16);
		printf("움직이는 방법 :키보드 방향키");
		gotoxy(18, 18);
		printf("소화 방법 : 숫자 0 입력");

		y = 20;
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 7; j++) {
				gotoxy(x + j * 2, y + i);
				if (exampleArr2[i][j] == 1) {   //벽
					ColorSet(0, 7);
					printf("▩");
				}
				else if (exampleArr2[i][j] == 2) {
					ColorSet(0, 10);
					printf("◎");
				}
				else if (exampleArr2[i][j] == 3) {
					ColorSet(0, 13);
					printf("◎");
				}
				else if (exampleArr2[i][j] == 4) {
					ColorSet(0, 6);
					printf("★");
				}
			}
		}
		gotoxy(18, 21);
		printf("7. 목적지3");
		gotoxy(18, 23);
		printf("어떤 플레이어이든 통과 가능");

		gotoxy(13, 27);
		printf("PRESS ANYTHING TO NEXT PAGE!!!");
	}
	else if (n == 2) {
		system("cls");
		gotoxy(5, 3);
		printf("<소화 방식>");

		int exampleArr1_1[5][5] = {
			{1,1,1,1,1},
			{1,5,5,5,1},
			{1,5,2,5,1},
			{1,5,5,5,1},
			{1,1,1,1,1}
		};
		int exampleArr1_2[5][5] = {
			{1,1,1,1,1},
			{1,5,0,5,1},
			{1,0,2,0,1},
			{1,5,0,5,1},
			{1,1,1,1,1}
		};

		int exampleArr2_1[7][7] = {
			{1,1,1,1,1,1,1},
			{1,5,5,5,5,5,1},
			{1,5,5,5,5,5,1},
			{1,5,5,2,5,5,1},
			{1,5,5,5,5,5,1},
			{1,5,5,5,5,5,1},
			{1,1,1,1,1,1,1}
		};
		int exampleArr2_2[7][7] = {
			{1,1,1,1,1,1,1},
			{1,5,5,0,5,5,1},
			{1,5,5,0,5,5,1},
			{1,0,0,2,0,0,1},
			{1,5,5,0,5,5,1},
			{1,5,5,0,5,5,1},
			{1,1,1,1,1,1,1}
		};

		while (1) {
			int x = 5, y = 7;   //맵이 시작하는 가장 왼쪽 위 끝점의 좌표
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					gotoxy(x + j * 2, y + i);
					if (exampleArr1_1[i][j] == 1) {   //벽
						ColorSet(0, 7);
						printf("▩");
					}
					else if (exampleArr1_1[i][j] == 5) {   //불
						ColorSet(0, 12);
						printf("♨");
					}
					else if (exampleArr1_1[i][j] == 2) {
						ColorSet(0, 10);
						printf("◎");
					}
				}
			}
			gotoxy(22, 5);
			ColorSet(0, 7);
			printf("1. 소화기");

			gotoxy(22, 7);
			ColorSet(0, 11);
			printf("§");

			gotoxy(24, 7);
			ColorSet(0, 7);
			printf(" (소화기)를 먹은뒤");

			gotoxy(22, 9);
			printf("플레이어별 소화버튼을 누르면");

			gotoxy(22, 11);
			printf("다음과 같이 불을 끌 수 있습니다.");


			y = 16;
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 7; j++) {
					gotoxy(x + j * 2, y + i);
					if (exampleArr2_1[i][j] == 1) {   //벽
						ColorSet(0, 7);
						printf("▩");
					}
					else if (exampleArr2_1[i][j] == 5) {   //불
						ColorSet(0, 12);
						printf("♨");
					}
					else if (exampleArr2_1[i][j] == 2) {
						ColorSet(0, 10);
						printf("◎");
					}
					else if (exampleArr2_1[i][j] == 0) {
						printf("  ");
					}
				}
			}

			gotoxy(22, 16);
			ColorSet(0, 7);
			printf("2. 소화전");

			gotoxy(22, 18);
			ColorSet(0, 11);
			printf("㉿");

			gotoxy(24, 18);
			ColorSet(0, 7);
			printf(" (소화전)를 먹은뒤");

			gotoxy(22, 20);
			printf("플레이어별 소화버튼을 누르면");

			gotoxy(22, 22);
			printf("다음과 같이 불을 끌 수 있습니다.");

			gotoxy(13, 27);
			printf("PRESS ANYTHING TO NEXT PAGE!!!");

			if (_kbhit()) {
				int trash = _getch();
				if (trash == 224)trash = _getch();
				system("cls"); return;
				return;
			}

			Sleep(500);
			x = 5, y = 7;
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					gotoxy(x + j * 2, y + i);
					if (exampleArr1_2[i][j] == 1) {   //벽
						ColorSet(0, 7);
						printf("▩");
					}
					else if (exampleArr1_2[i][j] == 5) {   //불
						ColorSet(0, 12);
						printf("♨");
					}
					else if (exampleArr1_2[i][j] == 2) {
						ColorSet(0, 10);
						printf("◎");
					}
					else if (exampleArr1_2[i][j] == 0) {
						printf("  ");
					}
				}
			}
			if (_kbhit()) {
				int trash = _getch();
				if (trash == 224)trash = _getch();
				system("cls"); return;
				return;
			}
			Sleep(500);
			y = 16;
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 7; j++) {
					gotoxy(x + j * 2, y + i);
					if (exampleArr2_2[i][j] == 1) {   //벽
						ColorSet(0, 7);
						printf("▩");
					}
					else if (exampleArr2_2[i][j] == 5) {   //불
						ColorSet(0, 12);
						printf("♨");
					}
					else if (exampleArr2_2[i][j] == 2) {
						ColorSet(0, 10);
						printf("◎");
					}
					else if (exampleArr2_2[i][j] == 0) {
						printf("  ");
					}
				}
			}
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 7; j++) {
					gotoxy(x + j * 2, y + i);
					if (exampleArr2_2[i][j] == 1) {   //벽
						ColorSet(0, 7);
						printf("▩");
					}
					else if (exampleArr2_2[i][j] == 5) {   //불
						ColorSet(0, 12);
						printf("♨");
					}
					else if (exampleArr2_2[i][j] == 2) {
						ColorSet(0, 10);
						printf("◎");
					}
					else if (exampleArr2_2[i][j] == 0) {
						ColorSet(0, 14);
						printf("＊");

					}
				}
			} if (_kbhit()) {
				int trash = _getch();
				if (trash == 224)trash = _getch();
				system("cls"); return;
				return;
			}
			Sleep(300);
			for (int i = 0; i < 7; i++) {
				for (int j = 0; j < 7; j++) {
					gotoxy(x + j * 2, y + i);
					if (exampleArr2_2[i][j] == 1) {   //벽
						ColorSet(0, 7);
						printf("▩");
					}
					else if (exampleArr2_2[i][j] == 5) {   //불
						ColorSet(0, 12);
						printf("♨");
					}
					else if (exampleArr2_2[i][j] == 2) {
						ColorSet(0, 10);
						printf("◎");
					}
					else if (exampleArr2_2[i][j] == 0) {
						printf("  ");
					}
				}
			}
			if (_kbhit()) {
				int trash = _getch();
				if (trash == 224)trash = _getch();
				system("cls"); return;
			}
			Sleep(500);




			if (_kbhit()) {
				int trash = _getch();
				if (trash == 224)trash = _getch();
				system("cls"); return;
			}
		}

	}
	else if (n == 3) {
		system("cls");

		gotoxy(10, 5);
		printf("[성공]");
		gotoxy(10, 7);
		printf(" 제한 시간 내에 플레이어 모두가");
		gotoxy(10, 9);
		printf(" 해당 맵의 탈출구로 도착해야 성공");


		gotoxy(10, 13);
		printf("[실패]");
		gotoxy(10, 15);
		printf(" 1. 불에 뛰어든 경우");
		gotoxy(10, 17);
		printf(" 2. 시간이 다 된 경우");
		gotoxy(10, frameArrsizei);
		printf(" 3. 엘레베이터에 뛰어들 경우");


		gotoxy(13, 27);
		printf("PRESS ANYTHING TO NEXT PAGE!!!");
	}

	while (1) {
		if (_kbhit()) {
			int trash = _getch();
			if (trash == 224)trash = _getch();
			system("cls"); return;
		}
	}
}

void person_info()
{
	gotoxy(20, 10); printf("   [개발자 정보]");
	gotoxy(20, 11); printf("22011824 이지호 (SW)");
	gotoxy(20, 12); printf("22011815 서현진 (SW)");
	gotoxy(20, 13); printf("22011819 복민정 (SW)");


	Sleep(700);
	ColorSet(0, 7);
	gotoxy(15, 20);
	printf("돌아가려면 아무키나 누르세요!!!");
	while (1) {
		if (_getch())
		{
			break;
		}
	}
}

//선택하고, 그 값을 메인함수에게 전달하는 함수
int menu_main(int* is_bgm_on) {

	int menumode = menuDraw(0);
	while (1) {

		if (menumode == 0)  //게임 시작
		{
			system("cls");
			return 0;
		}
		else if (menumode == 1)  //게임 방법
		{
			for (int i = 0; i < 4; i++)
			{
				infoprint(i);
			}
			system("cls");
			menumode = menuDraw(1);
			continue;
		}
		else if (menumode == 2)  //배경음악
		{
			if (*is_bgm_on == 1) {
				BGMplayer(2, 0);
				*is_bgm_on = 0;
			}
			else {
				BGMplayer(2, 1);
				*is_bgm_on = 1;
			}
			menumode = menuDraw(2);
			continue;
		}
		else if (menumode == 3)
		{
			system("cls");
			person_info();
			system("cls");
			menumode = menuDraw(3);
		}
		else if (menumode == 4)
		{
			system("cls");
			return -1;
		}
	}

	return 0;
}