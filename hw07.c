#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define TEST 0

const int WIDTH = 368;
const int HEIGHT = 448;
const int FRAME = 15;
const int WIDTHDIG = 154;
const int WIDTHRECT = 30;
const int HEIGHTDIG = 195;




typedef unsigned char  byte;

//header representation
typedef struct {
    byte id_length; //0
    byte color_map_type; //32
    byte image_type; //1
    byte color_map[5]; //1
    byte x_origin[2];
    byte y_origin[2];
    byte width[2]; //rozl
    byte height[2]; //rozl
    byte depth; //32
    byte descriptor;

}
TGAheader;

//pixel representation
typedef struct {
    byte blue;
    byte green;
    byte red;
    byte alpha;
} RGBA;

//whole image representation
typedef struct{
    TGAheader header;
    RGBA *data;
}TGAImage;

//jen nekere Deklerace - nedulezite
void watch_draw_time(TGAImage* self, const int hours, const int minutes);
void watch_draw_time_color(TGAImage* self, const int hours, const int minutes, const RGBA* fg_color, const RGBA* bg_color);


//MANIPULATION FUNCTIONS
// 2D array index into 1D array index
int to1D(int row, int col, int cols){
    return col + row * cols;
}

//SET ALL 4 ATRIBUTES OF SINGLE PIXEL
void set_pixel(RGBA *data, int x, int y, const RGBA *pix){
    data[x * WIDTH + y] = *pix; //plocha kopie, jde pac nejsou ukazatel
}



//MAIN DRAW FUNCTION ..rectangle shape
void draw(RGBA *data, int x[2], int y[2], const RGBA *pix){
    for (int i = x[0]; i < x[1]; ++i)
    {
        for (int j = y[0]; j < y[1]; ++j)
        {
                set_pixel(data, i, j, pix);
                if (TEST) printf("one: i:%d j:%d\n",i ,j);
        }
    }
}


