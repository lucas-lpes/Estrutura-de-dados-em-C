#include <stdio.h>
#include <stdlib.h>
int elementos = 0;

int indice_pai(int i)
{
    if (i <= 0 || i >= elementos)
        return -1;
    return (i - 1) / 2;
}

int indice_filhoesq(int i)
{
    int indice = 2 * i + 1;
    if (i >= elementos || indice >= elementos)
        return -1;
    return indice;
}

int indice_filhodir(int i)
{
    int indice = 2 * i + 2;
    if (i >= elementos || indice >= elementos)
        return -1;
    return indice;
}

void imprimir(int *heap)
{

    for (int i = 0; i < elementos; i++)
    {
        if (i == elementos - 1)
            printf("%d", heap[i]);
        else
            printf("%d|", heap[i]);
    }
    puts("");
}

void ajustar_subindo(int *heap, int indice)
{
    if (indice != -1)
    {
        int pai = indice_pai(indice);
        if (pai != -1)
        {
            if (heap[indice] > heap[pai])
            {
                int aux = heap[indice];
                heap[indice] = heap[pai];
                heap[pai] = aux;
                ajustar_subindo(heap, pai);
            }
        }
    }
}

void inserir(int *heap, int x)
{
    heap[elementos] = x;
    elementos++;
    ajustar_subindo(heap, elementos - 1);
}

void ajustar_descendo(int *heap, int indice)
{
    if (indice != -1 && indice_filhoesq(indice) != -1)
    {
        int menor = indice_filhoesq(indice);
        if (indice_filhodir(indice) != -1 && heap[indice_filhodir(indice)] < heap[menor])
        {
            menor = indice_filhodir(indice);
        }
        if (heap[indice] < heap[menor])
        {
            int aux = heap[indice];
            heap[indice] = heap[menor];
            heap[menor] = aux;
            imprimir(heap);
            printf("\n");
            ajustar_descendo(heap, menor);
        }
    }
}

int remover(int *heap)
{
    if (elementos == 0)
    {
        return -1;
    }
    imprimir(heap);
    printf("\n");
    int temp = heap[0];
    heap[0] = heap[elementos - 1];
    elementos--;
    imprimir(heap);
    printf("\n");
    ajustar_descendo(heap, 0);
    return temp;
}

int main()
{
    int c;
    int heap[100];
    int opcao;
    while (1)
    {
        puts("1-Inserir na heap\n2-Remover da heap\n3-Imprimir Heap\n4-Sair");
        printf("Opcao: ");
        scanf("%d", &opcao);
        printf("\n");
        if (opcao == 1)
        {
            puts("Qual valor deseja inserir?");
            int x;
            scanf("%d", &x);
            inserir(heap, x);
        }
        if (opcao == 2)
        {
            c = remover(heap);
            if (c == -1)
                printf("A heap esta vazia!\n");
            else
                printf("Item removido:%d\n", c);
        }
        if (opcao == 3)
            imprimir(heap);
        if (opcao == 4)
            break;
    }

    return 0;
}