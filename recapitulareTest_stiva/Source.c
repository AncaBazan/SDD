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

void push(Nod** stiva, Oras oras) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->informatie = oras;
	nodNou->next = *stiva;
	*stiva = nodNou;
}

Oras pop(Nod** stiva) {
	Oras oras;
	oras.nume = NULL;
	oras.populatie = -1;
	if (*stiva) {
		Nod* copie = *stiva;
		oras = (*stiva)->informatie;
		*stiva = copie->next;
		free(copie);
	}
	return oras;
}

void afisareStiva(Nod** stiva) {
	if (*stiva) {
		printf("\n\n Afisare stiva: ");
		Oras oras;
		Nod* copieStiva = NULL;
		while (*stiva)
		{
			oras = pop(stiva);
			afisareOras(oras);
			push(&copieStiva, oras);
		}
		while (copieStiva)
		{
			oras = pop(&copieStiva);
			push(stiva, oras);
		}
	}
	else {
		printf("\nSTIVA E GOALA");
	}
}

void afisareDupaCriteriu(Nod** stiva, char* orasNume) {
	if (*stiva)
	{
		printf("\n\n afisare oras %s", orasNume);
		Nod* stivaAux = NULL;
		Oras oras;
		while (*stiva)
		{
			oras = pop(stiva);
			if (strcmp(oras.nume, orasNume) == 0)
			{
				afisareOras(oras);
			}
			push(&stivaAux, oras);
		}
		while (stivaAux)
		{
			push(stiva, pop(&stivaAux));
		}
	}
	else {
		printf("\nStiva e goala");
	}
}

Oras popDupaCriteriu(Nod** stiva, char* orasNume) {
	Oras oras;
	oras.nume = NULL;
	oras.populatie = -1;
	if (*stiva)
	{
		printf("\n\n POP oras %s", orasNume);
		Nod* stivaAux = NULL;

		while (*stiva && strcmp((*stiva)->informatie.nume, orasNume) != 0)
		{
			push(&stivaAux, pop(stiva));
		}
		if (*stiva)
		{
			oras = pop(stiva);
		}
		while (stivaAux)
		{
			push(stiva, pop(&stivaAux));
		}
	}
	else {
		printf("\nStiva e goala");
	}
	return oras;
}

void dezalocareStiva(Nod** stiva) {
	Oras oras;
	while (*stiva)
	{
		oras = pop(stiva);
		free(oras.nume);
	}
}

void main() {
	Nod* stiva = NULL;
	Oras oras;
	push(&stiva, initOras("Pitesti", 0));
	push(&stiva, initOras("Bucuresti", 13));
	push(&stiva, initOras("Oradea", 123));
	push(&stiva, initOras("Constanta", 1));
	push(&stiva, initOras("Pitesti", 1));
	push(&stiva, initOras("Pitesti", 2));
	push(&stiva, initOras("Timisoara", 13000));
	push(&stiva, initOras("Oradea", 3));

	afisareStiva(&stiva);
	afisareDupaCriteriu(&stiva, "Pitesti");
	afisareOras(popDupaCriteriu(&stiva, "Pitesti"));
	printf("\nULTMA PARCURGERE A STIVEI");

	dezalocareStiva(&stiva);
	while (stiva)
	{
		oras = pop(&stiva);
		afisareOras(oras);
		free(oras.nume);
	}
}