/*
//digits combined from rectangles
void draw_zero(TGAImage *self, int dx, int dy, RGBA *pix){
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG, dy +  FRAME, dy + FRAME + WIDTHRECT , pix);  //|..
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHDIG - WIDTHRECT, dy + FRAME + WIDTHDIG , pix); //..|
    draw (self, dx + FRAME, dx + FRAME + WIDTHRECT, dy +  FRAME + WIDTHRECT, dy + FRAME + WIDTHDIG , pix); //-
    draw (self, dx + FRAME +HEIGHTDIG - WIDTHRECT, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHRECT, dy + FRAME + WIDTHDIG , pix); //_

}

void draw_one(TGAImage *self, int dx, int dy, RGBA *pix){
     draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHDIG - WIDTHRECT, dy + FRAME + WIDTHDIG , pix); //..|
}

void draw_two(TGAImage *self, int dx, int dy, RGBA *pix){
    draw (self, dx + FRAME + HEIGHTDIG/2, dx + FRAME + HEIGHTDIG, dy +  FRAME, dy + FRAME + WIDTHRECT , pix);  //|..
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG/2, dy +  FRAME + WIDTHDIG - WIDTHRECT, dy + FRAME + WIDTHDIG , pix); //..|
    draw (self, dx + FRAME  + HEIGHTDIG/2 - WIDTHRECT/2, dx + FRAME  + HEIGHTDIG/2 -WIDTHRECT/2 + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //---
    draw (self, dx + FRAME, dx + FRAME + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //-
    draw (self, dx + FRAME +HEIGHTDIG - WIDTHRECT, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHRECT, dy + FRAME + WIDTHDIG , pix); //_

}

void draw_three(TGAImage *self, int dx, int dy, RGBA *pix){
  
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHDIG - WIDTHRECT, dy + FRAME + WIDTHDIG , pix);
    draw (self, dx + FRAME  + HEIGHTDIG/2 - WIDTHRECT/2, dx + FRAME  + HEIGHTDIG/2 -WIDTHRECT/2 + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //---
    draw (self, dx + FRAME, dx + FRAME + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //-
    draw (self, dx + FRAME +HEIGHTDIG - WIDTHRECT, dx + FRAME + HEIGHTDIG, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //_

}

void draw_foure(TGAImage *self, int dx, int dy, RGBA *pix){
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG/2, dy +  FRAME, dy + FRAME + WIDTHRECT , pix);  //|..
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHDIG - WIDTHRECT, dy + FRAME + WIDTHDIG , pix);//...|
    draw (self, dx + FRAME  + HEIGHTDIG/2 - WIDTHRECT/2, dx + FRAME  + HEIGHTDIG/2 -WIDTHRECT/2 + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //---
}

void draw_five(TGAImage *self, int dx, int dy, RGBA *pix){
  
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG/2, dy +  FRAME, dy + FRAME + WIDTHRECT , pix);  //|..
    draw (self, dx + FRAME + HEIGHTDIG/2, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHDIG - WIDTHRECT, dy + FRAME + WIDTHDIG , pix); //..|
    draw (self, dx + FRAME  + HEIGHTDIG/2 - WIDTHRECT/2, dx + FRAME  + HEIGHTDIG/2 -WIDTHRECT/2 + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //---
    draw (self, dx + FRAME, dx + FRAME + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //-
    draw (self, dx + FRAME +HEIGHTDIG - WIDTHRECT, dx + FRAME + HEIGHTDIG, dy +  FRAME, dy + FRAME + WIDTHDIG , pix); //_
}

void draw_six(TGAImage *self, int dx, int dy, RGBA *pix){
  
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG, dy +  FRAME, dy + FRAME + WIDTHRECT , pix);  //|..
    draw (self, dx + FRAME + HEIGHTDIG/2, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHDIG - WIDTHRECT, dy + FRAME + WIDTHDIG , pix); //..|
    draw (self, dx + FRAME  + HEIGHTDIG/2 - WIDTHRECT/2, dx + FRAME  + HEIGHTDIG/2 -WIDTHRECT/2 + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //---
    draw (self, dx + FRAME, dx + FRAME + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //-
    draw (self, dx + FRAME +HEIGHTDIG - WIDTHRECT, dx + FRAME + HEIGHTDIG, dy +  FRAME, dy + FRAME + WIDTHDIG , pix); //_
}

void draw_seven(TGAImage *self, int dx, int dy, RGBA *pix){
    draw (self, dx + FRAME, dx + FRAME + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //-
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHDIG - WIDTHRECT, dy + FRAME + WIDTHDIG , pix); //..|
}

void draw_eight(TGAImage *self, int dx, int dy, RGBA *pix){

    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG, dy +  FRAME, dy + FRAME + WIDTHRECT , pix);  //|..
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHDIG - WIDTHRECT, dy + FRAME + WIDTHDIG , pix);
    draw (self, dx + FRAME  + HEIGHTDIG/2 - WIDTHRECT/2, dx + FRAME  + HEIGHTDIG/2 -WIDTHRECT/2 + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //---
    draw (self, dx + FRAME, dx + FRAME + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //-
    draw (self, dx + FRAME +HEIGHTDIG - WIDTHRECT, dx + FRAME + HEIGHTDIG, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //_

}

void draw_nine(TGAImage *self, int dx, int dy, RGBA *pix){
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG/2, dy +  FRAME, dy + FRAME + WIDTHRECT , pix);  //|.. 
    draw (self, dx + FRAME, dx + FRAME + HEIGHTDIG, dy +  FRAME + WIDTHDIG - WIDTHRECT, dy + FRAME + WIDTHDIG , pix); //...|
    draw (self, dx + FRAME  + HEIGHTDIG/2 - WIDTHRECT/2, dx + FRAME  + HEIGHTDIG/2 -WIDTHRECT/2 + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //---
    draw (self, dx + FRAME, dx + FRAME + WIDTHRECT, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //-
    draw (self, dx + FRAME +HEIGHTDIG - WIDTHRECT, dx + FRAME + HEIGHTDIG, dy +  FRAME , dy + FRAME + WIDTHDIG , pix); //_

}
*/


