#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "logika.h"

int SCORE=0;


int ** naalokuj_pamet(int R, int C) {
  int** arr = (int**)malloc(R * sizeof(int*));
  if (!arr) {fprintf(stderr, "out of memory 1"); exit(-1);}

    for (int i = 0; i < R; i++){
        arr[i] = (int*)malloc(C * sizeof(int));
        if (!*arr) {fprintf(stderr, "out of memory 2"); exit(-1);}

        for (int j = 0; j < C; j++)
            arr[i][j] = 0;
    }

    return arr;
}

void * uvolni_pamet(int ** arr_aloc, int R) {
    for (int i = 0; i < R; i++)
        free(arr_aloc[i]);

    free(arr_aloc);
    return 0;
}

int vygeneruj_cislo() {
  int cislo = rand();
  if (cislo%2 == 0) {return 4;
  //printf("%d\n", rand());
  } else return 2;
}


int ** make_control_array(int**array, int R, int C){
  int ** control_array;
  control_array = naalokuj_pamet(R,C);
  for (int i = 0; i < R; i++){
      for (int j = 0; j < C; j++){
        control_array[i][j] = array[i][j];
      }
    }
  return control_array;
}

int vygeneruj_pozici(int pocet_volnych) {
  return rand()%pocet_volnych + 1;
}


int win(int**array, int i, int j){
  int lose = 0;
  if (array[i][j] == 2048){
    lose = 2;
    printf("You are the winner!!!\n\n");
    //printing(array,R,C);
  }
  return lose;
}

int count_zeros(int ** array, int R, int C) {
  int num = 0;
  for (int i = 0; i < R; i++){
    for (int j = 0; j < C; j++){
      if (array[i][j] == 0) num++;
    } 
  }
  return num;
}




int move_left(int ** array, int R, int C){
  int same = 0;
  int lose = 0;
  int wining = 0;
  int** control = make_control_array(array, R, C);
  for (int r = 0; r < R; r++){
    for (int j = 0; j < C; j++){
      for (int  i = j; i < (C-1); i++){
        if (array[r][j] == 0){
          if (array[r][i+1] > 0){
            array[r][j] = array[r][i+1];
            array[r][i+1] = 0;
          }
        }
      }
    }
    for (int  k = 0; k < (C-1); k++){
      if (array[r][k]==array[r][k+1]){
        array[r][k] = 2 * array[r][k];
        SCORE += array[r][k];
        for (int  l = (k+1); l < (C-1); l++){
          array[r][l] = array[r][l+1];
          array[r][l+1] = 0;
        }
        array[r][C-1] = 0;
        wining = win(array,r,k);
        if (wining == 2) {lose = 2;}
      }
    }
  }
  for (int i = 0; i < R; i++){
      for (int j = 0; j < C; j++){
        if (array[i][j] != control[i][j]){
          same = 3;
        }
      }
  }
  uvolni_pamet(control,R);

  if (lose == 2){return lose;}
  else {return same;}
}

int move_right(int ** array, int R, int C){
  int same = 0;
  int lose = 0;
  int wining = 0;
  int** control = make_control_array(array, R, C);

  for (int r = 0; r <= (R-1); r++){
    for (int j = (C-1); j >= 0 ; j--){
      for (int  i = j; i > 0; i--){
        if (array[r][j] == 0){
          if (array[r][i-1] > 0){
            array[r][j] = array[r][i-1];
            array[r][i-1] = 0;
          }
        }
      }
    }

    for (int  k = (C-1); k > 0 ; k--){
      if (array[r][k]==array[r][k-1]){
        array[r][k] = 2 * array[r][k];
        SCORE += array[r][k];

        for (int  l = (k-1); l > 0 ; l--){
          array[r][l] = array[r][l-1];
          array[r][l-1] = 0;
        }
        array[r][0] = 0;
        wining = win(array,r,k);
         if (wining == 2) {lose = 2;}
      }
    }
  }
  for (int i = 0; i < R; i++){
      for (int j = 0; j < C; j++){
        if (array[i][j] != control[i][j]){
          same = 3;
        }
      }
  }
  uvolni_pamet(control,R);

  if (lose == 2){return lose;}
  else {return same;}
}

