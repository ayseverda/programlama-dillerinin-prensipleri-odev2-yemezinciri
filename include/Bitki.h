#ifndef BITKI_H
#define BITKI_H

#include "Canli.h"

typedef struct BITKI Bitki;

struct BITKI {
    Canli base;
    int sayisalDeger; // Bitki'nin sayisalDeger'i
};

Bitki* yeni_Bitki(int sayisalDeger, int konumX, int konumY);
void bitkisil(Bitki** bitki);

#endif
