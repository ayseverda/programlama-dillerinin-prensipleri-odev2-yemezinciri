#include "Sinek.h"
#include <stdio.h>
#include <stdlib.h>

void sinekYazdir(Canli* sinek) {
    printf("Sinek: %c\n", sinek->sembol);
}

Sinek* yeni_Sinek(int sayisalDeger, int konumX, int konumY) {
    Sinek* sinek = (Sinek*)malloc(sizeof(Sinek));
    sinek->base = *yeni_Bocek(sayisalDeger, konumX, konumY);
    sinek->base.base.yazdir = sinekYazdir;
    sinek->base.base.sembol = 'S'; // Sinek sembolünü 'S' olarak ayarla
  sinek->sayisalDeger = sayisalDeger; // sayisalDeger'i atama
    return sinek;
}
void sineksil(Sinek** sinek) {
    if (*sinek == NULL) {
        return;
    }

    // İlgili kaynakları serbest bırak
    free(*sinek);
    *sinek = NULL; // Sinek konumuna NULL atama
    printf("Sinek silindi....");
}