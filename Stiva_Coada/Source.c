#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Angajat Angajat;
typedef struct NodStiva NodStiva;
typedef struct NodCoada NodCoada;

struct Angajat
{
	int cod;
	char* nume;
	float salariu;
	float vechime;
};

struct NodStiva
{
	struct Angajat a;
	struct NodStiva* next;
};

struct NodCoada
{
	struct Angajat a;
	struct NodCoada* next;
};

void afiseazaAngajat(struct Angajat a)
{
	printf("%d %s %.2f %.2f\n", a.cod, a.nume, a.salariu, a.vechime);
}

struct Angajat deepCopyAngajat(struct Angajat a)
{
	struct Angajat nou;

	nou.cod = a.cod;
	nou.salariu = a.salariu;
	nou.vechime = a.vechime;
	nou.nume = (char*)malloc(strlen(a.nume) + 1);
	strcpy(nou.nume, a.nume);

	return nou;
}


void push(struct NodStiva** varf, struct Angajat a)
{
	struct NodStiva* nou = (struct NodStiva*)malloc(sizeof(struct NodStiva));

	nou->a = deepCopyAngajat(a);
	nou->next = NULL;

	if (*varf == NULL)
	{
		*varf = nou;
	}
	else
	{
		nou->next = *varf;

		*varf = nou;
	}

}

int pop(struct NodStiva** varf, struct Angajat* angExtras)
{
	if (*varf == NULL)
		return -1;
	{
		*angExtras = deepCopyAngajat((*varf)->a);

		struct NodStiva* temp = *varf;

		(*varf) = (*varf)->next;

		free(temp->a.nume);
		free(temp);

		return 0;

	}

}



void traversareStiva(struct NodStiva* varf)
{
	struct NodStiva* temp = varf;

	while (temp)
	{
		afiseazaAngajat(temp->a);
		temp = temp->next;
	}
}


void put(struct NodCoada** prim, struct NodCoada** ultim, struct Angajat a)
{
	struct NodCoada* nou = (struct NodCoada*)malloc(sizeof(struct NodCoada));
	nou->a = deepCopyAngajat(a);
	nou->next = NULL;

	if (*prim == NULL && *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	{
		(*ultim)->next = nou;
		(*ultim) = nou;
	}
}

int get(struct NodCoada** prim, struct NodCoada** ultim, struct Angajat* angExtras)
{
	if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
	else if (*prim != NULL && *ultim != NULL)
	{
		*angExtras = deepCopyAngajat((*prim)->a);

		struct NodCoada* temp = *prim;
		*prim = (*prim)->next;

		free(temp->a.nume);
		free(temp);

		return 0;

	}
}

void main()
{
	FILE* f;

	f = fopen("angajati.txt", "r+");

	char buffer[64];

	struct Angajat a;

	struct NodStiva* varf = NULL;
	struct NodCoada* prim, * ultim;
	prim = NULL;
	ultim = NULL;

	fscanf(f, "%d", &a.cod);

	while (!feof(f))
	{
		fscanf(f, "%s", buffer);
		a.nume = (char*)malloc(strlen(buffer) + 1);
		strcpy(a.nume, buffer);

		fscanf(f, "%f", &a.salariu);
		fscanf(f, "%f", &a.vechime);

		push(&varf, a);
		put(&prim, &ultim, a);

		free(a.nume);

		fscanf(f, "%d", &a.cod);
	}

	fclose(f);


	struct Angajat angPop;
	printf("Afisare din STIVA: \n");
	while (pop(&varf, &angPop) == 0)
	{
		printf("Angajat extras: ");
		afiseazaAngajat(angPop);
	}

	printf("\n\nAfisare din COADA: \n");
	while (get(&prim, &ultim, &angPop) == 0)
	{
		printf("Angajat extras: ");
		afiseazaAngajat(angPop);
	}



}