
int ** naalokuj_pamet(int R, int C);
void * uvolni_pamet(int ** arr_aloc, int R);
int vygeneruj_cislo();
int ** make_control_array(int**array, int R, int C);
int vygeneruj_pozici(int pocet_volnych);
void win(int**array, int win, int i, int j);
int count_zeros(int ** array, int R, int C);
int move_left(int ** array, int R, int C);
int move_right(int ** array, int R, int C);
int move_up(int ** array, int R, int C);
int move_down(int ** array, int R, int C);
void is_Lost(int**array, int R, int C, int lose);
void add_Num(int** array, int R, int C, int lose);
void move_left_add(int ** array, int R, int C, int lose);
void move_right_add(int ** array, int R, int C, int lose);
void move_up_add(int ** array, int R, int C, int lose);
void move_down_add(int ** array, int R, int C, int lose);






