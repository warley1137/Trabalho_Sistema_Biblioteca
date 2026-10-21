#include <stdio.h>
#include <string.h>

#define MAX_LIVROS 3
#define MAX_USUARIOS 3
#define TAM_TEXTO 121

typedef struct {
    int codigo;
    char descricao[TAM_TEXTO];
    int estoque;
} Livro;

typedef struct {
    int codigo;
    char dados[TAM_TEXTO];
    int codigoLivroEmprestado;
} Usuario;

void lerTexto(char texto[], int tamanho);
int cadastrarLivro(Livro livros[], int qtdLivros);
int cadastrarUsuario(Usuario usuarios[], int qtdUsuarios);
void listarLivros(Livro livros[], int qtdLivros);
void listarUsuarios(Usuario usuarios[], int qtdUsuarios);
int buscarLivro(Livro livros[], int qtdLivros, int codigoBuscado);
int calcularQtdExemplares(Livro livros[], int qtdLivros);
int disponibilidadeLivro(int qtdEstoque);

int main(void) {
    Livro livros[MAX_LIVROS];
    Usuario usuarios[MAX_USUARIOS];
    int qtdLivros = 0;
    int qtdUsuarios = 0;

    while (qtdLivros < MAX_LIVROS) {
        qtdLivros = cadastrarLivro(livros, qtdLivros);
    }

    while (qtdUsuarios < MAX_USUARIOS) {
        qtdUsuarios = cadastrarUsuario(usuarios, qtdUsuarios);
    }

    listarLivros(livros, qtdLivros);

    int qtdExemplares = calcularQtdExemplares(livros, qtdLivros);
    printf("Total de exemplares no acervo: %d\n", qtdExemplares);

    listarUsuarios(usuarios, qtdUsuarios);

    char consulta = 'S';
    int codigoBusca;

    while (consulta == 'S' || consulta == 's') {
        printf("\nDigite o codigo do livro que deseja buscar: ");
        scanf("%d", &codigoBusca);

        int posBusca = buscarLivro(livros, qtdLivros, codigoBusca);

        if (posBusca == -1) {
            printf("Livro nao encontrado no acervo.\n");
        } else {
            printf("Codigo: %d\n", livros[posBusca].codigo);
            printf("Descricao: %s\n", livros[posBusca].descricao);
            printf("Estoque: %d\n", livros[posBusca].estoque);

            if (disponibilidadeLivro(livros[posBusca].estoque) == 1) {
                printf("Livro disponivel.\n");
            } else {
                printf("Livro temporariamente indisponivel.\n");
            }
        }

        printf("Deseja continuar buscando? (S ou N): ");
        scanf(" %c", &consulta);
    }

    return 0;
}

void lerTexto(char texto[], int tamanho) {
    do {
        fgets(texto, tamanho, stdin);
        texto[strcspn(texto, "\n")] = '\0';

        if (strlen(texto) == 0) {
            printf("Texto invalido: nao pode ficar vazio. Digite novamente: ");
        }
    } while (strlen(texto) == 0);
}

int cadastrarLivro(Livro livros[], int qtdLivros) {
    Livro novo;
    int repetido;
    int c;

    printf("\nCadastro do livro %d de %d\n", qtdLivros + 1, MAX_LIVROS);

    do {
        printf("Digite o codigo do livro: ");
        scanf("%d", &novo.codigo);

        repetido = 0;
        for (int i = 0; i < qtdLivros; i++) {
            if (livros[i].codigo == novo.codigo) {
                repetido = 1;
                break;
            }
        }

        if (novo.codigo < 0) {
            printf("Codigo invalido: nao pode ser negativo.\n");
        } else if (repetido) {
            printf("Codigo invalido: ja cadastrado.\n");
        }

    } while (novo.codigo < 0 || repetido);

    do {
        printf("Digite a quantidade em estoque: ");
        scanf("%d", &novo.estoque);

        if (novo.estoque < 0) {
            printf("Estoque invalido: nao pode ser negativo.\n");
        }
    } while (novo.estoque < 0);

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    printf("Digite titulo; autor; ano; tema (max. 120 caracteres):\n");
    lerTexto(novo.descricao, TAM_TEXTO);

    livros[qtdLivros] = novo;

    return qtdLivros + 1;
}

int cadastrarUsuario(Usuario usuarios[], int qtdUsuarios) {
    Usuario novo;
    int repetido;
    int c;

    printf("\nCadastro do usuario %d de %d\n", qtdUsuarios + 1, MAX_USUARIOS);

    do {
        printf("Digite o codigo do usuario: ");
        scanf("%d", &novo.codigo);

        repetido = 0;
        for (int i = 0; i < qtdUsuarios; i++) {
            if (usuarios[i].codigo == novo.codigo) {
                repetido = 1;
                break;
            }
        }

        if (novo.codigo <= 0) {
            printf("Codigo invalido: deve ser maior que zero.\n");
        } else if (repetido) {
            printf("Codigo invalido: ja cadastrado.\n");
        }

    } while (novo.codigo <= 0 || repetido);

    while ((c = getchar()) != '\n' && c != EOF) {
    }

    printf("Digite os dados do usuario (nome; contato; etc., max. 120 caracteres):\n");
    lerTexto(novo.dados, TAM_TEXTO);

    novo.codigoLivroEmprestado = -1;

    usuarios[qtdUsuarios] = novo;

    return qtdUsuarios + 1;
}

void listarLivros(Livro livros[], int qtdLivros) {
    printf("\n--- Listagem do acervo ---\n");
    for (int i = 0; i < qtdLivros; i++) {
        printf("Codigo: %d | %s | Estoque: %d\n",
               livros[i].codigo, livros[i].descricao, livros[i].estoque);
    }
}

void listarUsuarios(Usuario usuarios[], int qtdUsuarios) {
    printf("\n--- Listagem de usuarios ---\n");
    for (int i = 0; i < qtdUsuarios; i++) {
        printf("Codigo: %d | %s | Livro emprestado: %d\n",
               usuarios[i].codigo, usuarios[i].dados, usuarios[i].codigoLivroEmprestado);
    }
}

int buscarLivro(Livro livros[], int qtdLivros, int codigoBuscado) {
    for (int i = 0; i < qtdLivros; i++) {
        if (livros[i].codigo == codigoBuscado) {
            return i;
        }
    }
    return -1;
}

int calcularQtdExemplares(Livro livros[], int qtdLivros) {
    int qtdExemplares = 0;

    for (int i = 0; i < qtdLivros; i++) {
        qtdExemplares += livros[i].estoque;
    }
    return qtdExemplares;
}

int disponibilidadeLivro(int qtdEstoque) {
    if (qtdEstoque > 0) {
        return 1;
    }
    return 0;
}
