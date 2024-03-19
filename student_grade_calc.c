#include <stdio.h>
#include <string.h>

#define NOTA_CORTE 7.0
#define DIVISOR_MEDIA 2.0
#define NOME_STATUS_APROVADO "Aprovado"
#define NOME_STATUS_REPROVADO "Reprovado"

typedef struct Aluno {
    int id;
    char nome[50];
    float nota_trabalho;
    float nota_prova;
    float media;
    char status[10];
} Aluno;

void ler_dados(Aluno*, const int);
void mostrar_resultado(const Aluno*, const int);

int main() {
    int qtd_alunos;

    printf("Bem vindo ao calculador de média. \n\n");

    printf("Por favor, informe a quantidade de alunos: ");
    scanf("%d", &qtd_alunos);

    Aluno* alunos = malloc(qtd_alunos * sizeof(Aluno));

    printf("\nAgora, digite os dados dos alunos: \n\n");

    ler_dados(alunos, qtd_alunos);

    printf("\nResultado final\n\n");

    mostrar_resultado(alunos, qtd_alunos);

    printf("\n\n");

    free(alunos);

    return 0;
}

void ler_dados(Aluno* alunos, const int qtd_alunos) {
    printf("----------------------------------\n");
    for (int i = 0; i < qtd_alunos; i++) {
        const int id = i + 1;
        Aluno aluno;

        aluno.id = id;

        printf("Nome do aluno ...%d: ", id);
        scanf("%s", aluno.nome);

        printf("Nota do Trabalho %d: ", id);
        scanf("%f", &aluno.nota_trabalho);

        printf("Nota da Prova ...%d: ", id);
        scanf("%f", &aluno.nota_prova);

        aluno.media = (aluno.nota_trabalho + aluno.nota_prova) / DIVISOR_MEDIA;
        strcpy(aluno.status, (aluno.media >= NOTA_CORTE) ? NOME_STATUS_APROVADO : NOME_STATUS_REPROVADO);

        memcpy(&alunos[i], &aluno, sizeof aluno);

        printf("----------------------------------\n");
    }
}

void mostrar_resultado(const Aluno* alunos, const int qtd_alunos) {
    printf("+-------------------------------------------------------------+\n");
    printf("|ID  |Nome                |Nota P1 |Nota P2 |Media |Status    |\n");
    printf("+-------------------------------------------------------------+\n");
    for (int i = 0; i < qtd_alunos; i++) {
        printf("|%-4d|%-20s|%-8.1f|%-8.1f|%-6.1f|%-10s|\n", 
            alunos[i].id, alunos[i].nome, alunos[i].nota_trabalho, 
            alunos[i].nota_prova, alunos[i].media, alunos[i].status);
    }
    printf("+-------------------------------------------------------------+\n");
}