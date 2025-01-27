#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WYNIKOW 100  // Maksymalna liczba wyników w pliku

typedef struct {
    char imie[100];
    int czas_gry;
    int wynik;
} Gracz;

// Funkcja do porównywania dwóch wyników (do sortowania)
int porownaj_wyniki(const void *a, const void *b) {
    Gracz *graczA = (Gracz *)a;
    Gracz *graczB = (Gracz *)b;
    return graczB->wynik - graczA->wynik;  // Sortowanie malejąco po wyniku
}

void zapisz_i_pokaz_wyniki(const char *plik_wynikow, const char *nazwa_gracza, int czas_gry, int liczba_odslonietych_pol, int mnoznik) {
    FILE *plik = fopen(plik_wynikow, "a");
    if (plik == NULL) {
        perror("Nie można otworzyć pliku z wynikami");
        return;
    }

    // Liczenie punktów: liczba odsłoniętych pól * mnożnik
    int wynik = liczba_odslonietych_pol * mnoznik;

    // Zapisz wynik do pliku
    fprintf(plik, "%s %d %d\n", nazwa_gracza, czas_gry, wynik);
    fclose(plik);

    // Wczytaj wyniki do tablicy
    Gracz gracze[MAX_WYNIKOW];
    int liczba_graczy = 0;

    plik = fopen(plik_wynikow, "r");
    if (plik == NULL) {
        perror("Nie można otworzyć pliku z wynikami");
        return;
    }

    // Wczytywanie wyników do tablicy
    while (fscanf(plik, "%s %d %d", gracze[liczba_graczy].imie, &gracze[liczba_graczy].czas_gry, &gracze[liczba_graczy].wynik) != EOF) {
        liczba_graczy++;
    }
    fclose(plik);

    // Sortowanie wyników
    qsort(gracze, liczba_graczy, sizeof(Gracz), porownaj_wyniki);

    // Wyświetl 5 najlepszych graczy
    printf("\nTop 5 Najlepszych Graczy:\n");
    for (int i = 0; i < 5 && i < liczba_graczy; i++) {
        printf("%d. %s - Czas: %d sekund, Wynik: %d\n", i + 1, gracze[i].imie, gracze[i].czas_gry, gracze[i].wynik);
    }
}
