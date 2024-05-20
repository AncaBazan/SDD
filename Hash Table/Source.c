#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>

typedef struct Proiect Proiect;
typedef struct nodls nodls;
typedef struct hashT hashT;

struct Proiect
{
	unsigned int cod;
	char* titlu;
	char* beneficiar;
	unsigned char nrExecutanti;
	float buget;
};

struct nodls
{
	Proiect inf;
	struct nodls* next;
};

struct hashT
{
	int nrElem;
	struct nodls** vect;
};

int functieHash(hashT tabela, char beneficiar[20])
{ 
	return beneficiar[0] % tabela.nrElem;
}

void inserareHash(hashT tabela, Proiect p)
{
	if (tabela.vect != NULL)
	{
		int pozitie = functieHash(tabela, p.beneficiar);
		nodls* nou = (nodls*)malloc(sizeof(nodls));

		nou->inf.cod = p.cod;

		nou->inf.titlu = (char*)malloc((strlen(p.titlu) + 1) * sizeof(char));
		strcpy(nou->inf.titlu, p.titlu);

		nou->inf.beneficiar = (char*)malloc((strlen(p.beneficiar) + 1) * sizeof(char));
		strcpy(nou->inf.beneficiar, p.beneficiar);

		nou->inf.nrExecutanti = p.nrExecutanti;
		nou->inf.buget = p.buget;

		nou->next = NULL;

		if (tabela.vect[pozitie] == NULL)
			tabela.vect[pozitie] = nou;
		else
		{
			nodls* temp = tabela.vect[pozitie];
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = nou;
		}
	}
}

void traversareLS(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		printf("\nCod: %u Titlu: %s Beneficiar: %s Nr Executanti: %u Buget: %5.2f",
			temp->inf.cod, temp->inf.titlu, temp->inf.beneficiar, temp->inf.nrExecutanti, temp->inf.buget);
		temp = temp->next;
	}
}

void traversareHash(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
			if (tabela.vect[i] != NULL)
			{
				printf("\nPozitie: %d ", i);
				traversareLS(tabela.vect[i]);
			}
	}
}

void dezalocareLS(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		nodls* temp2 = temp->next;
		free(temp->inf.titlu);
		free(temp->inf.beneficiar);
		free(temp);
		temp = temp2;
	}
}

void dezalocareHash(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				dezalocareLS(tabela.vect[i]);
			}
		}
		free(tabela.vect);
	}
}

float bugetTotalInvestitii(hashT tabela, char* beneficiar)
{
	float buget = 0;
	if (tabela.vect != NULL)
	{
		int pozitie = functieHash(tabela, beneficiar);
		nodls* temp = tabela.vect[pozitie];
		while (temp != NULL)
		{
			if (strcmp(temp->inf.beneficiar, beneficiar) == 0)
			{
				buget += temp->inf.buget;
			}
			temp = temp->next;

		}
	}
	return buget;
}

int detNrProiecte(hashT tabela, char* beneficiar)
{
	int nrProiecte = 0;
	if (tabela.vect != NULL)
	{
		int pozitie = functieHash(tabela, beneficiar);
		nodls* temp = tabela.vect[pozitie];
		while (temp != NULL)
		{
			if (strcmp(temp->inf.beneficiar, beneficiar) == 0)
				nrProiecte++;
			temp = temp->next;
		}
	}
	return nrProiecte;
}

void modificareNumeBeneficiar(hashT tabela, const char* beneficiar, const char* numeNouBeneficiar)
{
	int pozitie = functieHash(tabela, beneficiar);
	if (tabela.vect != NULL)
	{
		nodls* temp = tabela.vect[pozitie];
		while (temp != NULL)
		{
			if (strcmp(temp->inf.beneficiar, beneficiar) == 0)
			{
				free(temp->inf.beneficiar);
				temp->inf.beneficiar = (char*)malloc((strlen(numeNouBeneficiar) + 1) * sizeof(char));
				strcpy(temp->inf.beneficiar, numeNouBeneficiar);
				break;
			}
			temp = temp->next;
		}

	}
}

