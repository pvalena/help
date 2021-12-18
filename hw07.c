#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



typedef unsigned char  byte;

//DUlezite aby compilator tam nepridaval mezery, kvuli optimalizaci, ale nam by to zmenilo velikost strukturu
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

typedef struct {
    byte blue;
    byte green;
    byte red;
    byte alpha;
} RGBA;

typedef struct{
    TGAheader header;
    RGBA *data;
}TGAImage;

void watch_draw_time(TGAImage* self, const int hours, const int minutes);
void watch_draw_time_color(TGAImage* self, const int hours, const int minutes, const RGBA* fg_color, const RGBA* bg_color);

//zjistovani/kopirovani hodnoty z headru (z bytu na cislo) a predavani cisla, takze kdykoli si necham zavolat tuhle fci budu li chtit hodnotu, pac kde hodnote se dostanu
//ale je to identifikovano jako unsigned char, proste byte, musi memcpy do integer promene vytvorene (co prima konverze typova??? , hraje roli to ze to je pole v nekterych pripadech??)
int tgaheader_width( const TGAheader * self ) {
    int width = 0;

    memcpy( &width, self->width, 2 );
    printf("width: %d\n",width);

    return width;
}

int tgaheader_height( const TGAheader * self ) {
    int height = 0;

    memcpy( &height, self->height, 2 );
    printf("height: %d\n",height);

    return height;

}

int tgaheader_channels( const TGAheader * self ) {
    return self->depth / 8;
}

//zjistovani hodnot z headru pres fci - asi prehlednejsi
int tga_width( const TGAImage * self ) {
    return tgaheader_width( &self->header );
}

int tga_height( const TGAImage * self ) {
    return tgaheader_height( &self->header );
}

int tga_channels( const TGAImage * self ) {
    return  tgaheader_channels( &self->header );
}


//prevodova fce z 2d souradnic do indexu 1D odpovidajiciho serioveho elementu
int to1D(int row, int col, int cols){
    return col + row * cols;
}


//cokoliv zavola fci se souradnicema x,y bude prevedeno z 2d pole do odpovidajiciho indexu 1d pole jiz nainacializovaneho v *data
//prehodim x, y kdyz pocatek je 0,0 v dolnim levem rohy pokud prehodim x z y tak he to jakobych ho otozil o 90/ prohodil sloupce/radky
void set_pixel(TGAImage *self, int y, int x, RGBA *pix){
    self->data[to1D(x,y, tga_height(self))].alpha = pix->alpha;
    self->data[to1D(x,y, tga_height(self))].blue = pix->blue;
    self->data[to1D(x,y, tga_height(self))].green = pix->green;
    self->data[to1D(x,y, tga_height(self))].red = pix->red;
}

void draw_bg(TGAImage *self, RGBA *bg){
    for (int i = 0; i < tga_height(self); i++)
    {
        for (int j = 0; j < tga_width(self); j++)
        {
            set_pixel(self, i ,j , bg);
            printf("bg: i:%d j:%d\n",i ,j);
        }

    }

}

//pocita indexy nalezejici vykresleni znaku  ty posila do fce ktere zapisuje ty hodnotu do pole clena strukty *data
void draw_one(TGAImage *self, int dx, int dy, RGBA *pix){
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

//nevim jestli tohle muze byt jen v mainu nebo pokuud pouziju typedef nejak na tohle pak to jde takhle
//typedef of array of function pointers (takhle pka func_array je pak data type plus jmesno)
//typedef TGAImage* (*func_array[])(TGAImage *, size_t, size_t, RGBA *);

void watch_draw_time(TGAImage* self, const int hours, const int minutes){

    FILE *file = fopen("aw.tga","wb");
    assert(file);

    int firstH = hours / 10;;
    int secondH = hours % 10;
    int firstMin = minutes / 10;
    int secondMin = minutes % 10;

    RGBA fg = {.red = 30, .green = 10, .blue = 10, .alpha = 255};
//zde musem volat fci s fcnim ukazatel na pole a pdle first/,... hodnot se zavola rovnou dana fce,,nepamatujeu se uz inicializaci atd
//POLE FUNKCNICHU UKAZATELU
    void (*func_array[])(TGAImage*, int, int, RGBA*) = {
        draw_zero, draw_one, /*draw_two, draw_three, draw_foure, draw_five, draw_six, draw seven, draw_eight, draw_nine*/
    };
//jen budu omezovat nebo pricit konec zacatek k ouradnicim(prevod do 1D to pak prepocita na ta mista v celem poli, ktere je uz predpripraveno)
    //draw_one(self,0,0,&fg);
    /*void (*fptr)(TGAImage*, int, int, RGBA*);
    fptr = &draw_one;*/

   /* func_array[firstH](self, 0, 0, &fg);
    func_array[secondH](self, 184, 0, &fg);
    func_array[firstMin](self, 0, 224, &fg);
    func_array[secondMin](self, 184, 224, &fg);*/

    int writeCount = fwrite( &self->header, sizeof (TGAheader),1,file); //velikost prvku je header celej a je jen jeden
    assert(writeCount == 1);

    writeCount = fwrite(&self->data, sizeof(RGBA), tga_width(self) * tga_height(self) * sizeof(RGBA),file);

    fclose(file);
}


//POTREBUJU INIT BRIGHTNESS NENI TO pro cernobile nebo c oto kurva je
TGAImage *tga_new(const int height, const int width){
    TGAImage *tga = (TGAImage*)malloc(sizeof(TGAImage));// na heapu takze to neni jen loklani na stacku
  //  ALLOCTEST( TGAImage );

    memset(&tga->header, 0, sizeof(TGAheader)); //potrebuje adresu ukazatele na novy objekt tga, pac fce to chce
//TADY CHYBI NEKERE HODNOTY
    //tga->header == (*tga).header
    tga->header.image_type = 2;
    tga->header.depth = 32;
    tga->header.descriptor |= 1 << 3;
    tga->header.descriptor |= 1 << 5;


    //zapis rozmeru na dva bytes, prvni vyssii jsou nuly, pak cislo 0-255 zapsane binarne v nizsim bytu
    memcpy(&tga->header.width, &width, 2 );
    memcpy(&tga->header.height, &height, 2 );

    //ted alokuje pamet pro pixely podle = velikost struct pixel x vyska x sirka
    tga->data = (RGBA*)malloc(sizeof(RGBA) * width * height); //data je typu RGBA*
    //nastavime celou alokovanou  pamet pro data
    memset(tga->data, 0, sizeof(RGBA) * width * height); //tga->data uz je ukazatel

    return tga;

}

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
        hours = strtol(argv[1],NULL,10);
        minutes = strtoll(argv[2], NULL, 10);
    }

    //soubor otevru tady nebo muzu presunout do zapisovaci fce?


    //vytvorim strukturu obrazku
    TGAImage *self = tga_new(448,368);

    //bytvorim struktury pixelu kt. priradim urcite hodnoty tak aby vznikly ruzne barvy pozadi a popredi
    RGBA bg = {.red = 220, .green = 220, .blue = 20, .alpha = 255};
    RGBA fg = {.red = 100, .green = 10, .blue = 10, .alpha = 255};

    draw_bg(self, &bg);


    watch_draw_time(self,hours, minutes);


    tga_free(&self); //fre asi potrebuje adresu self aby z fce mohla prepsat ukazatel self samotny na NULL a vypropagovat zmenu ven z funkce takhle

    return 0;
}
