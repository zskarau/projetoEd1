#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

Produto *alocar(int codigo, char nome[], char categoria[], int quantidade){
    Produto *novo = NULL;
    novo = (Produto *)malloc(sizeof(Produto));
    if(novo){
        novo->codigo = codigo;
        strcpy(novo->nome, nome);
        strcpy(novo->categoria, categoria);
        novo->quantidade = quantidade;
        novo->prox = NULL;
    }
    return novo;
}

void inserirProduto(Produto **p, int codigo, char nome[], int quantidade, char categoria[]){
    Produto *aux = NULL;
    aux = alocar(codigo, nome, categoria, quantidade);
    if(aux){
        aux->prox = *p;
        *p = aux;
    }
}

void imprimir(Produto *p){
    Produto *aux = p;
    if(!aux) printf("Lista vazia\n");
    else{
        while(aux){
            printf("Cod: %d Nome: %s Qntd: %d Cat: %s\n", aux->codigo, aux->nome, aux->quantidade, aux->categoria);
            aux = aux->prox;
        }
    }
}

void carregar_estoque(char *tipo_arquivo, Produto **p){
    FILE *arquivo = fopen(tipo_arquivo, "r");
    if(!arquivo) printf("Não foi possível abrir o arquivo.");
    else{
        int codigo, quantidade;
        char nome[20], categoria[20];
        while(fscanf(arquivo, "%d%s%d%s", &codigo, nome, &quantidade, categoria) != EOF){
            inserirProduto(p, codigo, nome, quantidade, categoria);
        }
    }
}