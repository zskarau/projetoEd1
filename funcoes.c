#include <stdio.h>
#include "funcoes.h"

typedef struct produto{
    int codigo;     
    char nome[30];     
    int quantidade;     
    float precos[3];     
    struct produto *prox;     
}Produto;  
 
typedef struct historico{    
    int codigo;     
    int vendas[4];     
    struct historico *prox; 
}HistoricoVendas;  

typedef struct pedidoitem{     
    int codigo_produto;    
    int quantidade;     
    struct pedidoitem *prox; 
}PedidoItem; 

typedef struct Pedido{ 
    int id_pedido; 
    PedidoItem *itens; 
    struct Pedido *prox; 
}Pedido; 

typedef struct Cliente{ 
    int id_cliente; 
    char nome[30]; 
    Pedido *pedidos; 
    struct Cliente *prox; 
}Cliente; 

void carregar_estoque(char *tipo_arquivo){
    FILE *arquivo = fopen(tipo_arquivo, "r");
    if(!arquivo) printf("Não foi possível abrir o arquivo.");
    else{
        int cod, qntd;
        char nome[20], cat[20];
        while(fscanf(arquivo, "%d%s%d%s", &cod, nome, &qntd, cat) != EOF){
            printf("Cod: %d Nome: %s Qntd: %d Cat: %s\n", cod, nome, qntd, cat);
        }
    }
}

void carregar_precos(char *tipo_arquivo){
    FILE *arquivo = fopen(tipo_arquivo, "r");
    if(!arquivo) printf("Não foi possível abrir o arquivo.");
    else{
        int cod;
        float preco1, preco2, preco3;
        while(fscanf(arquivo, "%d%f%f%f", &cod, &preco1, &preco2, &preco3) != EOF){
            printf("Cod: %d Preco1: %.2f Preco2: %.2f Preco3: %.2f\n", cod, preco1, preco2, preco3);
        }
    }
}