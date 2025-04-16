#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define size 10

typedef struct
{
    int matricula;
    char nome[100];
    char curso[100];
    bool disponivel;
} aluno;

int hash(int x)
{
    return x % size;
}

void inicializar(char *nome)
{
    FILE *arq = fopen(nome, "rb+");
    if (arq == NULL)
    {
        arq = fopen(nome, "wb+");
        aluno temp;
        temp.disponivel = true;
        for (int i = 0; i < size; i++)
            fwrite(&temp, sizeof(aluno), 1, arq);
    }
    fclose(arq);
}

int achar_posicao(char *file, int x)
{
    int pos = hash(x);
    aluno a;
    FILE *arq = fopen(file, "rb+");
    fseek(arq, pos * sizeof(aluno), SEEK_SET);
    fread(&a, sizeof(aluno), 1, arq);
    while (a.disponivel != true)
    {
        pos = (pos + 1) % size;
        fseek(arq, pos * sizeof(aluno), SEEK_SET);
        fread(&a, sizeof(aluno), 1, arq);
    }
    fclose(arq);
    return pos;
}

void inserir(char *file, int mat, char *name, char *course)
{
    FILE *arq = fopen(file, "rb+");
    int pos = achar_posicao(file, mat);
    aluno a;
    a.disponivel = false;
    a.matricula = mat;
    strcpy(a.nome, name);
    strcpy(a.curso, course);
    fseek(arq, pos * sizeof(aluno), SEEK_SET);
    fwrite(&a, sizeof(aluno), 1, arq);
    fclose(arq);
}

void imprimirAluno(char *file, int mat)
{
    FILE *arq = fopen(file, "rb");
    int pos = achar_posicao(file, mat);
    fseek(arq, pos * sizeof(aluno), SEEK_SET);
    aluno temp;
    fread(&temp, sizeof(aluno), 1, arq);
    printf("\nMatricula:%d\nNome:%s\nCurso:%s\n", temp.matricula, temp.nome, temp.curso);
    fclose(arq);
}

void imprimir_tabela(char *file)
{
    FILE *arq = fopen(file, "rb");
    aluno temp;
    while (fread(&temp, sizeof(aluno), 1, arq))
    {
        if (!temp.disponivel)
            printf("\nMatricula:%d\nNome:%s\nCurso:%s\n", temp.matricula, temp.nome, temp.curso);
    }
    fclose(arq);
}

int main()
{
    int opcao;
    char arqv[20];
    printf("Digite o nome do arquivo a ser lido:");
    scanf("%s", arqv);
    inicializar(arqv);

    while (1)
    {
        printf("Bem vindo!\n1-Inserir um novo aluno\n2-Buscar um aluno\n3-Visualizar a tabela completa\n4-Sair\n");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            int mat;
            char nome[100], curso[100];
            printf("Digite a matricula do aluno:");
            scanf("%d", &mat);
            getchar();
            printf("Digite o nome do aluno:");
            fgets(nome, sizeof(nome), stdin);
            nome[strlen(nome) - 1] = '\0';
            printf("Digite o curso do aluno:");
            fgets(curso, sizeof(curso), stdin);
            curso[strlen(curso) - 1] = '\0';
            inserir(arqv, mat, nome, curso);
        }
        if (opcao == 2)
        {
            int mat;
            printf("Digite a matricula do aluno:");
            scanf("%d", &mat);
            imprimirAluno(arqv, mat);
        }
        if (opcao == 3)
            imprimir_tabela(arqv);

        if (opcao >= 4)
            break;
    }
    return 0;
}
