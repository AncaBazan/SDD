#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

// GRAF

typedef struct Judet Judet;
typedef struct NodGraf NodGraf;
typedef struct NodLegatura NodLegatura;
typedef struct Nod Nod;
typedef struct ListaDubla ListaDubla;

//stiva
struct Nod
{
	int ID;
	Nod* next;
	Nod* prev;
};

struct ListaDubla
{
	Nod* prim;
	Nod* ultim;
};

void push(ListaDubla* ld, int ID)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->ID = ID;
	nou->next = ld->prim;
	nou->prev = NULL;

	if (ld->prim == NULL)
	{
		ld->prim = ld->ultim = nou;
	}
	else
	{
		ld->prim->prev = nou;
		ld->prim = nou;
	}
}

// coada
void pushBack(ListaDubla* ld, int ID)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->ID = ID;
	nou->next = NULL;
	nou->prev = ld->ultim;

	if (ld->ultim == NULL)
	{
		ld->prim = ld->ultim = nou;
	}
	else
	{
		ld->ultim->next = nou;
		ld->ultim = nou;
	}
}

int pop(ListaDubla* ld)
{
	int id = -1;
	if (ld->prim)
	{
		id = ld->prim->ID;
		Nod* aux = ld->prim;

		ld->prim = ld->prim->next;
		if (ld->prim == NULL)
		{
			ld->ultim = NULL;
		}
		free(aux);
	}
	return id;
}

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

int getNumarNoduri(NodGraf* graf)
{
	int nr = 0;

	while (graf)
	{
		nr++;
		graf = graf->next;
	}

	return nr;
}


//stiva
void parcurgereInAdancime(NodGraf* graf, int idStart)
{

	ListaDubla stiva;
	stiva.prim = NULL;
	stiva.ultim = NULL;

	push(&stiva, idStart);

	int nrNoduri = getNumarNoduri(graf);
	int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		vizitate[i] = 0;
	}
	vizitate[idStart - 1] = 1;


	while (stiva.prim)
	{
		int idCurent = pop(&stiva);

		NodGraf* nodCurent = cautareDupaId(graf, idCurent);
		printf("%d: Judetul %s\n", nodCurent->info.id, nodCurent->info.nume);

		NodLegatura* p = nodCurent->legaturi;
		while (p)
		{

			if (vizitate[p->info->info.id - 1] == 0)
			{
				push(&stiva, p->info->info.id);
				vizitate[p->info->info.id - 1] = 1;
			}
			p = p->next;
		}
	}
}

void parcurgereInLatime(NodGraf* graf, int idStart)
{

	ListaDubla coada;
	coada.prim = NULL;
	coada.ultim = NULL;

	push(&coada, idStart);

	int nrNoduri = getNumarNoduri(graf);
	int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);
	for (int i = 0; i < nrNoduri; i++)
	{
		vizitate[i] = 0;
	}
	vizitate[idStart - 1] = 1;


	while (coada.prim)
	{
		int idCurent = pop(&coada);

		NodGraf* nodCurent = cautareDupaId(graf, idCurent);
		printf("%d: Judetul %s\n", nodCurent->info.id, nodCurent->info.nume);

		NodLegatura* p = nodCurent->legaturi;

		while (p)
		{
			if (vizitate[p->info->info.id - 1] == 0)
			{
				pushBack(&coada, p->info->info.id);
				vizitate[p->info->info.id - 1] = 1;
			}
			p = p->next;
		}
	}
}


void stergeGraf(NodGraf** graf)
{
	NodGraf* p = *graf;
	while (p)
	{
		NodLegatura* legaturi = p->legaturi;
		while (legaturi)
		{
			NodLegatura* aux = legaturi;
			legaturi = legaturi->next;

			free(aux);
		}
		NodGraf* aux = p;
		p = p->next;
		free(aux->info.nume);
		free(aux);
	}
	*graf = NULL;
}

void stergeNodGraf(NodGraf** graf, int id)
{
	if (*graf)
	{
		NodGraf* cautat = cautareDupaId(*graf, id);
		NodLegatura* leg = cautat->legaturi;
		while (leg)
		{
			NodGraf* vecin = leg->info;
			if (vecin->legaturi && vecin->legaturi->info->info.id == id)
			{
				NodLegatura* aux = vecin->legaturi;
				vecin->legaturi = vecin->legaturi->next;
				free(aux);
			}
			else
			{
				NodLegatura* parcurgere = vecin->legaturi;
				while (parcurgere && parcurgere->next && parcurgere->next->info->info.id != id)
				{
					parcurgere = parcurgere->next;
				}
				if (parcurgere->next)
				{
					NodLegatura* aux = parcurgere->next;
					parcurgere->next = aux->next;
					free(aux);
				}
			}
			NodLegatura* aux = leg;
			leg = leg->next;
			free(aux);
		}
		if ((*graf) == cautat)
		{
			NodGraf* aux = *graf;
			(*graf) = (*graf)->next;
			free(aux->info.nume);
			free(aux);
		}
		else
		{
			NodGraf* p = *graf;
			while (p->next && p->next->info.id != id)
			{
				p = p->next;
			}
			if (p->next)
			{
				NodGraf* aux = p->next;
				p->next = aux->next;
				free(aux->info.nume);
				free(aux);
			}
		}
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

	// parcurgere in adancime
	printf("\n\n");
	parcurgereInAdancime(graf, 1);

	// parcurgere in latime
	printf("\n\n");
	parcurgereInLatime(graf, 1);

	// stergere nod
	printf("\n\nDUPA STERGERE 6\n");
	stergeNodGraf(&graf, 1);
	afisareLista(graf);

	// stergere completa
	stergeGraf(&graf);
}