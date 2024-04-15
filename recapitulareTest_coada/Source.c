#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Oras Oras;
typedef struct Nod Nod;

struct Oras {
	char* nume;
	int populatie;
};
struct Nod {
	Oras informatie;
	Nod* next;
};

Oras initOras(char* nume, int populatie) {
	Oras orasNou;
	orasNou.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(orasNou.nume, nume);

	orasNou.populatie = populatie;

	return orasNou;
}

void afisareOras(Oras oras) {
	printf("\nOrasul %s are populatia de %d locuitori", oras.nume, oras.populatie);
}

void put(Nod** coada, Oras oras) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->informatie = oras;
	nodNou->next = NULL;
	if (*coada) {
		Nod* nodCurent = *coada;
		while (nodCurent->next)
		{
			nodCurent = nodCurent->next;
		}
		nodCurent->next = nodNou;
	}
	else
	{
		*coada = nodNou;
	}
}

Oras get(Nod** coada) {
	Oras oras;
	oras.nume = NULL;
	oras.populatie = -1;
	if (*coada) {
		oras = (*coada)->informatie;

		Nod* copie = *coada;
		*coada = (*coada)->next;
		free(copie);

	}
	return oras;
}

void afisareCoada(Nod** coada) {
	if (*coada) {
		printf("\n\n Afisare coada: ");
		Oras oras;
		Nod* copieCoada = NULL;
		while (*coada)
		{
			oras = get(coada);
			afisareOras(oras);
			put(&copieCoada, oras);
		}
		*coada = copieCoada;
	}
	else {
		printf("\nCOADA E GOALA");
	}
}

void afisareDupaCriteriu(Nod** coada, char* orasNume) {
	if (*coada)
	{
		printf("\n\n Afisare oras %s", orasNume);
		Nod* coadaAux = NULL;
		Oras oras;
		while (*coada)
		{
			oras = get(coada);
			if (strcmp(oras.nume, orasNume) == 0)
			{
				afisareOras(oras);
			}
			put(&coadaAux, oras);
		}
		*coada = coadaAux;

	}
	else {
		printf("\nCoada e goala");
	}
}

Oras getDupaCriteriu(Nod** coada, char* orasNume) {
	Oras oras;
	oras.nume = NULL;
	oras.populatie = -1;
	if (*coada)
	{
		printf("\n\n GET oras %s", orasNume);
		Nod* coadaAux = NULL;

		while (*coada && strcmp((*coada)->informatie.nume, orasNume) != 0)
		{
			put(&coadaAux, get(coada));
		}
		if (*coada)
		{
			oras = get(coada);
		}
		while (*coada)
		{
			put(&coadaAux, get(coada));
		}
		*coada = coadaAux;
	}
	else {
		printf("\nCoada e goala");
	}
	return oras;
}

void dezalocareCoada(Nod** coada) {
	Oras oras;
	while (*coada)
	{
		oras = get(coada);
		free(oras.nume);
	}
}

void main() {
	Nod* coada = NULL;
	Oras oras;
	put(&coada, initOras("Pitesti", 0));
	put(&coada, initOras("Bucuresti", 13));
	put(&coada, initOras("Oradea", 123));
	put(&coada, initOras("Constanta", 1));
	put(&coada, initOras("Pitesti", 1));
	put(&coada, initOras("Pitesti", 2));
	put(&coada, initOras("Timisoara", 13000));
	put(&coada, initOras("Oradea", 3));

	afisareCoada(&coada);
	afisareDupaCriteriu(&coada, "Pitesti");
	afisareOras(getDupaCriteriu(&coada, "Pitesti"));
	printf("\nULTMA PARCURGERE A COZII");

	dezalocareCoada(&coada);
	while (coada)
	{
		oras = get(&coada);
		afisareOras(oras);
		free(oras.nume);
	}
}