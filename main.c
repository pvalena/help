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

  
  int lose = 0;
  int** array;
  char movement;
  
  array = startGame(R, C,lose);
  printing(array,R,C); 
  /*array[0][1]=1024;
  array[0][0]=1024;*/

  while((movement != 'x') && (lose == 0)) {
    movement = getchar();
    switch (movement){
      case 'w': 
        lose = move_up_add(array,R,C);
         printing(array,R,C);
        break;
      case 's':
        lose = move_down_add(array,R,C);
         printing(array,R,C);
        break;
      case 'a':
        lose = move_left_add(array,R,C);
        printing(array,R,C);
        break;
      case 'd': 
        lose = move_right_add(array,R,C);
         printing(array,R,C);
        break;
    }
    vypisHlasku(lose);
  }
  uvolni_pamet(array,R);  
  return 0;
}