#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Produs Produs;
typedef struct Nod Nod;
typedef struct NodLD NodLD;
typedef struct LDI LDI;

struct Produs {
	char* nume;
	float pret;
	int stoc;
};

struct Nod {
	Produs info;
	Nod* next;
};

struct NodLD {
	Produs info;
	NodLD* prev;
	NodLD* next;
};

struct LDI {
	NodLD* prim;
	NodLD* ultim;
};


void afisareProdus(Produs produs) {
	printf("Produsul are numele: %s, pretul: %f, stocul: %d\n", produs.nume, produs.pret, produs.stoc);
}

//initializare produs cu parametri dati
Produs initProdus(const char* nume, float pret, int stoc) {

	Produs produsNou;
	//alocam spatiu pt nume
	produsNou.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(produsNou.nume, nume);
	produsNou.pret = pret;
	produsNou.stoc = stoc;
	return produsNou;
}

//initializare Produs Tastatura
Produs initProdusTastatura() {
	Produs produsNou;
	char buffer[20];

	printf("Nume: ");
	scanf("%s", buffer);
	produsNou.nume = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
	strcpy(produsNou.nume, buffer);

	printf("Pret: ");
	scanf("%f", &produsNou.pret);

	printf("Stoc: ");
	scanf("%d", &produsNou.stoc);

	return produsNou;
}

//initializare produs din fisier
Produs initProdusFisier(FILE* file) {
	Produs produs;
	if (file)
	{
		char buffer[20];

		fgets(buffer, 20, file);
		char* denumire = strtok(buffer, "\n");
		produs.nume = (char*)malloc(sizeof(char) * strlen(denumire) + 1);
		strcpy(produs.nume, denumire);

		fgets(buffer, 20, file);
		produs.pret = atof(buffer);

		fgets(buffer, 20, file);
		produs.stoc = atoi(buffer);

	}
	return produs;
}

void inserareLaInceput(Nod** cap, Produs produs) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = produs;
	nodNou->next = *cap; 
	*cap = nodNou;
}

void inserareLaSfarsit(Nod** cap, Produs produs) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = produs;
	nodNou->next = NULL; 
	if (*cap)
	{
		Nod* nodCurent = *cap;
		while (nodCurent->next)
		{
			nodCurent = nodCurent->next;
		}
		nodCurent->next = nodNou;
	}
	else
	{
		*cap = nodNou;
	}
}


void parcurgereLista(Nod* cap) {
	if (cap)
	{
		while (cap)
		{
			afisareProdus(cap->info);
			cap = cap->next;
		}
	}
	else {
		printf("LISTA ESTE GOALA");
	}
}

void stergeUltimNod(Nod** cap) {
	if ((*cap) && (*cap)->next) {
		Nod* aux = *cap;
		while (aux->next->next) {
			aux = aux->next;
		}
		free(aux->next->info.nume);
		free(aux->next);
		aux->next = NULL;
	}
	else
	{
		free((*cap)->info.nume);
		free((*cap));
		*cap = NULL;

	}
}

float calculPretMediu(Nod* cap) {
	float suma = 0;
	int nr = 0;
	while (cap) {
		suma += cap->info.pret;
		nr++;
		cap = cap->next;
	}
	if (nr == 0)
	{
		return 0;
	}
	return suma / nr;
}

char* getNumeProdus(Nod* cap, int stoc) {
	char* buffer[20];
	char* numeProdus = NULL;
	while (cap) {
		if (stoc == cap->info.stoc) {
			strcmp(buffer, cap->info.nume);
		}
		cap = cap->next;
	}
	if (strcmp(buffer, "") != 0) {
		numeProdus = (char*)malloc(sizeof(char) * strlen(buffer) + 1);
		strcpy(numeProdus, buffer);
	}
	return numeProdus;
}

void dezalocareLista(Nod** cap) {
	while (*cap)
	{
		Nod* copieCap = *cap;
		*cap = (*cap)->next;
		free(copieCap->info.nume);
		free(copieCap);
	}
}


void cautareNodDupaCriterii(Nod* cap, char* nume) {
	int gasit = 0;
	while (cap) {
		if (strcmp(nume, cap->info.nume) == 0)
		{
			afisareProdus(cap->info);
			gasit = 1;
		}
		cap = cap->next;
	}
	if (!gasit)
	{
		printf("Nu a fost gasit produsul cu numele %s", nume);
	}
}

