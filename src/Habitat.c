#include "Habitat.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Bitki.h"
#include "Bocek.h"
#include "Sinek.h"
#include "Pire.h"
#include <string.h>

Habitat* yeni_Habitat() {
    srand(time(NULL));
    Habitat* habitat = (Habitat*)malloc(sizeof(Habitat));
    return habitat;
}





char** veri_matrisi_oku(const char* dosya_ad, int* satir_sayisi, int* sutun_sayisi) {
    FILE* dosya = fopen(dosya_ad, "r");
    if (dosya == NULL) {
        perror("Dosya açma hatasi");
        exit(EXIT_FAILURE);
    }

    // Satır ve sütun sayısını belirlemek için ilk okuma
    *satir_sayisi = 0;
    *sutun_sayisi = 0;
    int maksimum_sutun_sayisi = 0; // En fazla sütun sayısını tutmak için bir değişken ekleyelim
    char satir[MAX_SUTUN]; // Bir satırın en fazla MAX_SUTUN karakter olmasını varsayalım

    // Dosyayı okuyarak satır ve sütun sayısını belirle
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        (*satir_sayisi)++;
        int gecici_sutun_sayisi = 0;
        char* token = strtok(satir, " \t\n"); // Boşluk, tab ve newline karakterlerine göre ayır
        while (token != NULL) {
            gecici_sutun_sayisi++;
            token = strtok(NULL, " \t\n");
        }
        if (gecici_sutun_sayisi > maksimum_sutun_sayisi) {
            maksimum_sutun_sayisi = gecici_sutun_sayisi;
        }
    }
    *sutun_sayisi = maksimum_sutun_sayisi;

    // Bellekte matris için yer ayır
    char** matris = (char**)malloc(*satir_sayisi * sizeof(char*));
    if (matris == NULL) {
        perror("Bellek hatasi");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < *satir_sayisi; i++) {
        matris[i] = (char*)malloc(*sutun_sayisi * sizeof(char)); // char olarak değiştir
        if (matris[i] == NULL) {
            perror("Bellek hatasi");
            exit(EXIT_FAILURE);
        }
    }

    // Dosyayı tekrar oku ve matrise aktar
    rewind(dosya);
    int satir_indeks = 0;
    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        int sutun_indeks = 0;
        char* token = strtok(satir, " \t\n"); // Boşluk, tab ve newline karakterlerine göre ayır
        while (token != NULL && sutun_indeks < *sutun_sayisi) { // Sütun sayısını aşmamak için kontrol ekle
            matris[satir_indeks][sutun_indeks] = atoi(token); // Stringi integer'a dönüştür
            token = strtok(NULL, " \t\n");
            sutun_indeks++;
        }
        satir_indeks++;
    }

    fclose(dosya);
    return matris;
}

void sil_matris(char** matris, int satir_sayisi) {
    if (matris == NULL) {
        return;
    }
    for (int i = 0; i < satir_sayisi; i++) {
        free(matris[i]);
    }
    free(matris);
}


void habitatOlustur(Habitat* habitat, char** matris, int satir_sayisi, int sutun_sayisi) {
    habitat->satir_sayisi = satir_sayisi;
    habitat->sutun_sayisi = sutun_sayisi;
    habitat->grid = (Canli***)malloc(satir_sayisi * sizeof(Canli**));
    if (habitat->grid == NULL) {
        perror("Bellek hatasi");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < satir_sayisi; i++) {
        habitat->grid[i] = (Canli**)malloc(sutun_sayisi * sizeof(Canli*));
        if (habitat->grid[i] == NULL) {
            perror("Bellek hatasi");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < sutun_sayisi; j++) {
            habitat->grid[i][j] = NULL; // Başlangıçta tüm hücreleri NULL olarak ayarlayalım
        }
    }

    for (int i = 0; i < satir_sayisi; i++) {
        for (int j = 0; j < sutun_sayisi; j++) {
            int sayi = matris[i][j];
            Canli* canli = NULL;

            if (sayi >= 1 && sayi <= 9) {
                canli = (Canli*)yeni_Bitki(sayi, i, j);
            } else if (sayi >= 10 && sayi <= 20) {
                canli = (Canli*)yeni_Bocek(sayi, i, j);
            } else if (sayi >= 21 && sayi <= 50) {
                canli = (Canli*)yeni_Sinek(sayi, i, j);
            } else if (sayi >= 51 && sayi <= 99) {
                canli = (Canli*)yeni_Pire(sayi, i, j);
            }

            habitat->grid[i][j] = canli;
        }
    }
}


