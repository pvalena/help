#pragma once

extern int SCORE;


int ** naalokuj_pamet(int R, int C);
void * uvolni_pamet(int ** arr_aloc, int R);

int add_Num(int** array, int R, int C);
int move_left_add(int ** array, int R, int C);
int move_right_add(int ** array, int R, int C);
int move_up_add(int ** array, int R, int C);
int move_down_add(int ** array, int R, int C);
int ** startGame(int R, int C, int lose);





