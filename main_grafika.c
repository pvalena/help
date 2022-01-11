#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "logika.h"

const int MEZERA = 15;
const int WIDTH = 106;
const int HEIGHT = WIDTH;
const int START_X = 100;
const int START_Y = 120;
typedef SDL_Texture* Sources[12];


SDL_Texture* loadTexture(char* image, SDL_Renderer *ren){
	SDL_Texture *texture = NULL;
	//Load the image
	SDL_Surface *loadedImage = SDL_LoadBMP(image);
	//If the loading went ok, convert to texture and return the texture
	if (loadedImage != NULL){
		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		SDL_FreeSurface(loadedImage);
		//Make sure converting went ok too
		if (texture == NULL){
			printf("loadTexture Error: %s\n", SDL_GetError());
		}
	}
	else {
        printf( "SDL_LoadBMP Error: %s\n", SDL_GetError());	}

	return texture;
}

void Vykresli_hraci_pole (SDL_Renderer *renderer, TTF_Font* Sans, SDL_Texture*Message,SDL_Texture* Score ,SDL_Texture * Score_text, Sources sources, int**array, int R, int C) {

    SDL_Color color = {119, 110, 101};
    SDL_Color color2 = {238, 228, 218};
    SDL_Color color3 = {255, 255, 255};
    Sans = TTF_OpenFontIndex("font/SansBold.ttf", 85, 0);

     if (Sans == NULL) {
        fprintf(stderr, "error: font not found: %s \n", SDL_GetError());
        TTF_Quit();
        exit(EXIT_FAILURE);
    }

    int i=SCORE;
    int delka_score =0;
    if (i == 0){delka_score=1;}
    else{
        while (i != 0){
            delka_score++;
            i/=10;
        }
    }

    char str[10];
    sprintf(str, "%d", SCORE);

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "2048", color);

    SDL_Surface* surfaceScore_text = TTF_RenderText_Solid(Sans, "SCORE", color2);
    SDL_Surface* surfaceScore = TTF_RenderText_Solid(Sans, str, color3);

    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    Score = SDL_CreateTextureFromSurface(renderer, surfaceScore);
    Score_text = SDL_CreateTextureFromSurface(renderer, surfaceScore_text);
    SDL_FreeSurface( surfaceMessage );
    SDL_FreeSurface( surfaceScore);
    SDL_FreeSurface( surfaceScore_text);


    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 110;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 200; // controls the width of the rect
    Message_rect.h = 120; // controls the height of the rect

    SDL_Rect rect;
    rect.x = START_X;
    rect.y = START_Y;
    rect.h = MEZERA + C * (WIDTH+MEZERA);
    rect.w = MEZERA + R * (WIDTH+MEZERA);


    SDL_SetRenderDrawColor(renderer, 238, 228, 218, 255); // Nastavení barvy na zlutou
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
    SDL_RenderFillRect(renderer, &rect);
    rect.x = START_X + MEZERA +2*(WIDTH+MEZERA);
    rect.y = 5;
    rect.h = 100;
    rect.w =  2 * (WIDTH+MEZERA);
    SDL_RenderFillRect(renderer, &rect);

    Message_rect.x = rect.x + MEZERA/2;
    Message_rect.y = rect.y + MEZERA/2;
    Message_rect.w = WIDTH*3/4;
    Message_rect.h = 40;
    SDL_RenderCopy(renderer, Score_text, NULL, &Message_rect);

    Message_rect.x = rect.x +MEZERA + 1.75*WIDTH-20* delka_score;
    Message_rect.y = rect.y + 40;
    Message_rect.w = 20*delka_score; 
    Message_rect.h = 60;
    SDL_RenderCopy(renderer, Score, NULL, &Message_rect);


    rect.h = WIDTH;
    rect.w = rect.h;

    int index;
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){

            int h = array[i][j];

            rect.x = START_X + MEZERA + i*(WIDTH + MEZERA);
            rect.y = START_Y + MEZERA + j*(WIDTH + MEZERA) ;
            if (h == 0){
                index = 0;
            } else {
                index = 1;
                while (h != (1 << index)){
                    index++;
                }
            }

            SDL_RenderCopy(renderer, sources[index], NULL, &rect);
        }
    }
    SDL_DestroyTexture( Message );
    SDL_DestroyTexture( Score );
    SDL_DestroyTexture( Score_text );
    TTF_CloseFont( Sans );
}

void Vykresli_prohru(SDL_Renderer *renderer, TTF_Font* Sans, SDL_Texture*Message){
    SDL_Color color = {119, 110, 101};

    Sans = TTF_OpenFontIndex("font/SansBold.ttf", 85, 0);

     if (Sans == NULL) {
        fprintf(stderr, "error: font not found: %s \n", SDL_GetError());
        TTF_Quit();
        exit(EXIT_FAILURE);
    }
 
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "OH, YOU LOST !!", color);  
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
    SDL_FreeSurface( surfaceMessage ); 

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = START_X+(WIDTH+MEZERA);  //controls the rect's x coordinate 
    Message_rect.y = START_Y+(WIDTH+MEZERA); // controls the rect's y coordinte
    Message_rect.w = 250; // controls the width of the rect
    Message_rect.h = 150; // controls the height of the rect

    SDL_Rect rect;
    rect.x = START_X;
    rect.y = START_Y;
    rect.h = MEZERA + 4 * (WIDTH+MEZERA);
    rect.w = MEZERA + 4 * (WIDTH+MEZERA);

    
    
    SDL_SetRenderDrawColor(renderer, 238, 228, 218, 255);
    SDL_RenderFillRect(renderer, &rect); 
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    
    
    SDL_DestroyTexture( Message );
    TTF_CloseFont( Sans );
}

