#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	char nome[100];
	int idade;
	char morada[100];
	char profisao[100];
} PESSOA;

typedef struct node {
	PESSOA* data;
	struct node* next;
} LIST_NODE;

typedef LIST_NODE* LIST;

// --------------------------

// FUNÇÕES DE NÓ E LISTA

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
int Inserir(LIST* list, PESSOA* data, int pos) {

	if (pos < 0) return 0;

	LIST_NODE* new_node = NewNode(data);

	if (new_node == NULL) return 0;

	if (pos == 0) {
		new_node->next = *list;
		return 1;
	}

	LIST_NODE* atual = *list;

	for (int i = 0; i < pos - 1 && atual != NULL; i++) {
		atual = atual->next;
	}

	if (atual == NULL) {
		free(new_node);
		return 0;

		new_node->next = atual->next;
		atual->next = new_node;
	}
}
int remover(LIST * list, int pos) {

		if (pos < 0) return 0;

		LIST_NODE* atual = *list;
		LIST_NODE* anterior = NULL;


		if (pos == 0) {
			*list = atual->next;
			return 1;
		}

		for (int i = 0; i < pos && atual != NULL; i++) {

			anterior = atual;
			atual = atual->next;
		}

		if (atual == NULL) {
			return 0;
		}

		anterior->next = atual->next;
}


void addpessoa(LIST* list) {
	
	int pos, idade;
	char nome[100], morada[100], profisao[100];
	PESSOA* nova = malloc(sizeof(PESSOA));

	if ( !nova) {
		printf("Erro ao alocar memória.\n");
		return;
	}

	printf("Nome: ");
	scanf(" %[^\n]", nova->nome);
	printf("Idade: ");
	scanf("%d", &nova->idade);
	printf("Morada: ");
	scanf(" %[^\n]", nova->morada);
	printf("Profissão: ");
	scanf(" %[^\n]", nova->profisao);
	printf(" Em que possiçao quer adicionar ? ");
	scanf("%d", &pos);

	strcpy(nova->nome, nome);
	nova->idade = idade;
	strcpy(nova->morada, morada);
	strcpy(nova->profisao, profisao);

	if (Inserir(list, nova, pos))
		printf("Pessoa inserida com sucesso.\n");
	else {
		printf("Erro ao inserir.\n");
		free(nova);
	}

}

void removerpessoa(LIST* list) {
	int pos;

	printf("Qual a posição que quer remover ? ");
	scanf("%d", &pos);

	if (remover(list, pos)
		)
		printf("Pessoa removida com sucesso.\n");
	else
		printf("Erro: posição inválida.\n");

	
}

void procurarpessoa(LIST list)
{
	char nome[100];
	printf("Qual o nome da pessoa que quer procurar ? ");
	scanf(" %[^\n]", nome);

	while(list != NULL) {
		if (strcomp(nome, list->data->nome) == 0 ) {
			printf("Nome: %s\n", list->data->nome);
			printf("Idade: %d\n", list->data->idade);
			printf("Morada: %s\n", list->data->morada);
			printf("Profissão: %s\n", list->data->profisao);
			return;
		}
		list = list->next;

	}
	printf("Pessoa não encontrada.\n");
}
void imprimir(LIST list) {
	int i = 0;
	while (list != NULL) {
		printf("[%d] %s (%d anos), %s, %s\n", i, list->data->nome, list->data->idade, list->data->morada, list->data->profisao);
		list = list->next;
		i++;
	}
}

int main() {












}