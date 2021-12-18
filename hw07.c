#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define WIDTH 368
#define HEIGHT 448
#define TEST 0


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
    int height = tga_height(self);
    self->data[to1D(y,x,height)] = *pix; //plocha kopie, jde pac nejsou ukazatel

    /*self->data[to1D(y,x, tga_height(self))].alpha = pix->alpha;
    self->data[to1D(y,x, tga_height(self))].blue = pix->blue;
    self->data[to1D(y,x, tga_height(self))].green = pix->green;
    self->data[to1D(y,x, tga_height(self))].red = pix->red;*/
}




//DRAWING FUNCTIONS
//background
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

//digits
void draw_one(TGAImage *self, int dx, int dy, RGBA *pix){
    for (int i = 0 + dx; i < 195 + dx; i++)
    {
        for (int j = 0 + dx; j < 169 + dy; j++)
        {
            if (i > 15 + dx && j > 139 + dy)
            {
                set_pixel(self, i, j, pix);
                if (TEST) printf("one: i:%d j:%d\n",i ,j);
            }
        }
    }
}

//zatim dela to stejne co draw_one ()
void draw_zero(TGAImage *self, int dx, int dy, RGBA *pix){
    for (int i = 0 + dx; i < 195 + dx; i++)
    {
        for (int j = 0 + dx; j < 169 + dy; j++)
        {
            if (i > 15 + dx && j > 139 + dy)
            {
                set_pixel(self, i, j, pix);
                printf("one: i:%d j:%d\n",i ,j);
            }
        }
    }
}


//TASK functions
void watch_draw_time(TGAImage* self, const int hours, const int minutes){

    FILE *file = fopen("aw.tga","wb");
    assert(file);

    //boil down to single digits
    int firstH = hours / 10;;
    int secondH = hours % 10;
    int firstMin = minutes / 10;
    int secondMin = minutes % 10;

    //pixel definition for foreground
    RGBA fg = {.red = 30, .green = 10, .blue = 10, .alpha = 255};
    //set_pixel(self,0,0,&fg);

    //FUNCTION POINTERS ARRAY (prvni prvek func_array[0] = &draw zero, druhy prvke array[1] = &draw one....)
    void (*func_array[])(TGAImage*, int, int, RGBA*) = {
        draw_zero, draw_one, /*draw_two, draw_three, draw_foure, draw_five, draw_six, draw seven, draw_eight, draw_nine*/
    };


    //function calling based on individual digit (dx, dy prirustky podle toho kera/kde je cislice na ciferniku)
   /* func_array[firstH](self, 0, 0, &fg);
    func_array[secondH](self, 184, 0, &fg);
    func_array[firstMin](self, 0, 224, &fg);
    func_array[secondMin](self, 184, 224, &fg);  uncomment az bude fungovat*/

    //write it all in the file
    int writeCount = fwrite( &self->header, sizeof (TGAheader),1,file); //velikost prvku je header celej a je jen jeden
    assert(writeCount == 1);

    writeCount = fwrite(&self->data, sizeof(RGBA), tga_width(self) * tga_height(self),file);

    fclose(file);
}


//tady vytvarim vlastni struktury a nastavuju jejich hodnoty > PRAVDEPODOBNE PROBLE ZDE NEKDE
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

    if (argc != 3)
    {
        return 1;
    }
    else
    {
        hours = atoi(argv[1]);
        minutes = atoi(argv[2]);
    }

    

    //vytvorim strukturu obrazku
    TGAImage *self = tga_new(HEIGHT,WIDTH);

 
    //pixel setting for foreground and background
    RGBA bg = {.red = 220, .green = 220, .blue = 20, .alpha = 255};
    RGBA fg = {.red = 100, .green = 10, .blue = 10, .alpha = 255};

    
    draw_bg(self, &bg);


    watch_draw_time(self,hours, minutes);


    tga_free(&self); //fre asi potrebuje adresu self aby z fce mohla prepsat ukazatel self samotny na NULL a vypropagovat zmenu ven z funkce takhle

    return 0;
}
