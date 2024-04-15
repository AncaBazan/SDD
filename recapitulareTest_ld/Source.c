#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

typedef struct Produs Produs;
typedef struct Nod Nod;
typedef struct LDI LDI;

struct Produs {
	char* denumire;
	float pret;
	int stoc;
};

struct Nod {
	Produs info;
	Nod* prev;
	Nod* next;
};

struct LDI {
	Nod* prim;
	Nod* ultim;
};

Produs initProdus(char* nume, float pret, int stoc) {
	Produs produsNou;
	produsNou.denumire = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(produsNou.denumire, nume);

	produsNou.pret = pret;
	produsNou.stoc = stoc;

	return produsNou;
}

void afisareProdus(Produs produs) {
	printf("\nProdusul %s are pretul %.2f si cantitatea de %d", produs.denumire, produs.pret, produs.stoc);
}

void inserareLaInceput(LDI* lista, Produs produs) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = produs;
	nodNou->next = lista->prim;
	nodNou->prev = NULL;
	if (lista->prim) {
		lista->prim->prev = nodNou;
		lista->prim = nodNou;
	}
	else
	{
		lista->prim = lista->ultim = nodNou;
	}
}

void inserareLaSfarsit(LDI* lista, Produs produs) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = produs;
	nodNou->next = NULL;
	nodNou->prev = lista->ultim;
	if (lista->ultim)
	{
		lista->ultim->next = nodNou;
		lista->ultim = nodNou;
	}
	else {
		lista->prim = nodNou;
		lista->ultim = nodNou;
	}
}

void traversareStangaDreapta(LDI lista) {
	if (lista.prim)
	{
		while (lista.prim)
		{
			afisareProdus(lista.prim->info);
			lista.prim = lista.prim->next;
		}
	}
	else {
		printf("\n LISTA ESTE GOALA");
	}
}

void traversareDreaptaStanga(LDI lista) {
	if (lista.ultim) {
		while (lista.ultim) {
			afisareProdus(lista.ultim->info);
			lista.ultim = lista.ultim->prev;
		}
	}
	else
	{
		printf("\n LISTA ESTE GOALA");
	}
}

void dezalocare(LDI* lista) {
	if (lista->prim)
	{
		Nod* copie = lista->prim;
		while (copie)
		{
			free(copie->info.denumire);
			copie = copie->next;
			if (copie) {
				free(copie->prev);
			}

		}
		free(lista->ultim);
		lista->prim = lista->ultim = NULL;
	}
	else {
		printf("\nLISTA E GOALA");
	}
}

void cautareDupaCriterii(LDI lista, char* nume) {
	int ok = 0;
	if (lista.prim) {
		while (lista.prim)
		{
			if (strcmp(nume, lista.prim->info.denumire) == 0) {
				afisareProdus(lista.prim->info);
				ok = 1;
			}
			lista.prim = lista.prim->next;
		}
		if (!ok)
		{
			printf("\nNu exista produsul cu numele %s", nume);
		}
	}
	else
	{
		printf("\nLISTA E GOALA");
	}
}

void stergereDupaCriterii(LDI* lista, char* nume) {
	if (lista->prim)
	{
		Nod* nodCurent = lista->prim;
		while (nodCurent) {
			Nod* nodUrmator = nodCurent->next;
			if (strcmp(nodCurent->info.denumire, nume) == 0)
			{
				if (!nodCurent->prev) {//primul nod din lista
					lista->prim = nodCurent->next;
					lista->prim->prev = NULL;
				}
				else if (!nodCurent->next)
				{
					lista->ultim = nodCurent->prev;
					lista->ultim->next = NULL;
				}
				else
				{
					nodCurent->prev->next = nodCurent->next;
					nodCurent->next->prev = nodCurent->prev;
				}
				free(nodCurent->info.denumire);
				free(nodCurent);
			}
			nodCurent = nodUrmator;
		}
	}
	else {
		printf("\nLISTA ESTE GOALA");
	}
}

void conversieLD_Vector(LDI lista, Produs** vectorProduse, int* nrProduse) {
	Nod* copie = lista.prim;
	while (lista.prim)
	{
		(*nrProduse)++;
		lista.prim = lista.prim->next;
	}
	*vectorProduse = (Produs*)malloc((*nrProduse) * sizeof(Produs));
	int i = 0;
	while (copie)
	{
		(*vectorProduse)[i] = copie->info;
		i++;
		copie = copie->next;
	}
}

void main() {
	LDI listaDubla;
	listaDubla.prim = listaDubla.ultim = NULL;

	inserareLaSfarsit(&listaDubla, initProdus("ciocolata0", 144.6f, 83));
	inserareLaInceput(&listaDubla, initProdus("ciocolata1", 424.6f, 81));
	inserareLaInceput(&listaDubla, initProdus("ciocolata2", 443.6f, 83));
	inserareLaInceput(&listaDubla, initProdus("ciocolata3", 444.6f, 82));
	inserareLaInceput(&listaDubla, initProdus("ciocolata3", 44.56f, 81));
	inserareLaInceput(&listaDubla, initProdus("ciocolata5", 44.66f, 88));
	inserareLaInceput(&listaDubla, initProdus("ciocolata5", 44.67f, 87));
	inserareLaSfarsit(&listaDubla, initProdus("ciocolata4", 844.6f, 86));
	inserareLaSfarsit(&listaDubla, initProdus("ciocolata5", 494.6f, 85));
	inserareLaSfarsit(&listaDubla, initProdus("ciocolata5", 440.6f, 84));
	inserareLaSfarsit(&listaDubla, initProdus("ciocolata5", 44.16f, 83));
	inserareLaSfarsit(&listaDubla, initProdus("ciocolata6", 44.64f, 18));
	inserareLaSfarsit(&listaDubla, initProdus("ciocolata5", 44.63f, 82));


	printf("\nTRAVERSARE DREAPTA STANGA");
	traversareDreaptaStanga(listaDubla);
	printf("\nTRAVERSARE STANGA DREAPTA");
	traversareStangaDreapta(listaDubla);

	printf("\n\ncautare element");
	cautareDupaCriterii(listaDubla, "ciocolata5");
	cautareDupaCriterii(listaDubla, "ciocolata amara");

	stergereDupaCriterii(&listaDubla, "ciocolata5");
	printf("\nTRAVERSARE STANGA DREAPTA dupa stergere");
	traversareStangaDreapta(listaDubla);

	
	Produs* vector = NULL;
	int nr = 0;
	conversieLD_Vector(listaDubla, &vector, &nr);
	printf("\n AFISARE VECTOR");
	for (int i = 0; i < nr; i++)
	{
		afisareProdus(vector[i]);
	}
	free(vector);

	dezalocare(&listaDubla);

}