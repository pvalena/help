#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "logika.h"


void printing(int**array,int R, int C){
  printf("2048 SCORE: %d \n",SCORE);
  for (int i =0; i < R;i++){
    for (int j =0; j < C;j++){
      printf("%5d ",array[i][j]);
    }
    printf("\n");
    
  }
  printf("---------\n");
}

void vypisHlasku(int lose){
  if (lose == 1){
    printf("Oh, You lost!!\n");
  } else if (lose == 2){
    printf("WOW, You won!!\n");
  }
}