void sil_Habitat(Habitat* habitat) {
    if (habitat == NULL) {
        return;
    }
    // grid içindeki tüm hücrelerin belleğini serbest bırak
    for (int i = 0; i < habitat->satir_sayisi; i++) {
        for (int j = 0; j < habitat->sutun_sayisi; j++) {
            sil_Canli(habitat->grid[i][j]); // Her Canli nesnesi için belleği serbest bırak
        }
        free(habitat->grid[i]);
    }
    free(habitat->grid);
    free(habitat);
}



void habitatYazdir(Habitat* habitat, int satir_sayisi, int sutun_sayisi) {
    for (int i = 0; i < satir_sayisi; i++) {
        for (int j = 0; j < sutun_sayisi; j++) {
            printf("%c ", habitat->grid[i][j]->sembol);
        }
        printf("\n");
    }
}


void adimKararlariniYap(Habitat* habitat, int satir_sayisi, int sutun_sayisi) {
    // current hücresi 0,0'dan başlayacak
    int nextRow = 0;
    int kalan_canli_sayisi = 0; // Kalan canlı sayısını takip etmek için bir değişken
    for (int i = 0; i < satir_sayisi; i++) {
        // Her bir sütun için döngü
        for (int j = 0; j < sutun_sayisi; j++) {
            // current hücresini al (0,0'dan başlar)
            Canli* current = habitat->grid[0][0];
            
            // Eğer current null ise veya sembolü 'X' ise, null olmayan ve 'X' sembolü taşımayan ilk hücreyi bul
            if (current == NULL || current->sembol == 'X') {
                int row = 0;
                int column = 0;
                while (habitat->grid[row][column] == NULL || habitat->grid[row][column]->sembol == 'X') {
                    column++;
					
                    if (column >= sutun_sayisi) {
                        row++;
                        if (row >= satir_sayisi) {
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
            if (nextColumn >= sutun_sayisi) {
				 nextRow++; 
                nextColumn = 0; // Sütun indeksini sıfırla
                    // Bir sonraki satıra geç
            }
                // Satır indeksi kontrol et, eğer satır sonuna gelindi ise sıfırla
                if (nextRow >= satir_sayisi && nextColumn == sutun_sayisi ) {
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
            habitatYazdir(habitat, satir_sayisi, sutun_sayisi);
            //system("cls");
            // Her adımda kalan canlı sayısını kontrol et
            kalan_canli_sayisi = 0;
            for (int m = 0; m < satir_sayisi; m++) {
                for (int n = 0; n < sutun_sayisi; n++) {
                    if (habitat->grid[m][n] != NULL && habitat->grid[m][n]->sembol != 'X') {
                        kalan_canli_sayisi++;
                    }
                }
            }
            
            // Eğer sadece bir canlı kaldıysa, döngülerden çık
            if (kalan_canli_sayisi <= 1) {
                goto cikis; // Döngülerden çıkmak için etiketli bir atama (goto) kullanıyoruz
            }
        }
    }
    
    // Döngülerden çıkmak için kullanılan etiket
    cikis:
    
    // Son kalan canlıyı bul ve sembolünü ekrana yazdır
    for (int i = 0; i < satir_sayisi; i++) {
        for (int j = 0; j < sutun_sayisi; j++) {
            if (habitat->grid[i][j] != NULL && habitat->grid[i][j]->sembol != 'X') {
                printf("Son kalan canli: %c\n", habitat->grid[i][j]->sembol);
				 printf("Son kalan canlinin konumu: (%d, %d)\n", i, j);
                return;
            }
        }
    }
    printf("Hic canli kalmadi.\n");
}


		
		
	void kararAl(Canli* current, Canli* komsu) {
    // İki canlının türüne göre işlem yap
    
        if (current->sembol == 'B' && komsu->sembol == 'P') { 
		
            piresil((Pire**)&komsu);
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
			printf("kararal");
            piresil((Pire**)&komsu);
			printf("kararakindi");
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
            piresil((Pire**)&current);
			current->sembol = 'X';
        } else if (current->sembol == 'P' && komsu->sembol == 'S') {
            piresil((Pire**)&current);
		current->sembol = 'X';}
		else if (current->sembol == 'P' && komsu->sembol == 'B') {
            piresil((Pire**)&current);
			current->sembol = 'X';
			
			
        } else if (current->sembol == 'P' && komsu->sembol == 'P') {
            if (((Pire*)current)->sayisalDeger > ((Pire*)komsu)->sayisalDeger) {
                piresil((Pire**)&komsu);
				komsu->sembol = 'X';
            } else {
                piresil((Pire**)&current);
				current->sembol= 'X';
            }
        } else if (current->sembol == 'S' && komsu->sembol == 'P') {
            piresil((Pire**)&komsu);
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