void Vykresli_vyhru(SDL_Renderer *renderer, TTF_Font* Sans, SDL_Texture*Message){
    SDL_Color color = {255, 255, 255};

    Sans = TTF_OpenFontIndex("font/SansBold.ttf", 85, 0);

     if (Sans == NULL) {
        fprintf(stderr, "error: font not found: %s \n", SDL_GetError());
        TTF_Quit();
        exit(EXIT_FAILURE);
    }
 
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "WOW, YOU WON !!", color);  
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); 
    SDL_FreeSurface( surfaceMessage ); 

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = START_X+(WIDTH+MEZERA);  //controls the rect's x coordinate 
    Message_rect.y = START_Y+(WIDTH+MEZERA); // controls the rect's y coordinte
    Message_rect.w = 300; // controls the width of the rect
    Message_rect.h = 200; // controls the height of the rect
    
    
    SDL_SetRenderDrawColor(renderer, 236, 196, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    
    
    SDL_DestroyTexture( Message );
    TTF_CloseFont( Sans );
}

void Nacti_textury(SDL_Renderer *ren, Sources sources) {
//    SDL_Texture* tex = loadTexture("obr.bmp", renderer);

    sources[0] = loadTexture("sources/obr.bmp", ren);
    sources[1] = loadTexture("sources/2.bmp", ren);
    sources[2] = loadTexture("sources/4.bmp", ren);
    sources[3] = loadTexture("sources/8.bmp", ren);
    sources[4] = loadTexture("sources/16.bmp", ren);
    sources[5] = loadTexture("sources/32.bmp", ren);
    sources[6] = loadTexture("sources/64.bmp", ren);
    sources[7] = loadTexture("sources/128.bmp", ren);
    sources[8] = loadTexture("sources/256.bmp", ren);
    sources[9] = loadTexture("sources/512.bmp", ren);
    sources[10] = loadTexture("sources/1024.bmp", ren);
    sources[11] = loadTexture("sources/2048.bmp", ren);

}

void Uvolni_textury(Sources sources){
    for (int i = 0; i <= 11; i++){
         SDL_DestroyTexture(sources[i]);
    }
}

int main (int argc, char **argv){

    assert(argc == 3);
    // Vykresluje se opacne
    const int C = atoi(argv[1]);
    const int R = atoi(argv[2]);

    int lose = 0;
    int** array;

    array = startGame( R, C, lose);
    int sirka = R*(MEZERA+WIDTH)+ MEZERA+2*START_X;
    int vyska = C*(MEZERA+WIDTH)+ MEZERA+2*START_Y;


    TTF_Init();

    TTF_Font* Sans;

    SDL_Texture* Message;
    SDL_Texture* Score;
    SDL_Texture * Score_text;

    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("2048", 400, 150, sirka, vyska, SDL_WINDOW_SHOWN);
    if (!window) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());

    } else {

      bool quit = false;

      SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (!renderer) {
          SDL_DestroyWindow(window);
          fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
          quit = true;
      }


      Sources sources;

      SDL_Event e;

      Nacti_textury(renderer, sources);

      int change = 1;

      while (!quit)
      {
          while (SDL_PollEvent(&e))
          {
            if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                //User presses a key
                else if( e.type == SDL_KEYDOWN )
                {
                    //Select surfaces based on key press
                    switch( e.key.keysym.sym )
                    {

                        case SDLK_UP:
                        lose = move_left_add(array,R,C);
                        change = 1;
                        break;

                        case SDLK_DOWN:
                        lose = move_right_add(array,R,C);
                        change = 1;
                        break;

                        case SDLK_LEFT:
                        lose = move_up_add(array,R,C);
                        change = 1;
                        break;

                        case SDLK_RIGHT:
                        lose = move_down_add(array,R,C);
                        change = 1;
                        break;

                        case SDLK_x:
                        quit = 1;
                        break;
                    }
                }
            }

          if (change) {
                change = 0;

                Vykresli_hraci_pole(renderer, Sans, Message, Score, Score_text, sources, array, R, C);
                SDL_RenderPresent(renderer);

                if (lose != 0) {
                    if (lose == 1){
                        SDL_Delay(1000);
                        Vykresli_prohru(renderer,Sans, Message);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(5000);
                        quit=true;

                    } else if (lose == 2){
                        SDL_Delay(1000);
                        Vykresli_vyhru(renderer,Sans, Message);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(5000);
                        quit=true;
                    }
                }

          }
      }

      Uvolni_textury(sources);
      SDL_DestroyRenderer(renderer);
    }

    uvolni_pamet(array,R);

    SDL_DestroyWindow(window);
    SDL_Quit();

    TTF_Quit();

    return 0;
}
