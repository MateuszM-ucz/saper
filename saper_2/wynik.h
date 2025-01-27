#ifndef WYNIK_H_IS_INCLUDED_
#define WYNIK_H_IS_INCLUDED_

#define MAX_GRACZY 100  //maksymalna liczba wyników w systemie
#define NAZWA_GRACZA_MAX 50  //maksymalna długość nazwy gracza

typedef struct {
    char nazwa[NAZWA_GRACZA_MAX];  //imię gracza
    int czas;  //czas w sekundach
} Wynik;

// Funkcje
int porownaj_wyniki(const void *a, const void *b);
void zapisz_i_pokaz_wyniki(const char *plik_wynikow, const char *nazwa_gracza, int czas_gry, int liczba_odslonietych_pol, int mnoznik);
#endif
