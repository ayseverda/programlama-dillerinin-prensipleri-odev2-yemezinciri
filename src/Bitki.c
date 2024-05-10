#include "Bitki.h"
#include <stdio.h>
#include <stdlib.h>

void bitkiYazdir(Canli* bitki) {
    printf("Bitki: %c\n", bitki->sembol);
}

Bitki* yeni_Bitki(int sayisalDeger, int konumX, int konumY) {
    Bitki* bitki = (Bitki*)malloc(sizeof(Bitki));
    bitki->base = *yeni_Canli('B', sayisalDeger, konumX, konumY);
    bitki->base.yazdir = bitkiYazdir;
    bitki->sayisalDeger = sayisalDeger; // sayisalDeger'i atama
    return bitki;
}

void bitkisil(Bitki** bitki) {
    if (*bitki == NULL) {
        return;
    }

    // İlgili kaynakları serbest bırak
    free(*bitki);
    *bitki = NULL; // Bitki konumuna NULL atama
    printf("Bitki silindi....");
}
