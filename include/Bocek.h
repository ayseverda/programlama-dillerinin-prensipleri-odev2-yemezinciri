#ifndef BOCEK_H
#define BOCEK_H

#include "Canli.h"

typedef struct BOCEK Bocek;

struct BOCEK {
    Canli base;
    int sayisalDeger; // Bocek'in sayisalDeger'i
};

Bocek* yeni_Bocek(int sayisalDeger, int konumX, int konumY);
void boceksil(Bocek** bocek);

#endif
