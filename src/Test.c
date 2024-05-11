#include <stdio.h>
#include <stdlib.h> // for free
#include "Habitat.h"
#include "Bocek.h"
#include "Canli.h"
#include "Bitki.h"
#include "Sinek.h"
#include "Pire.h"

int main() {
    int satir_sayisi, sutun_sayisi;
    char** matris = veri_matrisi_oku("veri.txt", &satir_sayisi, &sutun_sayisi);

    Habitat* habitat = yeni_Habitat();
    habitatOlustur(habitat, matris, satir_sayisi, sutun_sayisi);
oyunuBaslat( habitat, satir_sayisi, sutun_sayisi);
    printf("Habitat:\n");
    habitatYazdir(habitat, satir_sayisi, sutun_sayisi);

    printf("\nAdim kararlarini yapiliyor...\n");
	
    adimKararlariniYap(habitat, satir_sayisi, sutun_sayisi);
	
    printf("\nSon durum:\n");
    habitatYazdir(habitat, satir_sayisi, sutun_sayisi);

    // Habitat ve matris için ayrılan belleği serbest bırak
    sil_Habitat(habitat);
    for (int i = 0; i < satir_sayisi; i++) {
        free(matris[i]);
    }
    free(matris);

    return 0;
}
