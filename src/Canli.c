#include "Canli.h"
#include <stdio.h>
#include <stdlib.h>

Canli* yeni_Canli(char sembol, int sayisalDeger, int konumX, int konumY) {
    Canli* canli = (Canli*)malloc(sizeof(Canli));
    canli->sembol = sembol;
    canli->sayisalDeger = sayisalDeger;
    canli->konumX = konumX;
    canli->konumY = konumY;

    return canli;
}

void sil_Canli(Canli* canli) {
    free(canli);
}
