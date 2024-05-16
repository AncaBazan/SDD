#include<stdio.h>
#include<malloc.h>
#include<string.h>

// Heap - coada de prioritati

typedef struct Email Email;
typedef struct Heap Heap;

struct Email
{
    char* subiect;
    int prioritate;
};

struct Heap
{
    Email* emailuri;
    int dim;
    int dimMaxima;
};

void afisareInfo(Heap h)
{
    for (int i = 0; i < h.dim; i++)
    {
        printf("Emailul cu subiectul %s are prioritatea %d.\n", h.emailuri[i].subiect, h.emailuri[i].prioritate);
    }
}

void filtrareHeap(Heap h, int index)
{
    if (h.dim)
    {
        int iS = 2 * index + 1;
        int iD = 2 * index + 2;
        int iMax = index;


        if (iS < h.dim && h.emailuri[iMax].prioritate < h.emailuri[iS].prioritate)
        {
            iMax = iS;
        }
        if (iD < h.dim && h.emailuri[iMax].prioritate < h.emailuri[iD].prioritate)
        {
            iMax = iD;
        }


        if (iMax != index)
        {
            Email aux = h.emailuri[index];
            h.emailuri[index] = h.emailuri[iMax];
            h.emailuri[iMax] = aux;

            if (iMax < h.dim / 2 - 1)
            {
                filtrareHeap(h, iMax);
            }
        }
    }
}

void initializareHeap(Heap* h, int dimMaxima)
{
    h->dim = 0;
    h->dimMaxima = dimMaxima;
    h->emailuri = (Email*)malloc(sizeof(Email) * dimMaxima);
}

void adaugareEmail(Heap* h, char* subiect, int prioritate)
{
    if (h->dim < h->dimMaxima)
    {
        h->emailuri[h->dim].subiect = _strdup(subiect);
        h->emailuri[h->dim].prioritate = prioritate;
        h->dim++;
    }
}

Email* extragereHeap(Heap* h)
{
    if (h->dim == 0)
        return NULL;

    Email* e = (Email*)malloc(sizeof(Email));
    e->prioritate = h->emailuri[0].prioritate;
    e->subiect = _strdup(h->emailuri[0].subiect);

    Email aux = h->emailuri[0];
    h->emailuri[0] = h->emailuri[h->dim - 1];
    h->dim--;

    filtrareHeap(*h, 0);

    return e;
}

void afisareEmail(Email e)
{
    printf("Emailul cu subiectul %s are prioritatea %d.\n", e.subiect, e.prioritate);
}

void afisareHeapAscuns(Heap h)
{
    for (int i = 0; i < h.dimMaxima; i++)
    {
        printf("Emailul cu subiectul %s are prioritatea %d.\n", h.emailuri[i].subiect, h.emailuri[i].prioritate);
    }
}

void dezalocareEmail(Email* e)
{
    free(e->subiect);
    free(e);
}

void dezalocareHeap(Heap* h)
{
    for (int i = 0; i < h->dim; i++)
    {
        free(h->emailuri[i].subiect);
    }
    free(h->emailuri);
    h->dim = 0;
    h->dimMaxima = 0;
}

int main()
{
    Heap h;
    initializareHeap(&h, 6);

    adaugareEmail(&h, "Mihai", 3);
    adaugareEmail(&h, "Andreea", 6);
    adaugareEmail(&h, "Denisa", 2);
    adaugareEmail(&h, "Anca", 1);
    adaugareEmail(&h, "Alexandra", 4);
    adaugareEmail(&h, "Roxana", 5);

    afisareInfo(h);

    for (int i = h.dim / 2 - 1; i >= 0; i--)
    {
        filtrareHeap(h, i);
    }

    printf("\n\n");
    afisareInfo(h);

    while (h.dim)
    {
        Email* e = extragereHeap(&h);
        if (e != NULL)
        {
            afisareEmail(*e);
            dezalocareEmail(e);
        }
    }

    printf("\n\n");
    afisareHeapAscuns(h);

    dezalocareHeap(&h);

    return 0;
}
