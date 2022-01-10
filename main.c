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
/*
   array[0][0] = 2 ;
   array[0][1] = 0 ;
   array[0][2] = 3 ;
   array[0][3] = 4 ;
   array[1][3] = 8 ;
   array[1][2] = 5 ;
   array[1][1] = 4 ;
   array[1][0] = 8 ;
   array[2][3] = 22 ;
   array[2][2] = 13 ;
   array[2][1] = 8 ;
   array[2][0] = 2 ;
   array[3][3] = 4 ;
   array[3][2] = 2 ;
   array[3][1] = 16 ;
   array[3][0] = 4 ;*/ 
  printing(array,R,C);
 
       
  int num = 0;
  char movement;

  
  add_Num(array,R,C,lose);
  add_Num(array,R,C,lose);
  printing(array,R,C); 
 
  while((movement != 'x') && (win == 0) && (lose == 0)) {
    movement = getchar();
    switch (movement){
      case 'w': 
        move_up_add(array,R,C,lose);

        printing(array,R,C);
        break;
      case 's':
        move_down_add(array,R,C,lose);
        //printing();
     
        printing(array,R,C);
        break;
      case 'a':
        move_left_add(array,R,C,lose);
        printing(array,R,C);
        break;
      case 'd': 
        move_right_add(array,R,C,lose);
        printing(array,R,C);
        break;
    }
  }
  uvolni_pamet(array,R);  
  return 0;
}
