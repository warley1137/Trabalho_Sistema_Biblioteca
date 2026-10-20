#include <stdio.h>

#define MAX_TITULOS 3

int main(void) {
    int codigos[MAX_TITULOS] = {0};
    int estoques[MAX_TITULOS] = {0};
    int qtdTitulos = 0;


    while (qtdTitulos < MAX_TITULOS) {
        int novoCodigo;
        int repetido;
        int i;

        printf("\nCadastro do titulo %d de %d\n", qtdTitulos + 1, MAX_TITULOS);

        do {
            printf("Digite o codigo do titulo: ");
            scanf("%d", &novoCodigo);

            repetido = 0;
            for (i = 0; i < qtdTitulos; i++) {
                if (codigos[i] == novoCodigo) {
                    repetido = 1;
                }
            }

            if (novoCodigo < 0) {
                printf("Codigo invalido: nao pode ser negativo.\n");
            } else if (repetido) {
                printf("Codigo invalido: ja cadastrado.\n");
            }

        } while (novoCodigo < 0 || repetido);

        codigos[qtdTitulos] = novoCodigo;

        int novoEstoque;
        do {
            printf("Digite a quantidade em estoque: ");
            scanf("%d", &novoEstoque);

            if (novoEstoque < 0) {
                printf("Estoque invalido: nao pode ser negativo.\n");
            }
        } while (novoEstoque < 0);

        estoques[qtdTitulos] = novoEstoque;

        qtdTitulos++;
    }


    int qtdExemplares = 0;

    printf("\n--- Listagem do acervo ---\n");
    for (int i = 0; i < qtdTitulos; i++) {
        printf("Codigo: %d | Estoque: %d\n", codigos[i], estoques[i]);
        qtdExemplares += estoques[i];
    }
    printf("Total de exemplares no acervo: %d\n", qtdExemplares);


char consulta = 'S';
int codigoBusca;

while (consulta == 'S' || consulta == 's') {
    printf("\nDigite o codigo do titulo que deseja buscar: ");
    scanf("%d", &codigoBusca);

    int posBusca = -1;
    for (int i = 0; i < qtdTitulos; i++) {
        if (codigos[i] == codigoBusca) {
            posBusca = i;
        }
    }

    if (posBusca == -1) {
        printf("Titulo nao encontrado no acervo.\n");
    } else {
        if (estoques[posBusca] == 0) {
            printf("Titulo encontrado, porem temporariamente indisponivel.\n");
        } else {
            printf("Titulo disponivel. Quantidade em estoque: %d\n", estoques[posBusca]);
        }
    }

    printf("Deseja continuar buscando? (S ou N):");
    scanf(" %c", &consulta);
}

    return 0;
}
