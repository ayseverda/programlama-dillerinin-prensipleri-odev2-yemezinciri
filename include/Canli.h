#ifndef CANLI_H
#define CANLI_H

typedef struct CANLI Canli;

struct CANLI {
    char sembol;
    int sayisalDeger;
    int konumX;
    int konumY;

    void (*yazdir)(Canli*);
	
};

Canli* yeni_Canli(char sembol, int sayisalDeger, int konumX, int konumY);
void sil_Canli(Canli* canli);

#endif
