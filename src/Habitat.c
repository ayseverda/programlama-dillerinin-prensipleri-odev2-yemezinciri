#include "Habitat.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Bitki.h"
#include "Bocek.h"
#include "Sinek.h"
#include "Pire.h"



Habitat* yeni_Habitat() {
    srand(time(NULL));
    Habitat* habitat = (Habitat*)malloc(sizeof(Habitat));
    return habitat;
}

void habitatOlustur(Habitat* habitat, const char* dosya_adi) {
    FILE* dosya = fopen(dosya_adi, "r");
    if (dosya == NULL) {
        printf("Dosya acilamadi.");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < SATIR_SAYISI; i++) {
        for (int j = 0; j < SUTUN_SAYISI; j++) {
            int sayi;
            fscanf(dosya, "%d", &sayi);
            Canli* canli;

            if (sayi >= 1 && sayi <= 9) {
                canli = (Canli*)yeni_Bitki(sayi, i, j);
            } else if (sayi >= 10 && sayi <= 20) {
                canli = (Canli*)yeni_Bocek(sayi, i, j);
            } else if (sayi >= 21 && sayi <= 50) {
                canli = (Canli*)yeni_Sinek(sayi, i, j);
            } else {
                canli = (Canli*)yeni_Pire(sayi, i, j);
            }

            habitat->grid[i][j] = canli;
        }
    }

    fclose(dosya);
}

void sil_Habitat(Habitat* habitat) {
    for (int i = 0; i < SATIR_SAYISI; i++) {
        for (int j = 0; j < SUTUN_SAYISI; j++) {
            sil_Canli(habitat->grid[i][j]);
        }
    }
    free(habitat);
}

void habitatYazdir(Habitat* habitat) {
    for (int i = 0; i < SATIR_SAYISI; i++) {
        for (int j = 0; j < SUTUN_SAYISI; j++) {
            printf("%c ", habitat->grid[i][j]->sembol);
        }
        printf("\n");
    }
}
void adimKararlariniYap(Habitat* habitat) {
    // Her bir satır için döngü
    int nextRow = 0; // nextRow'u döngülerin dışında tanımlayalım
    for (int i = 0; i < SATIR_SAYISI; i++) {
        // Her bir sütun için döngü
        for (int j = 0; j < SUTUN_SAYISI; j++) {
            // current hücresini al (0,0'dan başlar)
            Canli* current = habitat->grid[0][0];
            // Eğer current null ise veya sembolü 'X' ise, null olmayan ve 'X' sembolü taşımayan ilk hücreyi bul
            if (current == NULL || current->sembol == 'X') {
                int row = 0;
                int column = 0;
                while (habitat->grid[row][column] == NULL || habitat->grid[row][column]->sembol == 'X') {
                    column++;
					
                    if (column >= SUTUN_SAYISI) {
                        row++;
                        if (row >= SATIR_SAYISI) {
                            break;						// Hücre bulunamadı, döngüden çık
                        }
                        column = 0; // Satır değiştiği için sütun indeksini sıfırla
						
						// Satır değiştiğinde nextRow değerini de güncelle
						//nextRow = row;
                    }              
                }
				current = habitat->grid[row][column];
            }
            // komsu hücresini belirle (0,1'den başlar)
            Canli* komsu = NULL;
            int nextColumn = j + 1;
            if (nextColumn >= SUTUN_SAYISI) {
				 nextRow++; 
                nextColumn = 0; // Sütun indeksini sıfırla
                    // Bir sonraki satıra geç
            }
                // Satır indeksi kontrol et, eğer satır sonuna gelindi ise sıfırla
                if (nextRow >= SATIR_SAYISI && nextColumn == SUTUN_SAYISI ) {
                   break;
                }         
            // komsu hücresini belirle
            komsu = habitat->grid[nextRow][nextColumn];
            printf("Current: (%d, %d)\n", current->konumX, current->konumY);
            printf("komsu: (%d, %d)\n", komsu->konumX, komsu->konumY);
            // Ardından, current ve komsu değişkenlerini kullanarak kararları yapabiliriz
            kararAl(current, komsu);
            // Habitatı güncelle
			printf("\n");
            habitatYazdir(habitat);
        }
    }
}



//bitki pire sinek böcek
void kararAl(Canli* current, Canli* komsu) {
    // İki canlının türüne göre işlem yap
    
        if (current->sembol == 'B' && komsu->sembol == 'P') { 
		
            piresil((Pire**)komsu);
		komsu->sembol = 'X';}
 
		else if (current->sembol == 'B' && komsu->sembol == 'C') {
            bitkisil((Bitki**)current);
		current->sembol = 'X';}
        
		else if (current->sembol == 'B' && komsu->sembol == 'S') {
            sineksil((Sinek**)komsu);
		komsu->sembol = 'X';}
		
		
		
		
        else if (current->sembol == 'B' && komsu->sembol == 'B') {
        
			if (((Bitki*)current)->sayisalDeger > ((Bitki*)komsu)->sayisalDeger) {

				bitkisil((Bitki**)komsu);
				komsu->sembol = 'X';
				
            } else {
			

                bitkisil((Bitki**)current);
				current->sembol = 'X';
				
            }
		} 
		
		
		
		else if (current->sembol == 'C' && komsu->sembol == 'B') {
            bitkisil((Bitki**)komsu);
		komsu->sembol = 'X';}
			else if (current->sembol == 'C' && komsu->sembol == 'S') {
            boceksil((Bocek**)current);
			current->sembol = 'X';
			
        } else if (current->sembol == 'C' && komsu->sembol == 'P') {
            piresil((Pire**)komsu);
			komsu->sembol = 'X';
        } else if (current->sembol == 'C' && komsu->sembol == 'C') {
            if (((Bocek*)current)->sayisalDeger > ((Bocek*)komsu)->sayisalDeger) {
                boceksil((Bocek**)komsu);
				komsu->sembol = 'X';
            } else {
                boceksil((Bocek**)current);
				current->sembol = 'X';
            }
        } else if (current->sembol == 'P' && komsu->sembol == 'C') {
            piresil((Pire**)current);
			current->sembol = 'X';
        } else if (current->sembol == 'P' && komsu->sembol == 'S') {
            piresil((Pire**)current);
		current->sembol = 'X';}
		else if (current->sembol == 'P' && komsu->sembol == 'B') {
            piresil((Pire**)current);
			current->sembol = 'X';
			
			
        } else if (current->sembol == 'P' && komsu->sembol == 'P') {
            if (((Pire*)current)->sayisalDeger > ((Pire*)komsu)->sayisalDeger) {
                piresil((Pire**)komsu);
				komsu->sembol = 'X';
            } else {
                piresil((Pire**)current);
				current->sembol= 'X';
            }
        } else if (current->sembol == 'S' && komsu->sembol == 'P') {
            piresil((Pire**)komsu);
			komsu->sembol = 'X';
        } else if (current->sembol == 'S' && komsu->sembol == 'C') {
            boceksil((Bocek**)komsu);
			komsu->sembol = 'X';
        } else if (current->sembol == 'S' && komsu->sembol == 'B') {
            sineksil((Sinek**)current);
			current->sembol = 'X';
        } else if (current->sembol == 'S' && komsu->sembol == 'S') {
            if (((Sinek*)current)->sayisalDeger > ((Sinek*)komsu)->sayisalDeger) {
                sineksil((Sinek**)current);
				current->sembol = 'X';
            } else {
                sineksil((Sinek**)komsu);
				komsu->sembol = 'X';
            }
        }
    }
