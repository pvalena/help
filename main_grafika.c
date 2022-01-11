#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

const int MEZERA = 15;
const int WIDTH = 106;
const int HEIGHT = WIDTH;
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

void Vykresli_hraci_pole (SDL_Renderer *renderer, Sources sources,int R, int C) {

    SDL_Rect rect;
    rect.x = 250;
    rect.y = 250;
    rect.h = MEZERA + 4 * (WIDTH+MEZERA);
    rect.w = MEZERA + 4 * (WIDTH+MEZERA);

    SDL_SetRenderDrawColor(renderer, 187, 173, 160, 255);
    SDL_RenderFillRect(renderer, &rect);


    rect.h = WIDTH;
    rect.w = rect.h;

    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){

            rect.x = 265 + i*(WIDTH + MEZERA);
            rect.y = 265 + j*(WIDTH + MEZERA) ;

            SDL_RenderCopy(renderer, sources[0], NULL, &rect);
        }
    }

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
    sources[9] = loadTexture("sources/512bmp", ren);
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
    const int R = atoi(argv[1]);
    const int C = atoi(argv[2]);


    TTF_Init();

    TTF_Font* Sans;
    Sans = TTF_OpenFontIndex("font/sans.ttf", 25, 0);

     if (Sans == NULL) {
        fprintf(stderr, "error: font not found: %s \n", SDL_GetError());
        TTF_Quit();
        exit(EXIT_FAILURE);
    }

    if (SDL_Init(SDL_INIT_VIDEO)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("2048", 400, 150, 1000, 800, SDL_WINDOW_SHOWN);
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

      SDL_Color color = {255, 255, 0};

      SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "2048", color); 

      SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
      SDL_FreeSurface( surfaceMessage );


      SDL_Rect Message_rect; //create a rect
      Message_rect.x = 5;  //controls the rect's x coordinate 
      Message_rect.y = 5; // controls the rect's y coordinte
      Message_rect.w = 100; // controls the width of the rect
      Message_rect.h = 100; // controls the height of the rect


      Sources sources;

      SDL_Event e;

      Nacti_textury(renderer, sources);

      while (!quit)
      {
          while (SDL_PollEvent(&e))
          {
              if (e.type == SDL_QUIT)
              {
                  quit = true;
              }
          }
          SDL_SetRenderDrawColor(renderer, 250, 248, 239, 255); // Nastavení barvy na zlutou
          SDL_RenderClear(renderer);                      // Vykreslení pozadí
          //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
          SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

          Vykresli_hraci_pole(renderer, sources, R, C);

          SDL_RenderPresent(renderer);  // Prezentace kreslítka
      }

      Uvolni_textury(sources);

      SDL_DestroyTexture( Message );
      SDL_DestroyRenderer(renderer);

    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    TTF_CloseFont( Sans );
    TTF_Quit();

    return 0;
}
