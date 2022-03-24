#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int WIDTH = 4;
int HEIGHT = 4;
int array[4][4]={0};
int WIN = 0;
int LOSE = 0;
int SCORE = 0;
int CONTROL = 0;

int vygeneruj_cislo() {
  int cislo = rand();
  if (cislo%2 == 0) {return 4;
  //printf("%d\n", rand());
  } else return 2;
}
/*
int make_control_array(c){
  for (int i = 0; i < WIDTH; i++){
      for (int j = 0; j < HEIGHT; j++){
        array[i][j] = c[i][j];
      } 
    }
}
*/
int vygeneruj_pozici(int pocet_volnych) {
  return rand()%pocet_volnych + 1;
}

void win(int i, int j){
  if (array[i][j] == 2048){
    WIN = 1;
    printf("You are the winner!!!\n\n");
  }
}
void printing(){
  //printf("%d\n",WIN);
    printf("%d %d %d %d\n",array[0][0],array[0][1],array[0][2],array[0][3]);
    printf("%d %d %d %d\n",array[1][0],array[1][1],array[1][2],array[1][3]);
    printf("%d %d %d %d\n",array[2][0],array[2][1],array[2][2],array[2][3]);
    printf("%d %d %d %d\n\n",array[3][0],array[3][1],array[3][2],array[3][3]);
}

int move_left(){
  int same = 0;
  int control[4][4]={0};
  for (int i = 0; i < WIDTH; i++){
      for (int j = 0; j < HEIGHT; j++){
        control[i][j] = array[i][j];
      } 
  }
  for (int r = 0; r <= (HEIGHT-1); r++){
    for (int j = 0; j <= (WIDTH-1) ; j++){
      for (int  i = j; i < (WIDTH-1); i++){  
        if (array[r][j] == 0){
          if (array[r][i+1] > 0){
            array[r][j] = array[r][i+1];
            array[r][i+1] = 0;
          }
        }
      }
    }
    for (int  k = 0; k < (WIDTH-1); k++){
      if (array[r][k]==array[r][k+1]){
        array[r][k] = 2 * array[r][k];
        //if (CONTROL == 0) {SCORE += array[r][k];}
        //win(r,k);
        for (int  l = (k+1); l < (WIDTH-1); l++){
          array[r][l] = array[r][l+1];
          array[r][l+1] = 0;
        }
        array[r][WIDTH-1] = 0;
      }
    }
  }
  for (int i = 0; i < WIDTH; i++){
      for (int j = 0; j < HEIGHT; j++){
        if (array[i][j] != control[i][j]){
          same = 1;
        }
      } 
  }return same;
}

void move_right(){
  for (int r = 0; r <= (HEIGHT-1); r++){
    for (int j = (WIDTH-1); j >= 0 ; j--){
      for (int  i = j; i > 0; i--){
        if (array[r][j] == 0){
          if (array[r][i-1] > 0){
            array[r][j] = array[r][i-1];
            array[r][i-1] = 0;
            //printf("%d %d %d %d\n",array[r][0],array[r][1],array[r][2],array[r][3]);
          }
        } 
      }
    }

    for (int  k = (WIDTH-1); k > 0 ; k--){
      if (array[r][k]==array[r][k-1]){
        array[r][k] = 2 * array[r][k];
        if (CONTROL == 0) SCORE += array[r][k];
        win(r,k);
        for (int  l = (k-1); l > 0 ; l--){
          array[r][l] = array[r][l-1];
          array[r][l-1] = 0;
        }
        array[r][0] = 0;
      }
    }
  }
}

void move_up(){
  for (int c = 0; c <= (WIDTH-1); c++){
    for (int j = 0; j <= (HEIGHT-1) ; j++){
      for (int  i = j; i < (HEIGHT-1); i++){  
        if (array[j][c] == 0){
          if (array[i+1][c] > 0){
            array[j][c] = array[i+1][c];
            array[i+1][c] = 0;
          }
        }
      }
    }
    for (int  k = 0; k < (HEIGHT-1); k++){
      if (array[k][c]==array[k+1][c]){
        array[k][c] = 2 * array[k][c];
        if (CONTROL == 0) SCORE += array[k][c];
        win(k,c);
        for (int  l = (k+1); l < (WIDTH-1); l++){
          array[l][c] = array[l+1][c];
          array[l+1][c] = 0;
        }
        array[HEIGHT-1][c] = 0;
      }
    }
  }
}

