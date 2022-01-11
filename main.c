#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "output.h"
#include "logika.h"

int main (int argc, char **argv){

  assert(argc == 3);
  const int R = atoi(argv[1]);
  const int C = atoi(argv[2]);

  if (R < 4 || C < 4){
    printf("Error : Input must be R and C must be at least 4");
    return 1;
  }

  int win = 0;
  int lose = 0;
  int SCORE = 0;

  int** array;
  array = naalokuj_pamet(R, C);

  printing(array,R,C);

  int num = 0;

  add_Num(array,R,C,lose);
  add_Num(array,R,C,lose);
  printing(array,R,C);

  int quit = 0;

  while(!quit) {
    switch ( getchar() ){

      case 'w':
        move_up_add(array,R,C,lose);
        break;

      case 's':
        move_down_add(array,R,C,lose);
        break;

      case 'a':
        move_left_add(array,R,C,lose);
        break;

      case 'd':
        move_right_add(array,R,C,lose);
        break;

      case 'x':
        quit = 1;
        break;
    }

    printing(array,R,C);
  }

  uvolni_pamet(array,R);
  return 0;
}
