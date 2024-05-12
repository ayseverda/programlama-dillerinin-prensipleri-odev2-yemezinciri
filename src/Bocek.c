#include "Bocek.h"
#include <stdio.h>
#include <stdlib.h>

void bocekYazdir(Canli* bocek) {
    printf("Bocek: %c\n", bocek->sembol);
}

Bocek* yeni_Bocek(int sayisalDeger, int konumX, int konumY) {
    Bocek* bocek = (Bocek*)malloc(sizeof(Bocek));
    bocek->base = *yeni_Canli('C', sayisalDeger, konumX, konumY);
    bocek->base.yazdir = bocekYazdir;
  bocek->sayisalDeger = sayisalDeger; // sayisalDeger'i atama
    return bocek;
}

void boceksil(Bocek** bocek) {
    if (*bocek == NULL) {
        return;
    }

    // İlgili kaynakları serbest bırak
    free(*bocek); // Bocek nesnesini temizle
    *bocek = NULL; // Bocek işaretçisine NULL atama
    printf("Bocek silindi....");
}