//TASK function 1
void watch_draw_time(TGAImage* self, const int hours, const int minutes){

    //pixel definition for foreground and background
    RGBA fg = {.red = 100, .green = 10, .blue = 10, .alpha = 255};
    RGBA bg = {.red = 220, .green = 220, .blue = 20, .alpha = 255};

    watch_draw_time_color(self, hours, minutes, &fg, &bg);
}

//TASK function 2 with pixels parameters
void watch_draw_time_color(TGAImage* self, const int hours, const int minutes, const RGBA* fg_color, const RGBA* bg_color){

    //boil down to single digits
    int firstH = hours / 10;
    int secondH = hours % 10;
    int firstMin = minutes / 10;
    int secondMin = minutes % 10;

    int x[] = {0, HEIGHT};
    int y[] = {0, WIDTH};

    draw(self->data, x, y, bg_color);


    /// TODO:

    //function calling based on individual digit (dx, dy prirustky podle toho kera/kde je cislice na ciferniku)
    /*
    func_array[firstH](self, 0 , 0, fg);
    func_array[secondH](self, 0 ,2*FRAME + WIDTHDIG, fg);
    func_array[firstMin](self, 2*FRAME + HEIGHTDIG, 0, fg);
    func_array[secondMin](self, 2*FRAME + HEIGHTDIG, 2*FRAME + WIDTHDIG, fg);
    */



    //write it all in the file
    FILE *file = fopen("aw.tga","wb");
    assert(file);

    int writeCount = fwrite( &self->header, sizeof (TGAheader), 1, file);
    assert(writeCount == 1);

    writeCount = fwrite(self->data, sizeof(RGBA), WIDTH * HEIGHT, file);
    assert(writeCount == WIDTH * HEIGHT);

    fclose(file);
}



//function to create new TGA_Image STRUCT
TGAImage *tga_new(){
    TGAImage *tga = (TGAImage*)malloc(sizeof(TGAImage));// heap allocation for the whole image

    //nastavovani hodnot headru
    memset(&tga->header, 0, sizeof(TGAheader)); //vynulovani
    tga->header.image_type = 2;
    tga->header.depth = 32;

    //00101000 = 40
    tga->header.descriptor = (1 << 3) | (1 << 5);

    //zkopirovani hodnot sirky vysky na dva bajty
    memcpy(&tga->header.width, &WIDTH, 2 );
    memcpy(&tga->header.height, &HEIGHT, 2 );

    //ted alokuje pamet pro pixely podle = velikost struct pixel x vyska x sirka
    tga->data = (RGBA*)malloc(sizeof(RGBA) * WIDTH * HEIGHT);

    // Toto se nastavi skrze draw:
    //nastavime celou alokovanou pamet pro data na 0
    // memset(tga->data, 0, sizeof(RGBA) * WIDTH * HEIGHT);

    return tga;
}



//FREE all allocated memory
void tga_free(TGAImage **self){

    free((*self)->data);
    (*self)->data = NULL;
    free(*self);
    *self = NULL;
}



int main(int argc, char **argv){
    int hours = 0;
    int minutes = 0;

    if (argc != 3){
        return 1;
    }

    hours = atoi(argv[1]);
    minutes = atoi(argv[2]);

    //pixel setting for foreground and background for watch_draw_time_color function
    RGBA bg = {.red = 220, .green = 220, .blue = 200, .alpha = 255};
    RGBA fg = {.red = 250, .green = 10, .blue = 50, .alpha = 255};

    //vytvorim strukturu obrazku
    TGAImage *self = tga_new();

    watch_draw_time(self, hours, minutes);
    watch_draw_time_color(self, hours, minutes, &fg, &bg);

    tga_free(&self);

    return 0;
}