void modificareTitlu(hashT tabela, unsigned int cod, char* titluNou)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				nodls* temp = tabela.vect[i];
				while (temp != NULL)
				{
					if (temp->inf.cod == cod)
					{
						free(temp->inf.titlu);
						temp->inf.titlu = (char*)malloc((strlen(titluNou) + 1) * sizeof(char));
						strcpy(temp->inf.titlu, titluNou);
					}
					temp = temp->next;
				}
			}
		}

	}
}


nodls* inserareLista(hashT tabela, nodls* cap, float bugetMin)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.nrElem; i++)
		{
			if (tabela.vect[i] != NULL)
			{
				nodls* temp = tabela.vect[i];
				while (temp != NULL)
				{
					if (temp->inf.buget > bugetMin)
					{
						nodls* nou = (nodls*)malloc(sizeof(nodls));

						nou->inf.cod = temp->inf.cod;
						nou->inf.titlu = (char*)malloc((strlen(temp->inf.titlu) + 1) * sizeof(char));
						strcpy(nou->inf.titlu, temp->inf.titlu);
						nou->inf.beneficiar = (char*)malloc((strlen(temp->inf.beneficiar) + 1) * sizeof(char));
						strcpy(nou->inf.beneficiar, temp->inf.beneficiar);
						nou->inf.nrExecutanti = temp->inf.nrExecutanti;
						nou->inf.buget = temp->inf.buget;

						nou->next = NULL;
						if (cap == NULL)
							cap = nou;
						else
						{
							nodls* temp = cap;
							while (temp->next != NULL)
								temp = temp->next;
							temp->next = nou;
						}

					}
					temp = temp->next;
				}
			}
		}
	}
	return cap;
}


void stergeNod(nodls* nod)
{
	free(nod->inf.titlu);
	free(nod->inf.beneficiar);
	free(nod);
}


void stergere(hashT tabela, char* beneficiar)
{
	if (tabela.vect != NULL)
	{
		int pozitie = functieHash(tabela, beneficiar);
		nodls* temp = tabela.vect[pozitie];
		nodls* prev = NULL;

		while (temp != NULL)
		{
			if (strcmp(temp->inf.beneficiar, beneficiar) == 0)
			{
				if (prev == NULL)
					tabela.vect[pozitie] = temp->next;
				else
					prev->next = temp->next;

				stergeNod(temp);
				break;
			}

			prev = temp;
			temp = temp->next;
		}
	}
}

void salvareInVector2(hashT tabela, Proiect* vect, int* nr, float bugetMinim)
{
	for (int i = 0; i < tabela.nrElem; i++)
	{
		nodls* temp = tabela.vect[i];
		while (temp != NULL)
		{
			if (temp->inf.buget > bugetMinim)
			{
				vect[*nr].cod = temp->inf.cod;
				vect[*nr].titlu = (char*)malloc((strlen(temp->inf.titlu) + 1) * sizeof(char));
				strcpy(vect[*nr].titlu, temp->inf.titlu);
				vect[*nr].beneficiar = (char*)malloc((strlen(temp->inf.beneficiar) + 1) * sizeof(char));
				strcpy(vect[*nr].beneficiar, temp->inf.beneficiar);
				vect[*nr].nrExecutanti = temp->inf.nrExecutanti;
				vect[*nr].buget = temp->inf.buget;
				(*nr)++;
			}
			temp = temp->next;
		}
	}
}


