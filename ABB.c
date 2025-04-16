#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <assert.h>

typedef struct arvore
{
    int data;
    struct arvore *esq;
    struct arvore *dir;
    char cor;
} arvore;

arvore *ler_arvore(FILE *f)
{
    char c;
    int dado;

    fscanf(f, "%c", &c);
    fscanf(f, "%d", &dado);

    if (dado == -1)
    {
        fscanf(f, "%c", &c);
        return NULL;
    }
    else
    {
        char z = c;
        arvore *a = (arvore *)malloc(sizeof(arvore));
        a->data = dado;
        a->esq = ler_arvore(f);
        a->dir = ler_arvore(f);
        a->cor = z;
        fscanf(f, "%c", &c);
        return a;
    }
}

void pre_ordem(arvore *a)
{
    if (a != NULL)
    {
        printf("%d (%c)", a->data, a->cor);
        pre_ordem(a->esq);
        pre_ordem(a->dir);
    }
}

void em_ordem(arvore *a)
{
    if (a != NULL)
    {
        em_ordem(a->esq);
        printf("%d ", a->data);
        em_ordem(a->dir);
    }
}

void pos_ordem(arvore *a)
{

    if (a != NULL)
    {
        pos_ordem(a->esq);
        pos_ordem(a->dir);
        printf("%d ", a->data);
    }
}

int descobrir_altura(arvore *a)
{
    if (a == NULL)
    {
        return 0;
    }
    else
    {
        int he = 1 + descobrir_altura(a->esq);
        int hd = 1 + descobrir_altura(a->dir);

        if (he > hd)
        {
            return he;
        }
        return hd;
    }
}

void imprimir_nivel(arvore *a, int cont, int nivel)
{
    if (a != NULL)
    {
        if (cont == nivel)
        {
            printf("%d ", a->data);
        }
        else
        {
            imprimir_nivel(a->esq, cont + 1, nivel);
            imprimir_nivel(a->dir, cont + 1, nivel);
        }
    }
}

void imprimir_largura(arvore *a)
{
    for (int i = 0; i < descobrir_altura(a); i++)
    {
        printf("Nivel [%d]: ", i);
        imprimir_nivel(a, 0, i);
        printf("\n");
    }
}

void imprimir(arvore *a)
{
    int opcao;
    if (a == NULL)
    {
        puts("A árvore está vazia\n");
        return;
    }
    while (1)
    {
        puts("Escolha uma forma de impressão\n1-Pré-ordem\n2-Em-ordem\n3-Pós-ordem\n4-Em Largura\n5-Voltar ao Menu\n");
        scanf("%d", &opcao);
        if (opcao == 1)
        {
            printf("Pre-ordem: ");
            pre_ordem(a);
            printf("\n\n");
        }
        if (opcao == 2)
        {
            printf("Em-ordem: ");
            em_ordem(a);
            printf("\n\n");
        }
        if (opcao == 3)
        {
            printf("Pós-ordem: ");
            pos_ordem(a);
            printf("\n\n");
        }
        if (opcao == 4)
        {
            imprimir_largura(a);
            puts("\n");
        }
        if (opcao == 5)
            break;
    }
}

int verifica(arvore *a, int x)
{
    if (a == NULL)
        return 0;

    if (a->data == x)
        return 1;

    if (x <= a->data)
        verifica(a->esq, x);
    else
        verifica(a->dir, x);
}

int buscar_nivel(arvore *a, int x)
{
    int temp = 0;
    if (x != a->data)
    {
        if (x < a->data)
            temp = 1 + buscar_nivel(a->esq, x);
        else
            temp = 1 + buscar_nivel(a->dir, x);
    }
    if (a == NULL)
        return 0;

    return temp;
}

void imprimir_folha_menor(arvore *a, int x)
{
    if (a != NULL)
    {
        if (a->esq == NULL && a->dir == NULL)
        {
            if (a->data < x)
                printf("%d ", a->data);
        }
        else
        {
            if (a->data > x)
                imprimir_folha_menor(a->esq, x);
            else
            {
                imprimir_folha_menor(a->esq, x);
                imprimir_folha_menor(a->dir, x);
            }
        }
    }
}