void stergereDupaCriterii(Nod** cap, char* nume) {
	Nod* curent = *cap;
	Nod* anterior = NULL;

	while (curent) {
		if (strcmp(curent->info.nume, nume) == 0) {
			// Daca numele coincide, eliminam nodul
			if (anterior == NULL) {
				// Daca nodul este primul din lista
				*cap = curent->next;
				free(curent->info.nume);
				free(curent);
				curent = *cap;
			}
			else {
				anterior->next = curent->next;
				free(curent->info.nume);
				free(curent);
				curent = anterior->next;
			}
		}
		else {
			// Daca numele nu coincide, continuam parcurgerea listei
			anterior = curent;
			curent = curent->next;
		}
	}
}

void inserareDupaCriteriiStanga(Nod** cap, char* nume, Produs produs) {
	Nod* curent = *cap;
	Nod* precedent = NULL;
	while (curent)
	{
		if (strcmp(nume, curent->info.nume) == 0) {
			Nod* nodNouStanga = (Nod*)malloc(sizeof(Nod));
			nodNouStanga->info.pret = produs.pret;
			nodNouStanga->info.stoc = produs.stoc;
			nodNouStanga->info.nume = (char*)malloc(sizeof(char) * strlen(produs.nume) + 1);
			strcpy(nodNouStanga->info.nume, produs.nume);
			//daca e in stanga capului
			if (precedent == NULL)
			{
				nodNouStanga->next = curent;
				precedent = nodNouStanga;
				*cap = nodNouStanga;

			}
			else
			{
				nodNouStanga->next = curent;
				precedent->next = nodNouStanga;
				precedent = nodNouStanga;
			}
		}
		precedent = curent;
		curent = curent->next;
	}

}

void inserareDupaCriteriiDreapta(Nod** cap, char* nume, Produs produs) {
	Nod* curent = *cap;
	while (curent) {
		if (strcmp(nume, curent->info.nume) == 0) {
			Nod* nodNouDreapta = (Nod*)malloc(sizeof(Nod));
			nodNouDreapta->info.pret = produs.pret;
			nodNouDreapta->info.stoc = produs.stoc;
			nodNouDreapta->info.nume = (char*)malloc(sizeof(char) * strlen(produs.nume) + 1);
			strcpy(nodNouDreapta->info.nume, produs.nume);
			nodNouDreapta->next = curent->next;
			curent->next = nodNouDreapta;

		}
		curent = curent->next;
	}
}

void conversieLS_Vector(Nod* cap, Produs** vectorProduse, int* nrProduse) {
	if (cap)
	{
		Nod* copieCap = cap;
		while (cap)
		{
			(*nrProduse)++;
			cap = cap->next;
		}
		*vectorProduse = (Produs*)malloc(*nrProduse * sizeof(Produs));
		int i = 0;
		while (copieCap)
		{
			(*vectorProduse)[i] = copieCap->info;
			i++;
			copieCap = copieCap->next;
		}
	}
	else {
		printf("\nLista este GOALA");
	}
}

void main() {
	Nod* cap = NULL;
	FILE* fisier = fopen("Produse.txt", "r");

	inserareLaSfarsit(&cap, initProdusTastatura());
	inserareLaSfarsit(&cap, initProdus("caramele", 2.3f, 9));
	inserareLaInceput(&cap, initProdusFisier(fisier));
	inserareLaInceput(&cap, initProdusFisier(fisier));
	inserareLaInceput(&cap, initProdusFisier(fisier));
	inserareLaInceput(&cap, initProdusFisier(fisier));
	parcurgereLista(cap);
	inserareDupaCriteriiDreapta(&cap, "caramele", initProdus("dupa caramele", 1, 2));
	printf("\n-------dupa inserare la dreapta de caramele-----\n");
	parcurgereLista(cap);
	inserareDupaCriteriiStanga(&cap, "caramele", initProdus("inainte de caramele", 1.8882, 2222222));
	printf("\n-------dupa inserare la stanga de caramele-----\n");
	parcurgereLista(cap);
	stergereDupaCriterii(&cap, "caramele");
	printf("\n-------dupa stergere caramele-----\n");
	parcurgereLista(cap);

	fclose(fisier);

	Produs* vectorProduse = NULL;
	int nrProduse = 0;
	conversieLS_Vector(cap, &vectorProduse, &nrProduse);
	printf("\n-------dupa converise la vector-----\n");
	for (int i = 0; i < nrProduse; i++)
	{
		afisareProdus(vectorProduse[i]);
	}
	free(vectorProduse);

	dezalocareLista(&cap);
}