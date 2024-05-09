#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>

//vector binar de cautare

typedef struct Serial Serial;
typedef struct Nod Nod;

struct Serial
{
	char* nume;
	int id;
	int nrEpisoade;
};

struct Nod
{
	Serial serial;
	Nod* stanga;
	Nod* dreapta;
};


Serial initializareSerial(const char* nume, int id, int nrEpisoade)
{
	Serial s;
	s.id = id;
	s.nrEpisoade = nrEpisoade;

	s.nume = (char*)malloc(sizeof(char) * (strlen(nume) + 1));
	strcpy(s.nume, nume);

	return s;
}


void inserareSerialInArbore(Nod** radacina, Serial s)
{
	if (*radacina == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->serial = s;
		nou->dreapta = NULL;
		nou->stanga = NULL;

		*radacina = nou;
	}
	else
	{
	
		if (s.id > (*radacina)->serial.id)
		{
			inserareSerialInArbore(&(*radacina)->dreapta, s);
		}
		else
		{
			inserareSerialInArbore(&(*radacina)->stanga, s);
		}
	}
}


void afisareSerial(Serial s)
{
	printf("Serialul %s cu id-ul %d are %d episoade.\n", s.nume, s.id, s.nrEpisoade);
}


void afisareArborePreordine(Nod* radacina)
{
	if (radacina != NULL)
	{

		afisareSerial(radacina->serial);
		afisareArborePreordine(radacina->stanga);
		afisareArborePreordine(radacina->dreapta);
	}
}


void afisareArboreInordine(Nod* radacina)
{
	if (radacina != NULL)
	{
	
		afisareArborePreordine(radacina->stanga);
		afisareSerial(radacina->serial);
		afisareArborePreordine(radacina->dreapta);
	}
}

Serial cautareSerialId(Nod* radacina, int id)
{
	if (radacina != NULL)
	{
		if (radacina->serial.id == id)
		{
			Serial s = initializareSerial(radacina->serial.nume, radacina->serial.id, radacina->serial.nrEpisoade);
			return s;
		}
		else
		{
			if (radacina->serial.id < id)
			{
				return cautareSerialId(radacina->dreapta, id);
			}
			else
			{
				return cautareSerialId(radacina->stanga, id);
			}
		}
	}
	else
	{
		return initializareSerial("n/a", -1, -1);
	}
}


void stergeArbore(Nod** radacina)
{
	if (*radacina != NULL)
	{

		stergeArbore(&(*radacina)->stanga);
		stergeArbore(&(*radacina)->dreapta);
		free((*radacina)->serial.nume);
		free(*radacina);
	}
	*radacina = NULL;
}

int determinareInaltimeArbore(Nod* radacina)
{
	if (radacina)
	{
		int hStanga = determinareInaltimeArbore(radacina->stanga);
		int hDreapta = determinareInaltimeArbore(radacina->dreapta);
		return ((hStanga > hDreapta) ? hStanga : hDreapta) + 1;
	}
	else
	{
		return 0;
	}
}


//arbori AVL (echilibrati) 

int gradEchilibru(Nod* radacina)
{
	if (radacina) {

		return determinareInaltimeArbore(radacina->stanga) - determinareInaltimeArbore(radacina->dreapta);
	}
	else
	{
		return 0;
	}
}


void rotireStanga(Nod** radacina)
{
	Nod* aux = (*radacina)->dreapta;
	(*radacina)->dreapta = aux->stanga;
	aux->stanga = *radacina;

	*radacina = aux;
}

void rotireDreapta(Nod** radacina)
{
	Nod* aux = (*radacina)->stanga;
	(*radacina)->stanga = aux->dreapta;
	aux->dreapta = *radacina;

	*radacina = aux;
}


void inserareArboreAVL(Nod** radacina, Serial s)
{
	if (*radacina == NULL)
	{
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->serial = s;
		nou->dreapta = NULL;
		nou->stanga = NULL;

		*radacina = nou;
	}
	else
	{
		if (s.id > (*radacina)->serial.id)
		{
			inserareArboreAVL(&(*radacina)->dreapta, s);
		}
		else
		{
			inserareArboreAVL(&(*radacina)->stanga, s);
		}
	}
	



	int grad = gradEchilibru(*radacina);

	if (grad == 2) // dezechilibru stanga
	{
		if (gradEchilibru((*radacina)->stanga) == -1)
		{
			
			rotireStanga(&(*radacina)->stanga);
			rotireDreapta(radacina);
		}
		else
		{
			
			rotireDreapta(radacina);
		}
	}

	if (grad == -2) // dezechilibru dreapta
	{
		if (gradEchilibru((*radacina)->dreapta) == 1)
		{

			rotireDreapta(&(*radacina)->dreapta);
			rotireStanga(radacina);
		}
		else
		{
			rotireStanga(radacina);
		}
	}
}

void main()
{
	Nod* radacina = NULL;
	inserareArboreAVL(&radacina, initializareSerial("Black Mirror", 1, 10));
	inserareArboreAVL(&radacina, initializareSerial("Vikings", 2, 10));
	inserareArboreAVL(&radacina, initializareSerial("Lupin", 3, 10));
	inserareArboreAVL(&radacina, initializareSerial("Lord of the Rings", 4, 6));

	inserareArboreAVL(&radacina, initializareSerial("Friends", 5, 10));
	inserareArboreAVL(&radacina, initializareSerial("The 100", 6, 10));
	inserareArboreAVL(&radacina, initializareSerial("The 100", 7, 10));

	afisareArborePreordine(radacina);
	printf("\n");
	afisareArboreInordine(radacina);
	printf("\n");

	Serial s = cautareSerialId(radacina, 7);
	afisareSerial(s);
	free(s.nume);

	printf("\nInaltime: %d", determinareInaltimeArbore(radacina));

	stergeArbore(&radacina);
}