Proiect* salvareInVector(hashT tabela, int* count, float threshold)
{

	*count = 0;
	for (int i = 0; i < tabela.nrElem; i++)
	{
		nodls* temp = tabela.vect[i];
		while (temp)
		{
			if (temp->inf.buget > threshold)
				(*count)++;
			temp = temp->next;
		}
	}

	Proiect* vector = (Proiect*)malloc((*count) * sizeof(Proiect));
	int index = 0;

	for (int i = 0; i < tabela.nrElem; i++)
	{
		nodls* temp = tabela.vect[i];
		while (temp)
		{
			if (temp->inf.buget > threshold)
			{
				vector[index].cod = temp->inf.cod;
				vector[index].titlu = (char*)malloc((strlen(temp->inf.titlu) + 1) * sizeof(char));
				strcpy(vector[index].titlu, temp->inf.titlu);
				vector[index].beneficiar = (char*)malloc((strlen(temp->inf.beneficiar) + 1) * sizeof(char));
				strcpy(vector[index].beneficiar, temp->inf.beneficiar);
				vector[index].nrExecutanti = temp->inf.nrExecutanti;
				vector[index].buget = temp->inf.buget;
				index++;
			}
			temp = temp->next;
		}
	}

	return vector;
}


void main()
{
	hashT tabela;
	tabela.nrElem = 30;
	tabela.vect = (nodls**)malloc(tabela.nrElem * sizeof(nodls*));
	for (int i = 0; i < tabela.nrElem; i++)
		tabela.vect[i] = NULL;

	int n;
	FILE* f = fopen("fisier.txt", "r");
	fscanf(f, "%d", &n);
	nodls* cap = NULL;
	Proiect p;
	char buffer[20];
	for (int i = 0; i < n; i++)
	{
		fscanf(f, "%u", &p.cod);

		fscanf(f, "%s", buffer);
		p.titlu = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.titlu, buffer);

		fscanf(f, "%s", buffer);
		p.beneficiar = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		strcpy(p.beneficiar, buffer);

		fscanf(f, "%u", &p.nrExecutanti);
		fscanf(f, "%f", &p.buget);

		inserareHash(tabela, p);
		free(p.titlu);
		free(p.beneficiar);
	}
	fclose(f);

	traversareHash(tabela);


	printf("\n-------------------------------\n");
	printf("\nBugetul total al beneficiarului Vlad este %5.2f", bugetTotalInvestitii(tabela, "Vlad"));

	printf("\n-------------------------------\n");
	printf("\nBeneficiarul are un numar de %d proiecte ", detNrProiecte(tabela, "Ioana"));

	printf("\n-------------------------------\n");
	printf("\nModific numele unui beneficiar\n");
	modificareNumeBeneficiar(tabela, "Vlad", "Vladut");
	traversareHash(tabela);

	printf("\n-------------------------------\n");
	printf("\nModific titlul proiectului cu un anumit cod\n");
	modificareTitlu(tabela, 104, "XXX");
	traversareHash(tabela);

	printf("\n-------------------------------\n");
	printf("\nStergerea proiectului care are un anumit beneficiar\n");
	stergere(tabela, "Ionel");
	traversareHash(tabela);

	printf("\n-------------------------------\n");
	printf("\nInserare in lista:\n");
	cap = inserareLista(tabela, cap, 4000);
	traversareLS(cap);
	dezalocareLS(cap);

	printf("\n-------------------------------\n");
	printf("\nSalvare in vector a proiectelor ce au un buget care depaseste un prag dat ca parametru:");
	Proiect* vect = (Proiect*)malloc(n * sizeof(Proiect));
	int nr = 0;
	float bugetMinim = 4000.5;
	salvareInVector2(tabela, vect, &nr, bugetMinim);
	for (int i = 0; i < nr; i++) {
		printf("\nCod: %u Titlu: %s Beneficiar: %s Nr Executanti: %u Buget: %5.2f",
			vect[i].cod, vect[i].titlu, vect[i].beneficiar, vect[i].nrExecutanti, vect[i].buget);
	}
	for (int i = 0; i < nr; i++) {
		free(vect[i].titlu);
		free(vect[i].beneficiar);
	}
	free(vect);


	dezalocareHash(tabela);
}