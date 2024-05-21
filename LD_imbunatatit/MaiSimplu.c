#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Programare Programare;
typedef struct nodld nodld;

struct Programare
{
	char* data;
	char* numeSolicitant;
	float sumaPlata;
	int nrOrdine;
};

struct nodld
{
	Programare inf;
	struct nodld* next, * prev;
};

nodld* inserareNod(nodld* cap, nodld** coada, Programare p)
{
	nodld* nou = (nodld*)malloc(sizeof(nodld));

	nou->inf.data = (char*)malloc((strlen(p.data) + 1) * sizeof(char));
	strcpy(nou->inf.data, p.data);

	nou->inf.numeSolicitant = (char*)malloc((strlen(p.numeSolicitant) + 1) * sizeof(char));
	strcpy(nou->inf.numeSolicitant, p.numeSolicitant);

	nou->inf.sumaPlata = p.sumaPlata;
	nou->inf.nrOrdine = p.nrOrdine;

	nou->next = NULL;
	nou->prev = NULL;

	if (cap == NULL)
	{
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodld* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}
	return cap;
}

void traversare(nodld* cap)
{
	nodld* temp = cap;
	while (temp != NULL)
	{
		printf("\nData: %s, Nume Solicitant: %s, Suma Plata: %5.2f, NrOrdine: %d",
			temp->inf.data, temp->inf.numeSolicitant, temp->inf.sumaPlata, temp->inf.nrOrdine);
		temp = temp->next;
	}
}

void traversareInversa(nodld* coada)
{
	nodld* temp = coada;
	while (temp != NULL)
	{
		printf("\nData: %s, Nume Solicitant: %s, Suma Plata: %5.2f, NrOrdine: %d",
			temp->inf.data, temp->inf.numeSolicitant, temp->inf.sumaPlata, temp->inf.nrOrdine);
		temp = temp->prev;
	}
}

void dezalocare(nodld* cap)
{
	nodld* temp = cap;
	while (temp != NULL)
	{
		nodld* temp2 = temp->next;
		free(temp->inf.data);
		free(temp->inf.numeSolicitant);
		free(temp);
		temp = temp2;
	}
}

float sumaPlata(nodld* cap, char* numeSolicitant)
{
	float sumaPlata = 0;
	if (cap != NULL)
	{
		nodld* temp = cap;
		while (temp != NULL)
		{
			if (strcmp(temp->inf.numeSolicitant, numeSolicitant) == 0)
			{
				sumaPlata += temp->inf.sumaPlata;
			}
			temp = temp->next;
		}
	}
	return sumaPlata;
}

//float sumaPlata2Param(nodld* cap, char* data, bool areBiletTrimitere)
//{
//	float sumaPlata = 0;
//	if (cap != NULL)
//	{
//		nodld* temp = cap;
//		while (temp != NULL)
//		{
//			if (strcmp(temp->inf.data, data) == 0 && temp->inf.areBiletTrimitere == areBiletTrimitere)
//				sumaPlata += temp->inf.sumaPlata;
//			temp = temp->next;
//		}
//	}
//	return sumaPlata;
//}


float medieSumaPlata(nodld* cap, char* data)
{
	float sumaPlata = 0;
	int nrPacienti = 0;
	nodld* temp = cap;
	while (temp != NULL)
	{
		if (strcmp(temp->inf.data, data) == 0)
		{
			sumaPlata += temp->inf.sumaPlata;
			nrPacienti++;
		}
		temp = temp->next;

	}
	if (sumaPlata == 0 || nrPacienti == 0)
		return 0;
	return sumaPlata / nrPacienti;
}

void stergereNod(nodld** cap, nodld** coada, nodld* sters)
{
	if (*cap == NULL || sters == NULL || *coada == NULL)
	{
		return;
	}

	if (*cap == sters)
	{
		*cap = (*cap)->next;
		if (*cap != NULL)
			(*cap)->prev = NULL;

		free(sters->inf.data);
		free(sters->inf.numeSolicitant);
		free(sters);

		return;
	}

	if (*coada == sters)
	{
		*coada = (*coada)->prev;
		(*coada)->next = NULL;

		free(sters->inf.data);
		free(sters->inf.numeSolicitant);
		free(sters);

		return;
	}

	nodld* urmator = sters->next;
	nodld* anterior = sters->prev;

	anterior->next = urmator;
	urmator->prev = anterior;

	free(sters->inf.data);
	free(sters->inf.numeSolicitant);
	free(sters);

	return;
}

