#ifndef HABITAT_H
#define HABITAT_H

#include "Habitat.h"
#include "Canli.h"

#define SATIR_SAYISI 5
#define SUTUN_SAYISI 5


typedef struct Habitat {
    Canli* grid[SATIR_SAYISI][SUTUN_SAYISI];
} Habitat;

Habitat* yeni_Habitat();

void habitatOlustur(Habitat* habitat, const char* dosya_adi);
void habitatYazdir(Habitat* habitat);
void adimKararlariniYap(Habitat* habitat);
void sil_Habitat(Habitat* habitat);

void kararAl(Canli* current, Canli* komsu);

#endif /* HABITAT_H */
