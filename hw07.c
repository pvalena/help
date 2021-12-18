#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WIDTH 368
#define HEIGHT 448
#define TEST 0
#define TEST1 0

#define FRAME 15
#define WIDTHDIG 154
#define WIDTHRECT 30
#define HEIGHTDIG 195

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


//pomocne FUNKCE PRO PRISTUP K HODNOTAM V HEADRU
int tgaheader_width( const TGAheader * self ) {
    int width = 0;

    memcpy( &width, self->width, 2 );
    if (TEST) printf("width: %d\n",width);

    return width;
}

int tgaheader_height( const TGAheader * self ) {
    int height = 0;

    memcpy( &height, self->height, 2 );
    if (TEST) printf("height: %d\n",height);

    return height;
}

int tgaheader_channels( const TGAheader * self ) {
    return self->depth / 8;
}

//FCE PRO PRISTUP k hodnotam z headru
int tga_width( const TGAImage * self ) {
    return tgaheader_width( &self->header );
}

int tga_height( const TGAImage * self ) {
    return tgaheader_height( &self->header );
}

int tga_channels( const TGAImage * self ) {
    return  tgaheader_channels( &self->header );
}


//MANIPULATION FUNCTIONS
// 2D array index into 1D array index
int to1D(int row, int col, int cols){
    return col + row * cols;
}

//SET ALL 4 ATRIBUTES OF SINGLE PIXEL
void set_pixel(TGAImage *self, int x, int y, RGBA *pix){
    int width = tga_width(self);
    self->data[to1D(x,y,width)] = *pix; //plocha kopie, jde pac nejsou ukazatel
}




//DRAWING FUNCTIONS
//background ....can set pixels on 0 same way as memset does
void draw_bg(TGAImage *self, RGBA *bg){
    int height = tga_height(self);
    int width = tga_width(self);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            set_pixel(self, i ,j , bg);
            if (TEST) printf("bg: i:%d j:%d\n",i ,j);
        }

    }

}

//MAIN DRAW FUNCTION ..rectangle shape
void draw(TGAImage *self, int x_start, int x_end, int y_start, int y_end, RGBA *pix){
    for (int i = x_start; i < x_end; i++)
    {
        for (int j = y_start; j < y_end; j++)
        {
                set_pixel(self, i, j, pix);
                if (TEST) printf("one: i:%d j:%d\n",i ,j);
        }
    }
}


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



//TASK function 1
void watch_draw_time(TGAImage* self, const int hours, const int minutes){

    FILE *file = fopen("aw.tga","wb");
    assert(file);

    //boil down to single digits
    int firstH = hours / 10;;
    int secondH = hours % 10;
    int firstMin = minutes / 10;
    int secondMin = minutes % 10;

  
    //pixel definition for foreground and background
    RGBA fg = {.red = 100, .green = 10, .blue = 10, .alpha = 255};
    RGBA bg = {.red = 220, .green = 220, .blue = 20, .alpha = 255};
    //popuilated backround color
    draw_bg(self, &bg); 



    //FUNCTION POINTERS ARRAY populated by draw function - indexing corresponds with digits ......(prvni prvek func_array[0] = &draw zero, druhy prvke array[1] = &draw one....)
    void (*func_array[])(TGAImage*, int, int, RGBA*) = {
        draw_zero, draw_one, draw_two, draw_three, draw_foure, draw_five, draw_six, draw_seven, draw_eight, draw_nine
    };


    //function calling based on individual digit (dx, dy prirustky podle toho kera/kde je cislice na ciferniku)
    func_array[firstH](self, 0 , 0, &fg);
    func_array[secondH](self, 0 ,2*FRAME + WIDTHDIG, &fg);
    func_array[firstMin](self, 2*FRAME + HEIGHTDIG, 0, &fg);
    func_array[secondMin](self, 2*FRAME + HEIGHTDIG, 2*FRAME + WIDTHDIG, &fg);  

    //write it all in the file
    int writeCount = fwrite( &self->header, sizeof (TGAheader),1,file); //tady adresu &self->header, pack je to primo clen ("hodnota")
    assert(writeCount == 1);

    writeCount = fwrite(self->data, sizeof(RGBA), tga_width(self) * tga_height(self),file); //tady NE adresu &self primo ten clen je vlastne ukazatel na misto co chci zapisovat 

    fclose(file);
}

