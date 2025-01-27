#ifndef PLANSZA_H_IS_INCLUDED_
#define PLANSZA_H_IS_INCLUDED_

typedef struct {
    int **komórki;  // Komórki na planszy (liczba min wokół każdego pola)
    char **widocznosc;  // Widoczność pól: '#' - zakryte, '0'-'8' - liczba min w pobliżu, '*' - mina
    int wiersz;  // Liczba wierszy
    int kolumna;  // Liczba kolumn
    int mina;  // Liczba min
} Plansza;

// Funkcje
void inicjalizuj_plansze(Plansza *plansza, int wiersz, int kolumna, int mina, int sx, int sy);
void drukuj_plansze(const Plansza *plansza);
void odkryj_pole(Plansza *plansza, int x, int y);
void ustaw_flage(Plansza *plansza, int x, int y);
int trafiles_na_mine(const Plansza *plansza, int x, int y);
int sprawdz_wygrana(const Plansza *plansza);
void odkryj_wszystkie_miny(Plansza *plansza);
void zwolnij_plansze(Plansza *plansza);
void ustaw_poziom_trudnosci(Plansza *plansza, int poziom);
int sprawdz_flage(const Plansza *plansza);
#endif
