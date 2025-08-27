#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 5 // Tamanho máximo da fila

typedef enum { I, O, T, L } TipoPeca;

typedef struct {
    TipoPeca tipo;
    int id;
} Peca;

typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

int contador_id = 0;

// Inicializa a fila com valores padrão
void inicializaFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;      // Início e fim começam no mesmo ponto
    f->total = 0;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Gera uma nova peça aleatória
Peca gerarPeca() {
    return (Peca){ .tipo = rand() % 4, .id = contador_id++ };
}

// Insere uma peça na fila
int inserir(Fila *f, Peca p) {
    if (filaCheia(f)) return 0;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX;
    f->total++;
    return 1;
}

// Remove uma peça da fila
int remover(Fila *f, Peca *removida) {
    if (filaVazia(f)) return 0;
    *removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
    return 1;
}

// Converte enum para caractere
char tipoParaChar(TipoPeca tipo) {
    const char nomes[] = { 'I', 'O', 'T', 'L' };
    return nomes[tipo];
}

// Mostra a fila
void mostrarFila(const Fila *f) {
    printf("\nFila de peças:\n");
    if (filaVazia(f)) {
        printf("[Vazia]\n");
        return;
    }
    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c %d] ", tipoParaChar(f->itens[idx].tipo), f->itens[idx].id);
    }
    printf("\n");
}

// Mostra o menu
void mostrarMenu() {
    printf("\nOpções:\n");
    printf("1 - Jogar peça\n");
    printf("2 - Inserir nova peça\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

int main() {
    Fila fila;
    int opcao;
    Peca p;

    srand((unsigned)time(NULL));
    inicializarFila(&fila);

    for (int i = 0; i < MAX; i++) {
        inserir(&fila, gerarPeca());
    }

    do {
        mostrarFila(&fila);
        mostrarMenu();
        if (scanf("%d", &opcao) != 1) break;

        switch (opcao) {
            case 1:
                if (remover(&fila, &p))
                    printf("Peça jogada: [%c %d]\n", tipoParaChar(p.tipo), p.id);
                else
                    printf("Fila vazia.\n");
                break;

            case 2:
                p = gerarPeca();
                if (inserir(&fila, p))
                    printf("Peça inserida: [%c %d]\n", tipoParaChar(p.tipo), p.id);
                else
                    printf("Fila cheia.\n");
                break;

            case 0:
                printf("Encerrando...\n");
                break;

            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
