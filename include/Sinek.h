#ifndef SINEK_H
#define SINEK_H

#include "Bocek.h"

typedef struct SINEK Sinek;

struct SINEK {
    Bocek base;
    int sayisalDeger; // Sinek'in sayisalDeger'i
};

Sinek* yeni_Sinek(int sayisalDeger, int konumX, int konumY);
void sineksil(Sinek** sinek);

#endif
