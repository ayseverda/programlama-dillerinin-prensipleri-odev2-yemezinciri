#include <stdio.h>
#include "Habitat.h"
#include "Bocek.h"
#include "Canli.h"
#include "Bitki.h"
#include "Sinek.h"
#include "Pire.h"



int main() {
    Habitat* habitat = yeni_Habitat();
    habitatOlustur(habitat, "veri.txt");
	
    habitatYazdir(habitat);

    adimKararlariniYap(habitat);
	printf("adimkararlari uygulandi.");
    
    sil_Habitat(habitat);
	printf("havitat silindi.");
    return 0;
}
