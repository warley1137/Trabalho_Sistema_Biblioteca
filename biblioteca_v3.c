#include <stdio.h>
#include <string.h>

#define MAX_TITULOS 3
#define TAM_TEXTO 121

int cadastrarTitulo(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
);

void listarTitulos(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
);

int buscarTitulo(
    int codigos[],
    int qtdTitulos,
    int codigoBuscado
);

int calcularQtdExemplares(
    int estoques[],
    int qtdTitulos
);

int disponibilidadeTitulo(
    int qtdEstoque
);

int main(void) {
    int codigos[MAX_TITULOS] = {0};
    int estoques[MAX_TITULOS] = {0};
    int qtdTitulos = 0;

    char descricao1[TAM_TEXTO];
    char descricao2[TAM_TEXTO];
    char descricao3[TAM_TEXTO];

    while (qtdTitulos < MAX_TITULOS) {
        qtdTitulos = cadastrarTitulo(
            codigos,
            estoques,
            descricao1,
            descricao2,
            descricao3,
            qtdTitulos
        );
    }

    listarTitulos(
        codigos,
        estoques,
        descricao1,
        descricao2,
        descricao3,
        qtdTitulos
    );

    int qtdExemplares = calcularQtdExemplares(estoques, qtdTitulos);
    printf("Total de exemplares no acervo: %d\n", qtdExemplares);

    char consulta = 'S';
    int codigoBusca;

    while (consulta == 'S' || consulta == 's') {
        printf("\nDigite o codigo do titulo que deseja buscar: ");
        scanf("%d", &codigoBusca);

        int posBusca = buscarTitulo(codigos, qtdTitulos, codigoBusca);

        if (posBusca == -1) {
            printf("Titulo nao encontrado no acervo.\n");
        } else {
            if (posBusca == 0) {
                printf("Descricao: %s\n", descricao1);
            } else if (posBusca == 1) {
                printf("Descricao: %s\n", descricao2);
            } else {
                printf("Descricao: %s\n", descricao3);
            }

            int disponivel = disponibilidadeTitulo(estoques[posBusca]);

            if (disponivel == 1) {
                printf("Titulo disponivel. Quantidade em estoque: %d\n", estoques[posBusca]);
            } else {
                printf("Titulo encontrado, porem temporariamente indisponivel.\n");
            }
        }

        printf("Deseja continuar buscando? (S ou N): ");
        scanf(" %c", &consulta);
    }

    return 0;
}

int cadastrarTitulo(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
) {
    int novoCodigo;
    int novoEstoque;
    int repetido;
    int c;
    char descricaoTemp[TAM_TEXTO];

    printf("\nCadastro do titulo %d de %d\n", qtdTitulos + 1, MAX_TITULOS);

    do {
        printf("Digite o codigo do titulo: ");
        scanf("%d", &novoCodigo);

        repetido = 0;
        for (int i = 0; i < qtdTitulos; i++) {
            if (codigos[i] == novoCodigo) {
                repetido = 1;
                break;
            }
        }

        if (novoCodigo < 0) {
            printf("Codigo invalido: nao pode ser negativo.\n");
        } else if (repetido) {
            printf("Codigo invalido: ja cadastrado.\n");
        }

    } while (novoCodigo < 0 || repetido);

    do {
        printf("Digite a quantidade em estoque: ");
        scanf("%d", &novoEstoque);

        if (novoEstoque < 0) {
            printf("Estoque invalido: nao pode ser negativo.\n");
        }
    } while (novoEstoque < 0);

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    do {
        printf("Digite titulo; autor; ano; tema (max. 120 caracteres):\n");
        fgets(descricaoTemp, TAM_TEXTO, stdin);
        descricaoTemp[strcspn(descricaoTemp, "\n")] = '\0';

        if (strlen(descricaoTemp) == 0) {
            printf("Descricao invalida: nao pode ficar vazia.\n");
        }
    } while (strlen(descricaoTemp) == 0);

    codigos[qtdTitulos] = novoCodigo;
    estoques[qtdTitulos] = novoEstoque;

    if (qtdTitulos == 0) {
        strcpy(descricao1, descricaoTemp);
    } else if (qtdTitulos == 1) {
        strcpy(descricao2, descricaoTemp);
    } else {
        strcpy(descricao3, descricaoTemp);
    }

    return qtdTitulos + 1;
}

void listarTitulos(
    int codigos[],
    int estoques[],
    char descricao1[],
    char descricao2[],
    char descricao3[],
    int qtdTitulos
) {
    printf("\n--- Listagem do acervo ---\n");
    for (int i = 0; i < qtdTitulos; i++) {
        if (i == 0) {
            printf("Codigo: %d | %s | Estoque: %d\n", codigos[i], descricao1, estoques[i]);
        } else if (i == 1) {
            printf("Codigo: %d | %s | Estoque: %d\n", codigos[i], descricao2, estoques[i]);
        } else {
            printf("Codigo: %d | %s | Estoque: %d\n", codigos[i], descricao3, estoques[i]);
        }
    }
}

int buscarTitulo(
    int codigos[],
    int qtdTitulos,
    int codigoBuscado
) {
    for (int i = 0; i < qtdTitulos; i++) {
        if (codigos[i] == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

int calcularQtdExemplares(
    int estoques[],
    int qtdTitulos
) {
    int qtdExemplares = 0;

    for (int i = 0; i < qtdTitulos; i++) {
        qtdExemplares += estoques[i];
    }
    return qtdExemplares;
}

int disponibilidadeTitulo(
    int qtdEstoque
) {
    if (qtdEstoque > 0) {
        return 1;
    }
    return 0;
}
