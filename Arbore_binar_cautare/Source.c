#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
//ARBORE BINAR DE CAUTARE
typedef struct Autor Autor;
typedef struct Carte Carte;
typedef struct node node;
struct Autor {
	char* name;
	int age;
};

struct Carte {
	int id;
	Autor autor;
	int noPages;
};

//structura pentru un nod din arbore
struct node {
	Carte info;
	node* right;
	node* left;
};

node* initNode(Carte info, node* left, node* right) {
	node* newNode = (node*)malloc(sizeof(node));
	newNode->info = info; //shallow copy
	newNode->left = left;
	newNode->right = right;

	return newNode;
}

Carte readCarte(FILE* f) {
	Carte b;
	fscanf_s(f, "%d", &b.id);
	char buffer[20]; //citesc in buffer
	fscanf_s(f, "%s", buffer);
	b.autor.name = (char*)malloc(sizeof(char) * (strlen(buffer) + 1));
	strcpy(b.autor.name, buffer); //nu e necesar pentru ca e pointer
	fscanf(f, "%d", &b.autor.age);
	fscanf(f, "%d", &b.noPages);

	return b;
}

//pentru inserare am nev de cartea pe care o inserez si de radacina arborelui, adica de arbore
node* insertTree(Carte book, node* root) {
	//compar unde trebuie sa pun cartea
	if (root) {
		if (book.id < root->info.id)
		{
			root->left = insertTree(book, root->left);
			return root;
		}
		else {
			root->right = insertTree(book, root->right);
			return root;
		}
	}
	else {
		return initNode(book, NULL, NULL); //nodul devine radacina pentru ca nu exista radacina
	}
}

void printCarte(Carte b) {
	printf("%d. Carte written by %s has %d pages. %d\n", b.id, b.autor.name, b.noPages, b.autor.age);
}

void printTree(node* root) {
	if (root) {
		//in ordine
		printTree(root->left); //arborele din stanga 
		printCarte(root->info); //radacina
		printTree(root->right); //arborele din dreapta
	}
}

//cautare dupa id
Carte findCarteById(node* root, int id) {
	if (root) {
		//verific daca radacina e elementul pe care il caut
		if (root->info.id == id) {
			return root->info;
		}
		else {
			//verific daca id-ul e mai mic decat id-ul radacinii => atunci m-as duce in stanga
			if (root->info.id > id) {
				return findCarteById(root->left, id);
			}
			else {
				return findCarteById(root->right, id);
			}
		}
	}
	else {
		Carte b;
		b.id = -1;
		b.autor.age = -1;
		b.autor.name = NULL;
		b.noPages = -1;

		return b;
	}
}

int height(node* root) {
	if (root) {
		int hleft = height(root->left);
		int hright = height(root->right);
		return 1 + (hleft > hright ? hleft : hright);
	}
	else {
		return 0;
	}
}

//afisare a nodurilor de pe un anumit nivel pe care il dau eu ca param
void afisareDePeNivel(node* root, int nivelDorit, int nivelCurent) {
	if (root) {
		if (nivelDorit == nivelCurent) {
			printCarte(root->info);
		}
		else {
			afisareDePeNivel(root->left, nivelDorit, nivelCurent + 1);
			afisareDePeNivel(root->right, nivelDorit, nivelCurent + 1);
		}
	}
}

//stergere dintr-un arbore de facut -> atunci cand sterg radacina trebuie sa schimb locul pentru radacina

void main() {
	FILE* f = fopen("books.txt", "r");
	//am nevoie de radacina pentru arbore
	node* root = NULL;

	int noCartes = 0;
	fscanf(f, "%d", &noCartes);
	for (int i = 0; i < noCartes; i++) {
		root = insertTree(readCarte(f), root);
	}

	printTree(root);

	printf("\n\n");
	printCarte(findCarteById(root, 8));

	int heightTree = height(root);
	printf("\nInaltimea arborelui este: %d\n", heightTree);

	afisareDePeNivel(root, 3, 1);
	system("pause");
}