int move_up(int ** array, int R, int C){
  int same = 0;
  int lose = 0;
  int wining = 0;
  int** control = make_control_array(array, R, C);
  for (int c = 0; c < C; c++){
    for (int j = 0; j < R; j++){
      for (int i = j; i < (R-1); i++){
        if (array[j][c] == 0){
          if (array[i+1][c] > 0){
            array[j][c] = array[i+1][c];
            array[i+1][c] = 0;
          }
        }
      }
    }
    for (int  k = 0; k < (R-1); k++){
      if (array[k][c]==array[k+1][c]){
        array[k][c] = 2 * array[k][c];
        SCORE += array[k][c];

        for (int l = (k+1); l < (R-1); l++){
          array[l][c] = array[l+1][c];
          array[l+1][c] = 0;
        }
        array[R-1][c] = 0;
        wining = win(array,k,c);
         if (wining == 2) {lose = 2;}
      }
    }
  }
  for (int i = 0; i < R; i++){
      for (int j = 0; j < C; j++){
        if (array[i][j] != control[i][j]){
          same = 3;
        }
      }
  }
  uvolni_pamet(control,R);

  if (lose == 2){return lose;}
  else {return same;}
}

int move_down(int ** array, int R, int C){
  int same = 0;
  int lose = 0;
  int wining = 0;
  int** control = make_control_array(array, R, C);
  for (int c = 0; c <= (C-1); c++){
    for (int j = (R-1); j >= 0 ; j--){
      for (int  i = j; i > 0; i--){
        if (array[j][c] == 0){
          if (array[i-1][c] > 0){
            array[j][c] = array[i-1][c];
            array[i-1][c] = 0;
            //printf("%d %d %d %d\n",array[r][0],array[r][1],array[r][2],array[r][3]);
          }
        }
      }
    }

    for (int  k = (R-1); k > 0 ; k--){
      if (array[k][c]==array[k-1][c]){
        array[k][c] = 2 * array[k][c];
        SCORE += array[k][c];

        for (int  l = (k-1); l > 0 ; l--){
          array[l][c] = array[l-1][c];
          array[l-1][c] = 0;
        }
        array[0][c] = 0;
        wining = win(array,k,c);
         if (wining == 2) {lose = 2;}
      }
    }
  }
  for (int i = 0; i < R; i++){
      for (int j = 0; j < C; j++){
        if (array[i][j] != control[i][j]){
          same = 3;
        }
      }
  }
  uvolni_pamet(control,R);

  if (lose == 2){return lose;}
  else {return same;}
}


int is_Lost(int**array, int R, int C){
  int lose =0;
  int cLose;
  int** c = make_control_array(array, R, C);
  cLose = move_down(c, R, C);
  //printf("LOSE:");
  //printing();
  cLose = move_left(c, R, C);
  //printing();
  if (count_zeros(c, R, C)==0) lose=1;
  uvolni_pamet(c,R);
  if (lose == 1) {
    //printing(array,R,C);
    printf("You lose!!!\n\n");
  }
  return lose;
}

int add_Num(int** array, int R, int C) {
  int lose = 0;
  int numOfZeros = count_zeros(array, R, C);
  if (numOfZeros == 0) {
    lose = is_Lost(array, R, C);
  } else {
    int number = vygeneruj_cislo();
    int position = vygeneruj_pozici(numOfZeros);
    //printf("SCORE: %d zeros: %d, num = %d,  pozice = %d\n", SCORE, numOfZeros, number, position );
      for (int i = 0; i < R; i++){
      for (int j = 0; j < C; j++){
        if (array[i][j] == 0){ 
          position--;
          if (position == 0) {array[i][j] = number; break;}
        }
      }
    } 
    if (count_zeros(array, R,C) == 0) {
      lose = is_Lost(array, R, C);
    }
  }
  return lose;
}

int move_left_add(int ** array, int R, int C){
  int lose=0;
  lose = move_left(array, R, C);
  
  if (lose == 3) { 
    lose =0;
    lose = add_Num(array, R, C);  
    }

  return lose;
}

int move_right_add(int ** array, int R, int C){
  int lose =0;
  lose = move_right(array, R, C);
  if (lose == 3) {lose =add_Num(array, R, C);} 
  return lose;
}
int move_up_add(int ** array, int R, int C){
  int lose = 0;
  lose = move_up(array, R, C);
  if (lose == 3) {lose = add_Num(array, R, C);}
  return lose;
}
int move_down_add(int ** array, int R, int C){
  int lose = 0;
  lose = move_down(array, R, C);
  if (lose == 3) {lose =add_Num(array, R, C);}

  return lose;
}

int ** startGame(int R, int C, int lose){
  if (R < 4 || C < 4){
    printf("Error : Input must be R and C must be at least 4\n");
    exit(-1);
  }
  int ** array;
  array = naalokuj_pamet(R, C);

  lose =add_Num(array,R,C);
  lose =add_Num(array,R,C);
  return array;
}
