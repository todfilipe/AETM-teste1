#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  cadeira_{
	char nome[100];
	int media;
	char curso[100];
} CADEIRA;

typedef struct node {
	CADEIRA* data;
	struct node* next;
} LIST_NODE;

typedef LIST_NODE* LIST;

LIST_NODE* NewNode(PESSOA* data) {
	LIST_NODE* new_node = malloc(sizeof(LIST_NODE));
	if (new_node != NULL) {
		new_node->data = data;
		new_node->next = NULL;
	}
	return new_node;
}

void DeleteNode(LIST_NODE* node) {
	if (node != NULL) {
		free(node->data);
		free(node);
	}
}

void FreeList(LIST* list) {
	LIST_NODE* atual;
	while (*list != NULL) {
		atual = *list;
		*list = (*list)->next;
		DeleteNode(atual);
	}
}

	int adicionar(LIST* list, CADEIRA* data, int posi) {

		if (posi < 0)
			printf("posicao errado");
			return 0;

		LIST_NODE* new_node = NewNode(data);


		if (posi == 0) { new_node->next = *list;
			return 1;}
			

			LIST_NODE* atual = *list;

			for (int i = 0; i < posi - 1; && atual != NULL; i++) {
				atual = atual_next;
			}

			new_node->next = atual->next;
			atual->next = new_node;

			return 1;

	}

	int retirar(LIST* list, CADEIRA* data, int posi) {

		if (posi < 0) return 0;

		LIST_NODE* atual = list*;
		LIST_NODE* antes = NULL;

		if (posi == 0)
			*list = atual->next;

		return 1;

		for (int i = 0; i < posi && atual != NULL; i++) {

			antes = atual;
			atual->next = atual;

		}

		antes->next = atual->next
	}

	void adicionarcadeira(LIST* list) {

		char nome, curso;
		int media, posi;

		CADEIRA* nova = malloc(sizeof(CADEIRA));
		printf("Nome da cadeira ");
		scanf("%[^\n]", nova->nome);
		printf("media");
		scanf("%d", &nova->media);
		printf("curso");
		scanf("%[^\n]", nova->curso);
		printf(" Em que possiçao quer adicionar ? ");
		scanf("%d", &posi);

		strcpy(nova->nome, nome);
		strcpy(nova->curso, curso);
		nova->media = media;

		if (adicionar(list, nova, posi)) {printf("top");}
				
		else {
			printf("Erro ao inserir.\n");
			free(nova);
		}

	}