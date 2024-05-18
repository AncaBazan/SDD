#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

// GRAF

typedef struct Judet Judet;
typedef struct NodGraf NodGraf;
typedef struct NodLegatura NodLegatura;

struct Judet
{
	int id; 
	char* nume;
};

struct NodGraf
{
	Judet info;
	NodGraf* next;
	NodLegatura* legaturi; 
};

struct NodLegatura
{
	NodGraf* info; 
	NodLegatura* next;
};


Judet initializareJudet(int id, char* nume)
{
	Judet j;
	j.id = id;
	j.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(j.nume, nume);

	return j;
}

NodGraf* inserareNodGraf(NodGraf* lista, Judet j)
{
	NodGraf* nou = (NodGraf*)malloc(sizeof(NodGraf));
	nou->info = j;
	nou->legaturi = NULL;
	nou->next = NULL;

	if (lista)
	{
		NodGraf* p = lista;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;

		return lista;
	}
	else
	{
		return nou;
	}
}


NodLegatura* inserareNodLegatura(NodLegatura* cap, NodGraf* info)
{
	NodLegatura* nou = (NodLegatura*)malloc(sizeof(NodLegatura));
	nou->info = info; 
	nou->next = NULL;

	if (cap)
	{
		NodLegatura* p = cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = nou;

		return cap;
	}
	else
	{
		return nou;
	}
}


void afisareLista(NodGraf* lista)
{
	NodGraf* p = lista;
	while (p)
	{
		printf("Id: %d, Judetul: %s are legatura cu:\n", p->info.id, p->info.nume);

		NodLegatura* leg = p->legaturi;
		while (leg)
		{
			printf("\tId: %d, Judetul: %s\n", leg->info->info.id, leg->info->info.nume);

			leg = leg->next;
		}

		p = p->next;
	}
}

NodGraf* cautareDupaId(NodGraf* lista, int id)
{
	while (lista && lista->info.id != id)
	{
		lista = lista->next;
	}
	return lista;
}


void inserareMuchie(NodGraf* lista, int idStart, int idDestinaite)
{
	NodGraf* nodStart = cautareDupaId(lista, idStart);
	NodGraf* nodDestinatie = cautareDupaId(lista, idDestinaite);

	
	if (nodStart && nodDestinatie)
	{
		nodDestinatie->legaturi = inserareNodLegatura(nodDestinatie->legaturi, nodStart);
		nodStart->legaturi = inserareNodLegatura(nodStart->legaturi, nodDestinatie);
	}
}


void main()
{
	NodGraf* graf = NULL;

	// inserari
	graf = inserareNodGraf(graf, initializareJudet(1, "Bucuresti"));
	graf = inserareNodGraf(graf, initializareJudet(2, "Iasi"));
	graf = inserareNodGraf(graf, initializareJudet(3, "Brasov"));
	graf = inserareNodGraf(graf, initializareJudet(4, "Vaslui"));
	graf = inserareNodGraf(graf, initializareJudet(5, "Cluj"));
	graf = inserareNodGraf(graf, initializareJudet(6, "Botosani"));

	// afisare lista
	afisareLista(graf);

	// inserare legaturi
	inserareMuchie(graf, 1, 3);
	inserareMuchie(graf, 1, 5);
	inserareMuchie(graf, 1, 6);
	inserareMuchie(graf, 2, 3);
	inserareMuchie(graf, 3, 4);
	inserareMuchie(graf, 5, 4);
	inserareMuchie(graf, 5, 6);
	inserareMuchie(graf, 6, 4);

	// afisare graf
	printf("\n");
	afisareLista(graf);
}