//TASK function 2 with pixels parameters
void watch_draw_time_color(TGAImage* self, const int hours, const int minutes, const RGBA* fg_color, const RGBA* bg_color){

    FILE *file = fopen("aw.tga","wb");
    assert(file);

    //boil down to single digits
    int firstH = hours / 10;;
    int secondH = hours % 10;
    int firstMin = minutes / 10;
    int secondMin = minutes % 10;

    //local copies since const param.
    RGBA fgLoc = (*fg_color);
    RGBA bgLoc = (*bg_color);
    
    //popuilated backround color
    draw_bg(self, &bgLoc);


    //FUNCTION POINTERS ARRAY populated by draw function - indexing corresponds with digits ......(prvni prvek func_array[0] = &draw zero, druhy prvke array[1] = &draw one....)
    void (*func_array[])(TGAImage*, int, int, RGBA*) = {
        draw_zero, draw_one, draw_two, draw_three, draw_foure, draw_five, draw_six, draw_seven, draw_eight, draw_nine
    };

    //function calling based on individual digit (dx, dy prirustky podle toho kera/kde je cislice na ciferniku)
    func_array[firstH](self, 0 , 0, &fgLoc);
    func_array[secondH](self, 0 ,2*FRAME + WIDTHDIG, &fgLoc);
    func_array[firstMin](self, 2*FRAME + HEIGHTDIG, 0, &fgLoc);
    func_array[secondMin](self, 2*FRAME + HEIGHTDIG, 2*FRAME + WIDTHDIG, &fgLoc);  //uncomment az bude fungovat

    //write it all in the file
    int writeCount = fwrite( &self->header, sizeof (TGAheader),1,file); //tady adresu &self->header, pack je to primo clen ("hodnota")
    assert(writeCount == 1);

    writeCount = fwrite(self->data, sizeof(RGBA), tga_width(self) * tga_height(self),file); //tady NE adresu &self primo ten clen je vlastne ukazatel na misto co chci zapisovat 

    fclose(file);
}



//function to create new TGA_Image STRUCT
TGAImage *tga_new(const int height, const int width){
    TGAImage *tga = (TGAImage*)malloc(sizeof(TGAImage));// heap allocation for the whole image
 
    //nastavovani hodnot headru
    memset(&tga->header, 0, sizeof(TGAheader)); //vynulovani
    tga->header.image_type = 2;
    tga->header.depth = 32;
    
    //00101000 = 40
    tga->header.descriptor = (1 << 3) | (1 << 5); 


    //zkopirovani hodnot sirky vysky na dva bajty
    memcpy(&tga->header.width, &width, 2 );
    memcpy(&tga->header.height, &height, 2 );

    //ted alokuje pamet pro pixely podle = velikost struct pixel x vyska x sirka
    tga->data = (RGBA*)malloc(sizeof(RGBA) * width * height);

    //nastavime celou alokovanou pamet pro data na 0
    memset(tga->data, 0, sizeof(RGBA) * width * height);

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
    

    //vytvorim strukturu obrazku
    TGAImage *self = tga_new(HEIGHT,WIDTH);

 
    //pixel setting for foreground and background for watch_draw_time_color function
    RGBA bg = {.red = 220, .green = 220, .blue = 200, .alpha = 255};
    RGBA fg = {.red = 250, .green = 10, .blue = 50, .alpha = 255};

    
    watch_draw_time(self,hours, minutes);
    watch_draw_time_color(self, hours, minutes, &fg, &bg);


    tga_free(&self); //fre asi potrebuje adresu self aby z fce mohla prepsat ukazatel self samotny na NULL a vypropagovat zmenu ven z funkce takhle

    return 0;
}
