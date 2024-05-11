#ifndef PIRE_H
#define PIRE_H

#include "Bocek.h"

typedef struct PIRE Pire;

struct PIRE {
    Bocek base;
    int sayisalDeger; // pire'in sayisalDeger'i
};

Pire* yeni_Pire(int sayisalDeger, int konumX, int konumY);
void piresil(Pire** pire);

#endif
