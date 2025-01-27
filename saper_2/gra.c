#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "plansza.h"
#include "wynik.h"

void gra() {
    int wiersz, kolumna, mina, poziom;
    Plansza plansza;
    char nazwa_gracza[100];
    int czas_gry = 0;  // Czas gry w sekundach
    int liczba_odslonietych_pol = 0;
    int mnoznik = 1;  // Domyślnie łatwy poziom

    // Wybór poziomu trudności
    printf("Wybierz poziom trudnosci:\n");
    printf("1 - Latwy (9x9, 10 min)\n");
    printf("2 - Sredni (16x16, 40 min)\n");
    printf("3 - Trudny (16x30, 99 min)\n");
    printf("4 - Wlasny poziom\n");
    printf("Podaj numer poziomu: ");
    scanf("%d", &poziom);
    
    // Ustawienia dla poziomu trudności
    if (poziom == 1) {
        mnoznik = 1;  // Łatwy
    } else if (poziom == 2) {
        mnoznik = 2;  // Średni
    } else if (poziom == 3) {
        mnoznik = 3;  // Trudny
    } else if (poziom == 4) {
        // Własne ustawienia
        printf("Podaj liczbe wierszy: ");
        scanf("%d", &wiersz);
        printf("Podaj liczbe kolumn: ");
        scanf("%d", &kolumna);
        printf("Podaj liczbe min: ");
        scanf("%d", &mina);
    }

    // Inicjalizacja planszy
    ustaw_poziom_trudnosci(&plansza, poziom);
    if (poziom == 4) {
        inicjalizuj_plansze(&plansza, wiersz, kolumna, mina, -1, -1);
    }

    printf("Rozpoczynamy gre!\n");
    drukuj_plansze(&plansza);

    // Startujemy pomiar czasu
    time_t start_time = time(NULL);

    // Główna pętla gry
    while (1) {
        char komenda;
        int x, y;
        printf("Podaj komende (r - odsloniecie, f - flaga): ");
        while(scanf(" %c %d %d", &komenda, &x, &y) != 3) {
            printf("Blad: Nie podano dwoch liczb. Sprobuj ponownie.\n");
        }

        if (komenda == 'r') {
            if (trafiles_na_mine(&plansza, x, y)) {
                odkryj_wszystkie_miny(&plansza);
                drukuj_plansze(&plansza);
                printf("Niestety, trafiles na mine! Game over.\n");
                // Zapytanie o imię gracza
                printf("Podaj imie gracza: ");
                scanf("%s", nazwa_gracza);

                // Zapisz wynik i wyświetl najlepsze
                zapisz_i_pokaz_wyniki("wyniki.txt", nazwa_gracza, czas_gry, liczba_odslonietych_pol, mnoznik);
                break;
            }
            odkryj_pole(&plansza, x, y);
            liczba_odslonietych_pol++;  // Zwiększamy liczbę odsłoniętych pól
        } else if (komenda == 'f') {
            ustaw_flage(&plansza, x, y);
        }

        drukuj_plansze(&plansza);

        if (sprawdz_wygrana(&plansza)) {
            // Zatrzymujemy pomiar czasu
            czas_gry = (int)(time(NULL) - start_time);

            printf("Gratulacje, wygrana!\n");

            // Zapytanie o imię gracza
            printf("Podaj imie gracza: ");
            scanf("%s", nazwa_gracza);

            // Zapisz wynik i wyświetl najlepsze
            zapisz_i_pokaz_wyniki("wyniki.txt", nazwa_gracza, czas_gry, liczba_odslonietych_pol, mnoznik);
            break;
        }
    }

    // Zwolnienie pamięci
    zwolnij_plansze(&plansza);
}
