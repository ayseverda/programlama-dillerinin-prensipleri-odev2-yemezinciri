#include "Pire.h"
#include <stdio.h>
#include <stdlib.h>

void pireYazdir(Canli* pire) {
    printf("Pire: %c\n", pire->sembol);
}


Pire* yeni_Pire(int sayisalDeger, int konumX, int konumY) {
    Pire* pire = (Pire*)malloc(sizeof(Pire));
    pire->base = *yeni_Bocek(sayisalDeger, konumX, konumY);
    pire->base.base.yazdir = pireYazdir;
    pire->base.base.sembol = 'P'; // Pire sembolünü 'P' olarak ayarla
pire->sayisalDeger = sayisalDeger; // sayisalDeger'i atama
    return pire;
}


void piresil(Pire** pire) {
    if (*pire == NULL) {
        return;
    }

    // İlgili kaynakları serbest bırak
    free(*pire);
    *pire = NULL; // Pire konumuna NULL atama
    printf("Pire silindi....");
}

