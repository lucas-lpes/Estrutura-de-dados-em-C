#include <stdio.h>
#include <stdlib.h>
#define tam 4

// O grafo será representado como um vetor de lista
typedef struct lista
{
    int destino;
    int custo;
    struct lista *prox;
} lista;

void inicializar(lista **l, int n)
{
    for (int i = 0; i <= n; i++)
    {
        l[i] = NULL;
    }
}

lista *InserirLista(lista *l, int destino, int custo) // A inserção acontece no começo da lista
{
    lista *novo = (lista *)malloc(sizeof(lista));
    novo->destino = destino;
    novo->custo = custo;
    novo->prox = l;
    return novo;
}

void InserirAresta(lista **l, int origem, int destino, int custo)
{
    l[origem] = InserirLista(l[origem], destino, custo);
}

int Existe_na_lista(lista *l, int x)
{
    if (l == NULL)
        return 0;

    if (l->destino == x)
        return 1;
    else
        return Existe_na_lista(l->prox, x);
}

lista *remover_elemento(lista *l, int x)
{

    if (l == NULL)
    {
        return l;
    }
    else
    {
        if (l->destino == x)
        {
            lista *temp = l;
            l = l->prox;
            free(temp);
            return l;
        }
        else
        {
            l->prox = remover_elemento(l->prox, x);
        }
    }

    return l;
}

lista *RemoverLista(lista *l)
{
    if (l == NULL)
    {
        return l;
    }
    else
    {
        l->prox = RemoverLista(l->prox);
        free(l);
        l = NULL;
        return l;
    }
}

void RemoverAresta(lista **l, int origem, int destino)
{
    l[origem] = remover_elemento(l[origem], destino);
}

void ImprimirLista(lista *l)
{
    lista *t = l;
    for (t; t != NULL; t = t->prox)
    {
        printf("(%d, %d)", t->destino, t->custo);
    }
}

void ImprimirGrafo(lista **l, int n)
{
    puts("Grafo:");
    for (int i = 1; i <= n; i++)
    {
        printf("\n\t%d", i);
        ImprimirLista(l[i]);
    }
    printf("\n\n");
}

int Entrada(lista **l, int vertice, int n)
{
    int cont = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i != vertice)
        {
            lista *temp = l[i];
            while (temp != NULL)
            {
                if (temp->destino == vertice)
                {
                    cont++;
                    break;
                }
                temp = temp->prox;
            }
        }
        else
        {
            continue;
        }
    }
    return cont;
}

int Saida(lista **l, int vertice, int n)
{
    int cont = 0;

    lista *temp = l[vertice];
    while (temp != NULL)
    {

        cont++;
        temp = temp->prox;
    }

    return cont;
}

int VerificaCompleto(lista **l, int n) // Substitui "tam" por "n" para facilitar a visualização da fórmula n(n-1)
{
    int soma = 0;
    for (int i = 1; i <= n; i++)
    {
        soma += Saida(l, i, n);
    }
    if (soma == n * (n - 1))
        return 1;
    else
        return 0;
}

int existe(int *vet, int valor, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (vet[i] == valor)
            return 1;
    }
    return 0;
}

void caminhos(lista **l, int destino, int *vet, int pos)
{
    if (vet[pos - 1] == destino)
    {
        printf("\n");
        for (int i = 0; i < pos; i++)
            printf("%d%s", vet[i], i == pos - 1 ? "" : "->");

        printf("\n");
    }
    else
    {
        lista *p = l[vet[pos - 1]];
        while (p != NULL)
        {
            if (!existe(vet, p->destino, pos))
            {
                vet[pos] = p->destino;
                caminhos(l, destino, vet, pos + 1);
            }
            p = p->prox;
        }
    }
}

void caminhoCurto(lista **l, int destino, int *vet, int pos, int *menor, int *menorCaminho)
{
    if (vet[pos - 1] == destino)
    {
        if (pos < *menor)
        {
            *menor = pos;
            printf("\n");
            for (int i = 0; i < pos; i++)
                menorCaminho[i] = vet[i];
            printf("\n");
        }
    }
    else
    {
        lista *p = l[vet[pos - 1]];
        while (p != NULL)
        {
            if (!existe(vet, p->destino, pos))
            {
                vet[pos] = p->destino;
                caminhoCurto(l, destino, vet, pos + 1, menor, menorCaminho);
            }
            p = p->prox;
        }
    }
}

