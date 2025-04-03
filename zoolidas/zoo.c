#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --------------------------
// DEFINI��ES E ESTRUTURAS
// --------------------------

typedef struct {
    char nome[100];
    char especie[100];
    int idade;
} ANIMAL;

typedef struct node {
    ANIMAL* data;
    struct node* next;
} LIST_NODE;

typedef LIST_NODE* LIST;

// --------------------------
// FUN��ES DE N� E LISTA
// --------------------------

LIST_NODE* NewNode(ANIMAL* data) {
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

int InsertAt(LIST* list, ANIMAL* data, int pos) {
    // Se a posi��o for negativa, � inv�lida ? n�o insere nada.
    if (pos < 0) return 0;

    // Cria um novo n� com os dados fornecidos.
    LIST_NODE* new_node = NewNode(data);

    // Se a cria��o do n� falhar (mem�ria insuficiente, etc), retorna 0.
    if (new_node == NULL) return 0;

    // Caso especial: inserir na cabe�a da lista (posi��o 0).
    if (pos == 0) {
        // O novo n� aponta para o antigo primeiro elemento.
        new_node->next = *list;

        // A lista agora come�a com o novo n�.
        *list = new_node;

        // Inser��o bem-sucedida.
        return 1;
    }

    // Ponteiro auxiliar que percorre a lista.
    LIST_NODE* atual = *list;

    // Avan�a at� o n� imediatamente antes da posi��o desejada.
    // i < pos - 1 porque queremos parar no n� anterior � posi��o de inser��o.
    for (int i = 0; i < pos - 1 && atual != NULL; i++) {
        atual = atual->next;
    }

    // Se 'atual' for NULL, ent�o a posi��o est� fora dos limites da lista.
    if (atual == NULL) {
        // Liberta o n� que foi criado, pois n�o ser� usado.
        DeleteNode(new_node);
        return 0;
    }

    // Liga o novo n� ao n� seguinte (que antes vinha depois de 'atual').
    new_node->next = atual->next;

    // Liga o n� anterior ('atual') ao novo n�.
    atual->next = new_node;

    // Inser��o foi bem-sucedida.
    return 1;
}


int RemoveAt(LIST* list, int pos) {
    if (*list == NULL || pos < 0)
        return 0;

    LIST_NODE* atual = *list;
    LIST_NODE* anterior = NULL;

    if (pos == 0) {
        *list = atual->next;
        DeleteNode(atual);
        return 1;
    }

    for (int i = 0; i < pos && atual != NULL; i++) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL)
        return 0;

    anterior->next = atual->next;
    DeleteNode(atual);
    return 1;
}

// --------------------------
// FUN��ES NOVAS PEDIDAS
// --------------------------

// Inserir no in�cio da lista
void InserirAnimalInicio(LIST* list) {
    char nome[100], especie[100];
    int idade;

    printf("\n--- Inserir no in�cio ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Esp�cie: ");
    scanf(" %[^\n]", especie);
    printf("Idade: ");
    scanf("%d", &idade);

    ANIMAL* novo = malloc(sizeof(ANIMAL));
    if (!novo) {
        printf("Erro de mem�ria.\n");
        return;
    }

    strcpy(novo->nome, nome);
    strcpy(novo->especie, especie);
    novo->idade = idade;

    if (InsertAt(list, novo, 0))
        printf("Animal inserido no in�cio com sucesso.\n");
    else {
        printf("Erro ao inserir.\n");
        free(novo);
    }
}

// Procurar animal por nome
void ProcurarAnimalPorNome(LIST list) {
    char nome[100];
    printf("\n--- Procurar Animal ---\n");
    printf("Nome a procurar: ");
    scanf(" %[^\n]", nome);

    while (list != NULL) {
        if (strcmp(list->data->nome, nome) == 0) {
            printf("Encontrado: %s (%s), %d anos\n",
                list->data->nome, list->data->especie, list->data->idade);
            return;
        }
        list = list->next;
    }

    printf("Animal n�o encontrado.\n");
}

