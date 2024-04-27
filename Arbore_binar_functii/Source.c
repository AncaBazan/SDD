#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Carte {
    int id;
    char* nume;
    int nrPagini;
} Carte;

typedef struct Nod {
    Carte info;
    struct Nod* left;
    struct Nod* right;
} Nod;

// prototipuri de functii
Carte initializareCarte(int id, const char* nume, int nrPagini);
Nod* creareNod(Carte carte);
Nod* inserareInArbore(Nod* radacina, Carte carte);
void parcurgereInordine(Nod* radacina);
void dezalocareArbore(Nod* radacina);

int main() {
    Nod* radacina = NULL;
    radacina = inserareInArbore(radacina, initializareCarte(12, "Morometii", 260));
    radacina = inserareInArbore(radacina, initializareCarte(10, "Baltagul", 100));
    radacina = inserareInArbore(radacina, initializareCarte(11, "Amintiri din Copilarie", 380));
    radacina = inserareInArbore(radacina, initializareCarte(14, "Ion", 120));
    radacina = inserareInArbore(radacina, initializareCarte(7, "Enigma Otiliei", 300));
    radacina = inserareInArbore(radacina, initializareCarte(8, "Harap-Alb", 54));
    radacina = inserareInArbore(radacina, initializareCarte(13, "Moara cu noroc", 100));

    printf("Parcurgere inordine:\n");
    parcurgereInordine(radacina);

    dezalocareArbore(radacina);

    return 0;
}

// functie pentru initializarea unei carti
Carte initializareCarte(int id, const char* nume, int nrPagini) {
    Carte carte;
    carte.id = id;
    carte.nrPagini = nrPagini;
    carte.nume = _strdup(nume); // Alocare si copiere a numelui cartii
    return carte;
}

// functie pentru crearea unui nod nou in arbore
Nod* creareNod(Carte carte) {
    Nod* nodNou = (Nod*)malloc(sizeof(Nod));
    if (nodNou == NULL) {
        fprintf(stderr, "Eroare la alocarea memoriei pentru nod!\n");
        exit(EXIT_FAILURE);
    }
    nodNou->info = carte;
    nodNou->left = NULL;
    nodNou->right = NULL;
    return nodNou;
}

// functie pentru inserarea unei carti in arbore
Nod* inserareInArbore(Nod* radacina, Carte carte) {
    if (radacina == NULL) {
        return creareNod(carte);
    }

    if (carte.id < radacina->info.id) {
        radacina->left = inserareInArbore(radacina->left, carte);
    }
    else if (carte.id > radacina->info.id) {
        radacina->right = inserareInArbore(radacina->right, carte);
    }
    else {
        printf("Id-ul %d exista deja in arbore. Cea mai recenta carte cu acest id va fi ignorata.\n", carte.id);
    }

    return radacina;
}

// functie pentru parcurgerea in ordine a arborelui si afisarea cartilor
void parcurgereInordine(Nod* radacina) {
    if (radacina != NULL) {
        parcurgereInordine(radacina->left);
        printf("ID: %d, Nume: %s, Nr. pagini: %d\n", radacina->info.id, radacina->info.nume, radacina->info.nrPagini);
        parcurgereInordine(radacina->right);
    }
}

// functie pentru dezalocarea memoriei ocupate de arbore
void dezalocareArbore(Nod* radacina) {
    if (radacina != NULL) {
        dezalocareArbore(radacina->left);
        dezalocareArbore(radacina->right);
        free(radacina->info.nume); 
        free(radacina); 
    }
}
