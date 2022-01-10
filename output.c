#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

void printing(int**array,int R, int C){
  for (int i =0; i < R;i++){
    for (int j =0; j < C;j++){
      printf("%d ",array[i][j]);
    }
    printf("\n");
  }
}