void stergereDupaData(nodld** cap, nodld** coada, char* data)
{
	nodld* temp = *cap;
	while (temp != NULL)
	{
		if (strcmp(data, temp->inf.data) == 0)
		{
			nodld* sters = temp;
			temp = temp->next;
			stergereNod(cap, coada, sters);
		}
		else
		{
			temp = temp->next;
		}
	}
}

void salvareInVector(nodld* cap, Programare* vect, int* nr)
{
	nodld* temp = cap;
	while (temp != NULL)
	{
		if (temp->inf.sumaPlata >= 150) //conditia
		{
			vect[*nr].data = (char*)malloc((strlen(temp->inf.data) + 1) * sizeof(char));
			strcpy(vect[*nr].data, temp->inf.data);
			vect[*nr].numeSolicitant = (char*)malloc((strlen(temp->inf.numeSolicitant) + 1) * sizeof(char));
			strcpy(vect[*nr].numeSolicitant, temp->inf.numeSolicitant);
			vect[*nr].sumaPlata = temp->inf.sumaPlata;
			vect[*nr].nrOrdine = temp->inf.nrOrdine;
			(*nr)++;
		}
		temp = temp->next;
	}
}

void salvareInVector2(nodld* cap, Programare* vect, int* nr, char* numeSolicitant)
{
	nodld* temp = cap;
	while (temp != NULL)
	{
		if (strcmp(temp->inf.numeSolicitant, numeSolicitant) == 0) //conditia
		{
			vect[*nr].data = (char*)malloc((strlen(temp->inf.data) + 1) * sizeof(char));
			strcpy(vect[*nr].data, temp->inf.data);
			vect[*nr].numeSolicitant = (char*)malloc((strlen(temp->inf.numeSolicitant) + 1) * sizeof(char));
			strcpy(vect[*nr].numeSolicitant, temp->inf.numeSolicitant);
			vect[*nr].sumaPlata = temp->inf.sumaPlata;
			vect[*nr].nrOrdine = temp->inf.nrOrdine;
			(*nr)++;
		}
		temp = temp->next;
	}
}

void main()
{
	int n;
	FILE* f = fopen("fisier2.txt", "r");
	fscanf(f, "%d", &n);
	nodld* cap = NULL;
	nodld* coada = NULL;
	Programare p;
	char buffer[30];
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%s", buffer);
		p.data = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.data, buffer);

		fscanf(f, "%s", buffer);
		p.numeSolicitant = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.numeSolicitant, buffer);

		fscanf(f, "%f", &p.sumaPlata);
		fscanf(f, "%d", &p.nrOrdine);

		cap = inserareNod(cap, &coada, p);

		free(p.data);
		free(p.numeSolicitant);
	}
	fclose(f);

	traversare(cap);
	printf("\n-----------------------------------------");
	traversareInversa(coada);

	printf("\nPacientul are de platit %5.2f lei.\n", sumaPlata(cap, "JamesAnderson"));

	printf("\nPentru aceasta zi suma medie platita de un pacient a fost de %5.2f lei.\n", medieSumaPlata(cap, "2023-06-20"));

	//salvare in vector
	printf("\n--------------------------------");
	printf("Programarile pentru care se va plati o suma mai mare sau egala cu 150:");
	Programare* vect = (Programare*)malloc(n * sizeof(Programare));
	int nr = 0;
	salvareInVector(cap, vect, &nr);
	for (int i = 0; i < nr; i++)
	{
		printf("\nData: %s, Nume Solicitant: %s, Suma Plata: %5.2f, NrOrdine: %d",
			vect[i].data, vect[i].numeSolicitant, vect[i].sumaPlata, vect[i].nrOrdine);

	}
	for (int i = 0; i < nr; i++)
	{
		free(vect[i].data);
		free(vect[i].numeSolicitant);
	}
	free(vect);

	printf("\n-----------------------------------------");
	printf("\nStergerea programarilor de la o anumita data:");
	stergereDupaData(&cap, &coada, "2023-06-20");
	traversare(cap);
	printf("\n-----------------------------------------");
	traversareInversa(coada);

	dezalocare(cap);
}