// Remover animal por nome
void RemoverAnimalPorNome(LIST* list) {
    char nome[100];
    printf("\n--- Remover Animal por Nome ---\n");
    printf("Nome do animal a remover: ");
    scanf(" %[^\n]", nome);

    LIST_NODE* atual = *list;
    LIST_NODE* anterior = NULL;

    while (atual != NULL && strcmp(atual->data->nome, nome) != 0) {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL) {
        printf("Animal n�o encontrado.\n");
        return;
    }

    if (anterior == NULL)
        *list = atual->next;
    else
        anterior->next = atual->next;

    DeleteNode(atual);
    printf("Animal removido com sucesso.\n");
}

// --------------------------
// RESTO DAS FUN��ES
// --------------------------

void InserirAnimalNaPosicao(LIST* list) {
    char nome[100], especie[100];
    int idade, pos;

    printf("\n--- Inserir Animal em Posi��o ---\n");
    printf("Nome: ");
    scanf(" %[^\n]", nome);
    printf("Esp�cie: ");
    scanf(" %[^\n]", especie);
    printf("Idade: ");
    scanf("%d", &idade);
    printf("Posi��o: ");
    scanf("%d", &pos);

    ANIMAL* novo = malloc(sizeof(ANIMAL));
    if (!novo) {
        printf("Erro de mem�ria.\n");
        return;
    }

    strcpy(novo->nome, nome);
    strcpy(novo->especie, especie);
    novo->idade = idade;

    if (InsertAt(list, novo, pos))
        printf("Animal inserido com sucesso.\n");
    else {
        printf("Erro ao inserir.\n");
        free(novo);
    }
}

void RemoverAnimalNaPosicao(LIST* list) {
    int pos;
    printf("\n--- Remover por Posi��o ---\n");
    printf("Posi��o: ");
    scanf("%d", &pos);

    if (RemoveAt(list, pos))
        printf("Animal removido com sucesso.\n");
    else
        printf("Erro: posi��o inv�lida.\n");
}

void ImprimirLista(LIST list) {
    int i = 0;
    while (list != NULL) {
        printf("[%d] %s (%s), %d anos\n", i, list->data->nome, list->data->especie, list->data->idade);
        list = list->next;
        i++;
    }
}

int ReadAnimalsFromFile(LIST* list, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Erro ao abrir ficheiro");
        return 0;
    }

    char linha[300];
    int pos = 0;
    while (fgets(linha, sizeof(linha), fp)) {
        ANIMAL* a = malloc(sizeof(ANIMAL));
        if (!a) continue;

        linha[strcspn(linha, "\n")] = 0;

        if (sscanf(linha, "%[^;];%[^;];%d", a->nome, a->especie, &a->idade) == 3) {
            InsertAt(list, a, pos);
            pos++;
        }
        else {
            free(a);
        }
    }

    fclose(fp);
    return 1;
}

// --------------------------
// MAIN COM MENU
// --------------------------

int main() {
    LIST zoo = NULL;

    if (ReadAnimalsFromFile(&zoo, "animais.txt")) {
        printf("Animais carregados com sucesso.\n");
    }

    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Listar animais\n");
        printf("2. Inserir no in�cio\n");
        printf("3. Inserir em posi��o\n");
        printf("4. Remover por posi��o\n");
        printf("5. Remover por nome\n");
        printf("6. Procurar por nome\n");
        printf("0. Sair\n");
        printf("Op��o: ");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1: ImprimirLista(zoo); break;
        case 2: InserirAnimalInicio(&zoo); break;
        case 3: InserirAnimalNaPosicao(&zoo); break;
        case 4: RemoverAnimalNaPosicao(&zoo); break;
        case 5: RemoverAnimalPorNome(&zoo); break;
        case 6: ProcurarAnimalPorNome(zoo); break;
        case 0: printf("A sair...\n"); break;
        default: printf("Op��o inv�lida.\n");
        }
    } while (opcao != 0);

    FreeList(&zoo);
    return 0;
}
