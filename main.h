#ifndef __STDIO_H__
#define __STDIO_H__

#include <stdio.h>

#endif

#ifndef __WINDOWS_H__
#define __WINDOWS_H__

#include <windows.h>

#endif



#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<string.h>
#include <mmsystem.h>

#define frameArrsizei 19
#define frameArrsizej 25

int pass_map_arr[5];
void GameStart_Map1(int frameArr[][25], int TimeLimit, int extLimit, int exit_player1_X, int exit_player1_Y,
	int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y, int map_num);
void GameStart_Map2(int frameArr[][25], int TimeLimit, int extLimit, int exit_player1_X, int exit_player1_Y,
	int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y, int map_num);
void GameStart_Map3(int frameArr[][25], int TimeLimit, int extLimit, int exit_player1_X, int exit_player1_Y,
	int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y, int map_num);
void GameStart_Map4(int frameArr[][25], int TimeLimit, int extLimit, int exit_player1_X, int exit_player1_Y,
	int exit_player2_X, int exit_player2_Y, int exit_player3_X, int exit_player3_Y, int map_num);

void Ready_Map(int map_num);