arvore *inserir_no(arvore *a, int x)
{
    if (a == NULL)
    {
        arvore *novo = (arvore *)malloc(sizeof(arvore));
        novo->data = x;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    }
    if (x < a->data)
        a->esq = inserir_no(a->esq, x);
    else
        a->dir = inserir_no(a->dir, x);
    return a;
}

arvore *remover_no(arvore *a, int x)
{
    if (a != NULL)
    {
        if (a->data == x)
        {
            if (a->esq == NULL && a->dir == NULL)
            {
                free(a);
                return NULL;
            }
            else
            {
                if (a->esq == NULL)
                {
                    arvore *temp = a->dir;
                    free(a);
                    return temp;
                }
                if (a->dir == NULL)
                {
                    arvore *temp = a->esq;
                    free(a);
                    return temp;
                }
                else
                {
                    arvore *temp = a->esq;
                    while (temp->dir != NULL)
                        temp = temp->dir;
                    a->data = temp->data;
                    a->esq = remover_no(a->esq, temp->data);
                }
            }
        }
        else
        {
            if (x < a->data)
                a->esq = remover_no(a->esq, x);
            else
                a->dir = remover_no(a->dir, x);
        }
        return a;
    }
}

void free_arvore(arvore *a)
{
    if (a != NULL)
    {
        free_arvore(a->esq);
        free_arvore(a->dir);
        free(a);
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int x;
    int opcao;
    arvore *a = NULL;
    while (1)
    {
        puts("Bem-vindo ao menu, escolha dentre as opções:\n1-Ler um arquivo de árvore\n2-Imprimir a árvore\n3-Verificar se um elemento existe\n4-Imprimir o nivel de um elemento\n"
             "5-Imprimir 'folhas' menores que um valor x\n6-Inserir um elemento\n7-Remover um elemento\n8-Sair\n");

        scanf("%d", &opcao);
        if (opcao == 1)
        {
            const char s[20];
            printf("Insira o nome do arquivo a ser lido: ");
            scanf("%s", &s);
            printf("\n");
            FILE *f = fopen(s, "rt");
            assert(f != NULL);
            a = ler_arvore(f);
            printf("Arquivo lido com sucesso!\n\n");
            fclose(f);
        }
        if (opcao == 2)
        {
            imprimir(a);
        }
        if (opcao == 3)
        {
            puts("Qual elemento deseja verificar?");
            scanf("%d", &x);
            printf("\n");
            int temp = verifica(a, x);
            if (temp == 1)
                printf("Elemento existe na árvore\n\n");
            else
                printf("Elemento NÂO existe na árvore\n\n");
        }
        if (opcao == 4)
        {
            printf("Insira o elemento que deseja buscar: ");
            scanf("%d", &x);
            if (verifica(a, x) == 1)
                printf("Elemento se encontra no nivel: %d\n", buscar_nivel(a, x));
            else
                puts("Elemento não existe na árvore\n");
        }
        if (opcao == 5)
        {
            printf("Insira o valor(inteiro) que deseja filtrar: ");
            scanf("%d", &x);
            printf("Nós 'folhas' menores que %d: ", x);
            imprimir_folha_menor(a, x);
            puts("\n");
        }
        if (opcao == 6)
        {
            printf("Digite o elemento que deseja inserir: ");
            scanf("%d", &x);
            a = inserir_no(a, x);
            puts("Elemento inserido com sucesso!\n");
        }
        if (opcao == 7)
        {
            printf("Digite o elemento que deseja remover: ");
            scanf("%d", &x);
            if (verifica(a, x) == 1)
            {
                a = remover_no(a, x);
                puts("Elemento removido com sucesso!\n");
            }
            else
            {
                puts("Este elemento não se encontra na árvore\n");
            }
        }
        if (opcao == 8)
        {
            free_arvore(a);
            break;
        }
    }
    puts("\n");
    puts("Obrigado por utilizar o menu, espero que tenha gostado!\n");

    return 0;
}