void move_down(){
  for (int c = 0; c <= (WIDTH-1); c++){
    for (int j = (HEIGHT-1); j >= 0 ; j--){
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

    for (int  k = (WIDTH-1); k > 0 ; k--){
      if (array[k][c]==array[k-1][c]){
        array[k][c] = 2 * array[k][c];
         if (CONTROL == 0)SCORE += array[k][c];
        win(k,c);
        for (int  l = (k-1); l > 0 ; l--){
          array[l][c] = array[l-1][c];
          array[l-1][c] = 0;
        }
        array[0][c] = 0;
      }
    }
  }
}

bool is_zero(int i, int j){
  if (array[i][j] == 0) return true;
  return false;
}

int count_zeros() {
  int num = 0;
  for (int i = 0; i < WIDTH; i++){
    for (int j = 0; j < HEIGHT; j++){
      if (is_zero(i,j)) num++;
    } 
  }
  return num;
}

void is_Lost(){
  CONTROL = 1;
  int c[4][4] = {0};
  for (int i = 0; i < WIDTH; i++){
    for (int j = 0; j < HEIGHT; j++){
      c[i][j] = array[i][j];
    } 
  }
  move_down();
  //printf("LOSE:");
  //printing();
  move_left();
  //printing();
  if (count_zeros()==0) LOSE=1;

  if (LOSE == 0) {
    for (int i = 0; i < WIDTH; i++){
      for (int j = 0; j < HEIGHT; j++){
        array[i][j] = c[i][j];
      } 
    }
  } else {
    printf("You lose!!!\n\n");
  }
  CONTROL = 0;
}

void add_Num() {
  int numOfZeros = count_zeros();
  if (count_zeros() == 0) {
    is_Lost();
  } else {
    int number = vygeneruj_cislo();
    int position = vygeneruj_pozici(numOfZeros);
    printf("SCORE: %d zeros: %d, num = %d,  pozice = %d\n", SCORE, numOfZeros, number, position );
      for (int i = 0; i < WIDTH; i++){
      for (int j = 0; j < HEIGHT; j++){
        if (array[i][j] == 0){ 
          position--;
          if (position == 0) {array[i][j] = number; break;}
        }
      }
    } 
    if (count_zeros() == 0) {
      is_Lost();
    }
  }
}
void move_left_add(){
  int same = move_left();
  if (same == 1) add_Num();
}

int main(void) {
  int num = 0;
  char movement;
   /*array[0][0] = 4 ;
   array[0][1] = 0 ;
   array[0][2] = 4 ;
   array[0][3] = 4 ;
   array[1][3] = 8 ;
   array[1][2] = 8 ;
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
  add_Num();
  add_Num();
  printf("%d %d %d %d\n",array[0][0],array[0][1],array[0][2],array[0][3]);
  printf("%d %d %d %d\n",array[1][0],array[1][1],array[1][2],array[1][3]);
  printf("%d %d %d %d\n",array[2][0],array[2][1],array[2][2],array[2][3]);
  printf("%d %d %d %d\n",array[3][0],array[3][1],array[3][2],array[3][3]); 
 
  while((movement != 'x') && (WIN == 0) && (LOSE == 0)) {
    movement = getchar();
    switch (movement){
      case 'w': 
        move_up();
        add_Num();
        printing();
        break;
      case 's':
        move_down();
        //printing();
        add_Num();
        printing();
        break;
      case 'a':
        move_left_add();
        //add_Num();
        printing();
        break;
      case 'd': 
        move_right();
        add_Num();
        printing();
        break;
    }
  }
    
  return 0;
}
