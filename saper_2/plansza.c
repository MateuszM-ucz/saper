#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "plansza.h"

void inicjalizuj_plansze(Plansza *plansza, int wiersz, int kolumna, int mina, int sx, int sy){
    plansza->wiersz = wiersz;
    plansza->kolumna = kolumna;
    plansza->mina = mina;

    // Alokacja pamięci dla planszy
    plansza->komorki = malloc(wiersz * sizeof(int *));
    plansza->widocznosc = malloc(wiersz * sizeof(char *));
    for(int i=0; i<wiersz; i++){
        plansza->komorki[i] = calloc(kolumna, sizeof(int));
        plansza->widocznosc[i] = malloc(kolumna);
        for(int j=0; j<kolumna; j++){
            plansza->widocznosc[i][j] = '#';
        }
    }

    // Rozmieszczenie min
    srand(time(NULL));
    for(int i=0; i<mina; i++){
        int x, y;
        do{
            x = rand() % wiersz;
            y = rand() % kolumna;
        } 
        while((x == sx && y == sy) || plansza->komorki[x][y] == -1);
        plansza->komorki[x][y] = -1;

        // Aktualizacja cyfr w sąsiednich polach
        for(int dx = -1; dx <= 1; dx++){
            for(int dy = -1; dy <= 1; dy++){
                int nx = x + dx;
                int ny = y + dy;
                if(nx >= 0 && ny >= 0 && nx < wiersz && ny < kolumna && plansza->komorki[nx][ny] != -1){
                    plansza->komorki[nx][ny]++;
                }
            }
        }
    }
}

void drukuj_plansze(const Plansza *plansza){
    printf("   ");
    for (int j = 0; j < plansza->kolumna; j++){
        printf("%2d ", j);
    }
    printf("\n");

    for (int i = 0; i < plansza->wiersz; i++){
        printf("%2d ", i);
        for (int j = 0; j < plansza->kolumna; j++){
            printf("%2c ", plansza->widocznosc[i][j]);
        }
        printf("\n");
    }
}

void ustaw_poziom_trudnosci(Plansza *plansza, int poziom){
    switch(poziom) {
        case 1:
            inicjalizuj_plansze(plansza, 9, 9, 10, -1, -1);  // Poziom łatwy
            break;
        case 2:
            inicjalizuj_plansze(plansza, 16, 16, 40, -1, -1);  // Poziom średni
            break;
        case 3:
            inicjalizuj_plansze(plansza, 16, 30, 99, -1, -1);  // Poziom trudny
            break;
        default:
            printf("Nieznany poziom trudności!\n");
            break;
    }
}

void odkryj_wszystkie_miny(Plansza *plansza){
    for (int i = 0; i < plansza->wiersz; i++){
        for (int j = 0; j < plansza->kolumna; j++){
            if (plansza->komorki[i][j] == -1){
                plansza->widocznosc[i][j] = '*';
            }
        }
    }
}

void drukuj_skrocona_plansze(Plansza *plansza){
    printf("\nSkrócona plansza (widok debug):\n");
    for (int i = 0; i < plansza->wiersz; i++) {
        for (int j = 0; j < plansza->kolumna; j++){
            if (plansza->komorki[i][j] == -1) {
                printf(" * "); // Miejsce z miną
            } else {
                printf(" %d ", plansza->komorki[i][j]);
            }
        }
        printf("\n");
    }
}

// Funkcja rekurencyjna do odkrywania pustych pól
void odkryj_pole_rekurencyjnie(Plansza *plansza, int x, int y){
    // Sprawdzamy czy pole jest już odkryte
    if (plansza->widocznosc[x][y] != '#'){
        return;
    }

    // Odsłaniamy pole
    plansza->widocznosc[x][y] = '0' + plansza->komorki[x][y];

    // Jeśli na danym polu jest 0 min, rekurencyjnie odsłaniamy sąsiednie pola
    if (plansza->komorki[x][y] == 0){
        for (int dx = -1; dx <= 1; dx++){
            for (int dy = -1; dy <= 1; dy++){
                int nx = x + dx;
                int ny = y + dy;
                if (nx >= 0 && ny >= 0 && nx < plansza->wiersz && ny < plansza->kolumna){
                    odkryj_pole_rekurencyjnie(plansza, nx, ny);
                }
            }
        }
    }
}

void odkryj_pole(Plansza *plansza, int x, int y){
    if (x < 0 || y < 0 || x >= plansza->wiersz || y >= plansza->kolumna){
        printf("Bledne wspolrzedne (%d, %d). Sprobuj ponownie.\n", x, y);
        return;
    }
    if (plansza->widocznosc[x][y] == 'F'){
        printf("To pole jest oznaczone flaga. Nie mozesz go odkryc.\n");
        return;  // Ignoruj ruch, jeśli pole jest oznaczone flagą
    }
    if (plansza->widocznosc[x][y] == '#'){
        odkryj_pole_rekurencyjnie(plansza, x, y);
    }
}

int sprawdz_wygrana(const Plansza *plansza){
    for (int i = 0; i < plansza->wiersz; i++){
        for (int j = 0; j < plansza->kolumna; j++) {
            // Pole zakryte, które nie jest miną
            if (plansza->komorki[i][j] != -1 && plansza->widocznosc[i][j] == '#'){
                return 0; // Nie wszystkie pola zostały odkryte
            }
        }
    }

    // Sprawdzenie, czy wszystkie miny są oznaczone flagami
    if (!sprawdz_flage(plansza)){
        return 0; // Flagi nie są poprawnie ustawione
    }

    return 1; // Wszystkie pola są odkryte, a miny oznaczone
}

void ustaw_flage(Plansza *plansza, int x, int y){
    if (x < 0 || y < 0 || x >= plansza->wiersz || y >= plansza->kolumna){
        printf("Bledne wspolrzedne (%d, %d). Sprobuj ponownie.\n", x, y);
        return ;
    }
    if (plansza->widocznosc[x][y] != '#' && plansza->widocznosc[x][y] != 'F'){
        printf("Nie mozesz ustawic flagi na odkrytym polu.\n");
        return;
    }
    if (plansza->widocznosc[x][y] == '#'){
        plansza->widocznosc[x][y] = 'F'; // Ustawienie flagi
    } else if (plansza->widocznosc[x][y] == 'F') {
        plansza->widocznosc[x][y] = '#'; // Usuwanie flagi
    }
}

int trafiles_na_mine(const Plansza *plansza, int x, int y){
    if (x < 0 || y < 0 || x >= plansza->wiersz || y >= plansza->kolumna){
        printf("Bledne wspolrzedne (%d, %d). Sprobuj ponownie.\n", x, y);
        return 0;
    }
    if (plansza->komorki[x][y] == -1){
        plansza->widocznosc[x][y] = '*'; // Trafienie na minę
        return 1;
    }
    return 0;
}

void zwolnij_plansze(Plansza *plansza){
    for (int i = 0; i < plansza->wiersz; i++){
        free(plansza->komorki[i]);
        free(plansza->widocznosc[i]);
    }
    free(plansza->komorki);
    free(plansza->widocznosc);
}
int sprawdz_flage(const Plansza *plansza){
    int poprawnie_oznaczone = 0;
    int miny = 0;
    //int wszystkie_min = 0;

    for (int i = 0; i < plansza->wiersz; i++){
        for (int j = 0; j < plansza->kolumna; j++) {
            if (plansza->komorki[i][j] == -1) {  // Mina
                miny++;
                if (plansza->widocznosc[i][j] == 'F'){
                    poprawnie_oznaczone++;
                }
            }
        }
    }

    return poprawnie_oznaczone == miny;
}