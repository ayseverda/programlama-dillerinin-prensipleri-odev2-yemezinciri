#ifndef HABITAT_H
#define HABITAT_H

#include "Canli.h"

#define MAX_SUTUN 100

typedef struct {
    Canli*** grid;
    int satir_sayisi;
    int sutun_sayisi;
} Habitat;

Habitat* yeni_Habitat();
void kararAl(Canli* current, Canli* komsu, int satir_sayisi, int sutun_sayisi);
char** veri_matrisi_oku(const char* dosya_ad, int* satir_sayisi, int* sutun_sayisi);
void habitatOlustur(Habitat* habitat, char** matris, int satir_sayisi, int sutun_sayisi);
void sil_Habitat(Habitat* habitat);
void habitatYazdir(Habitat* habitat, int satir_sayisi, int sutun_sayisi);
void adimKararlariniYap(Habitat* habitat, int satir_sayisi, int sutun_sayisi);

#endif /* HABITAT_H */
