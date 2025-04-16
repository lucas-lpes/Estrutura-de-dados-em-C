#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<assert.h>
#include<math.h>

typedef struct arvore{
    int data;
    struct arvore* esq;
    struct arvore* dir;
}arvore;

arvore* ler_arvore(FILE* f){
    char c;
    int dado;

    fscanf(f,"%c",&c);
    fscanf(f,"%d",&dado);

    if(dado == -1){
        fscanf(f,"%c",&c);
        return NULL;
    }else{
        arvore* a = (arvore*)malloc(sizeof(arvore));
        a->data = dado;
        a->esq = ler_arvore(f);
        a->dir = ler_arvore(f);
        fscanf(f,"%c",&c);
        return a;
    }

}


void pre_ordem(arvore* a){
    if(a!=NULL){
        printf("%d ",a->data);
        pre_ordem(a->esq);
        pre_ordem(a->dir);
    }

}


void em_ordem(arvore* a){
    if(a!=NULL){
        em_ordem(a->esq);
        printf("%d ",a->data);
        em_ordem(a->dir);
    }

}


void pos_ordem(arvore* a){
    if(a!=NULL){
        pos_ordem(a->esq);
        pos_ordem(a->dir);
        printf("%d ",a->data);
    }

}


void imprimir_nivel(arvore* a, int cont, int n){
    if(a!=NULL){
        if(cont == n){
            printf("%d ",a->data);
        }
        imprimir_nivel(a->esq,cont+1,n);
        imprimir_nivel(a->dir,cont+1,n);
    }


}

void imprimir_largura(arvore* a){
    int n = descobrir_altura(a);
    for(int i=0;i<n;i++){
        printf("Nivel %d: ",i);
        imprimir_nivel(a,0,i);
        printf("\n");
    }
}


int descobrir_altura(arvore* a){
    if(a == NULL){
        return 0;
    }
    else{
         int he = descobrir_altura(a->esq);
         int hd = descobrir_altura(a->dir);
         if(he>hd)
            return he+1;
         else
            return hd+1;
    }
}


void imprimir(arvore* a){
    int opcao;
    if(a==NULL){
        puts("A �rvore est� vazia\n");
        return;
    }
    while(1){
        puts("Escolha uma forma de impress�o\n1-Pr�-ordem\n2-Em-ordem\n3-P�s-ordem\n4-Em Largura\n5-Voltar ao Menu\n");
        scanf("%d",&opcao);
        if(opcao == 1){
            printf("Pre-ordem: ");
            pre_ordem(a);
            printf("\n\n");
        }
        if(opcao == 2){
            printf("Em-ordem: ");
            em_ordem(a);
            printf("\n\n");
        }
        if(opcao == 3){
            printf("P�s-ordem: ");
            pos_ordem(a);
            printf("\n\n");
        }
        if(opcao == 4){
            imprimir_largura(a);
            puts("\n");
        }
        if(opcao == 5)
            break;
    }
}


int busca_elemento(arvore* a, int x){
    int aux;
    if(a==NULL){
        return 0;
    }
    else{
        if(a->data == x){
            return 1;
        }else{
            aux = busca_elemento(a->esq,x);
        }
        if(aux == 0){
            aux = busca_elemento(a->dir,x);
        }
    }
    return aux;
}


int contar_elementos(arvore* a){
    if(a!=NULL){
        return 1 + contar_elementos(a->esq) + contar_elementos(a->dir);
    }
    else{
        return 0;
    }

}


void imprimir_folhas(arvore* a){
    if(a == NULL){
        return;
    }
    if(a->esq == NULL && a->dir == NULL){
        printf("%d ",a->data);
    }else{
        imprimir_folhas(a->esq);
        imprimir_folhas(a->dir);
    }
}

void free_arvore(arvore*a){
    if(a!= NULL){
        free_arvore(a->esq);
        free_arvore(a->dir);
        free(a);
    }

}


int Nivel_No(arvore* a, int y,int n){
    int z = n;
    if(a == NULL){
        return -1;
    }else{
        if(a->data == y){
            return n;
        }else{
            n = Nivel_No(a->esq,y,z+1);
        }
        if(n==-1)
            n = Nivel_No(a->dir,y,z+1);
    }

    return n;
}


void esta_cheia(arvore* a, int niveis){
    int aux = contar_elementos(a);

    if(aux == pow(2,niveis)-1){
        puts("A �rvore est� cheia\n");
    }else{
        puts("A �rvore N�O est� cheia\n");
    }

}

int main(){
    setlocale(LC_ALL,"Portuguese");
    int opcao;
    arvore* a = NULL;
    while(1){
        puts("Bem-vindo ao menu, escolha dentre as op��es:\n1-Ler um arquivo de �rvore\n2-Imprimir a �rvore\n3-Buscar um elemento\n4-Contar elementos\n5-Imprimir apenas n�s 'folhas'\n6-Verificar se est� balanceada\n"
             "7-Verificar se est� cheia\n8-Imprimir o nivel que um dado elemento se encontra\n9-Sair\n");

        scanf("%d",&opcao);
    if(opcao == 1){
        const char s[20];
        printf("Insira o nome do arquivo a ser lido: ");
        scanf("%s",&s);
        printf("\n");
        FILE* f = fopen(s,"rt");
        assert(f!=NULL);
        a = ler_arvore(f);
        fclose(f);
    }
    if(opcao == 2){
        imprimir(a);
    }
    if(opcao == 3){
        int x;
        puts("Qual elemento deseja buscar?");
        scanf("%d",&x);
        printf("\n");
        int temp = busca_elemento(a,x);
        if(temp == 1)
            printf("Elemento encontrado na �rvore\n\n");
        else
            printf("Elemento N�O encontrado na �rvore\n\n");
    }
    if(opcao == 4){
        int cont = contar_elementos(a);
        printf("Essa �rvore possui %d elementos\n",cont);
        printf("\n");
    }
    if(opcao == 5){
        printf("N�s 'folhas': ");
        imprimir_folhas(a);
        puts("\n");
    }
    if(opcao == 6){
        int aux1, aux2;
        aux1 = descobrir_altura(a->esq);
        aux2 = descobrir_altura(a->dir);
        if(abs(aux1-aux2)>1)
            puts("A �rvore N�O est� balanceada\n");
        else
            puts("A �rvore est� balanceada\n");
    }
    if(opcao == 7){
        int niveis = descobrir_altura(a);
        esta_cheia(a,niveis);

    }
    if(opcao == 8){
        int y;
        printf("Insira o elemento que deseja buscar: ");
        scanf("%d",&y);
        printf("\n");
        int n = Nivel_No(a,y,0);
        if(n == -1){
            puts("ERRO: Elemento n�o encontrado na �rvore\n");
        }else
            printf("O elemento se encontra no nivel %d da �rvore\n\n",n);
    }
    if(opcao == 9){
        free_arvore(a);
        break;
    }

    }
    puts("\n");
    puts("Obrigado por utilizar o menu, espero que tenha gostado!\n");

    return 0;
}