void caminhoBarato(lista **l, int destino, int *vet, int pos, int *maisBarato, int *custoMin, int custoAtual)
{
    if (vet[pos - 1] == destino)
    {
        if (custoAtual < *custoMin)
        {
            *custoMin = custoAtual;
            for (int i = 0; i < pos; i++)
                maisBarato[i] = vet[i];
        }
    }
    else
    {
        lista *p = l[vet[pos - 1]];
        while (p != NULL)
        {
            if (!existe(vet, p->destino, pos))
            {
                vet[pos] = p->destino;
                caminhoBarato(l, destino, vet, pos + 1, maisBarato, custoMin, &custoAtual);
            }
            p = p->prox;
        }
    }
}

int main()
{

    lista *grafo[tam]; // cada espaço é um vertice, como a posição 0 é inutilizada, esse grafo terá apenas 4 vértices
    inicializar(grafo, tam);
    int origem, destino, custo;

    while (1)
    {

        printf("1-Inserir Aresta\n2-Remover Arestaz\n3-Imprimir grafo\n4-Imprimir graus de entrada e saida\n5-Verifica se e completo\n");
        printf("6-Imprimir todos os caminhos ate um vertice\n7-Imprimir o menor caminho entre dois vertices\n8-Imprimir o caminho de menor custo entre dois vertices\n9-Sair\n");
        int opcao;
        printf("Opcao: ");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            printf("Em qual vertice deseja inserir? ");
            scanf("%d", &origem);
            printf("\n");
            printf("Pra onde ele vai apontar? ");
            scanf("%d", &destino);
            printf("\n");
            printf("Qual o custo da aresta? ");
            scanf("%d", &custo);
            InserirAresta(grafo, origem, destino, custo);
            printf("Aresta Inserida com sucesso!\n");
            break;

        case 2:
            printf("Qual a origem da aresta? ");
            scanf("%d", &origem);
            printf("Qual o destino da aresta? ");
            scanf("%d", &destino);
            RemoverAresta(grafo, origem, destino);
            break;

        case 3:
            ImprimirGrafo(grafo, tam);
            break;

        case 4:
            printf("Qual vertice deseja analisar?");
            scanf("%d", &origem);
            printf("\n");
            printf("Grau de entrada: %d\n", Entrada(grafo, origem, tam));
            printf("Grau de saida: %d\n", Saida(grafo, origem, tam));
            printf("\n");
            break;
        case 5:
            if (VerificaCompleto(grafo, tam))
                printf("Completo!\n");
            else
                printf("Nao e Completo\n");
            break;
        case 6:
            printf("Digite o vertice origem:");
            scanf("%d", &origem);
            printf("Digite o vertice destino:");
            scanf("%d", &destino);
            int vet[tam + 1];
            vet[0] = origem;
            printf("\nCaminhos do vértice %d até o vértice %d:\n", origem, destino);
            caminhos(grafo, destino, vet, 1);
            break;

        case 7:
            printf("Digite o vertice origem: ");
            scanf("%d", &origem);
            printf("Digite o vertice destino: ");
            scanf("%d", &destino);

            int melhorCaminho[tam + 1];
            int menor = tam + 1;

            vet[0] = origem;

            caminhoCurto(grafo, destino, vet, 1, &menor, melhorCaminho);

            printf("Menor caminho de %d ate %d: ", origem, destino);
            for (int i = 0; i < menor; i++)
                printf("%d%s", melhorCaminho[i], i == menor - 1 ? "" : "->");
            printf("\n");

            break;

        case 8:
            printf("Digite o vertice origem: ");
            scanf("%d", &origem);
            printf("Digite o vertice destino: ");
            scanf("%d", &destino);

            int maisBarato[tam + 1];
            int custoMin = 2147483647; // valor máximo de um int, grande o suficiente pra inicializar

            vet[0] = origem;

            caminhoBarato(grafo, destino, vet, 1, maisBarato, &custoMin, 0);

            printf("Caminho mais barato de %d ate %d: ", origem, destino);
            printf("Custo: %d", custoMin);
            for (int i = 0; i < tam; i++)
                printf("%d%s", maisBarato[i], i == tam - 1 ? "" : "->");
            printf("\n");

            break;

        default:
            for (int i = 0; i <= tam; i++)
            {
                grafo[i] = RemoverLista(grafo[i]);
            }
            printf("Saindo...\n");
            break;
        }
    }

    return 0;
}
