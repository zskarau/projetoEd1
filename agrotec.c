#include <stdio.h>
#include <stdlib.h>
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

int main(){
    ler_arquivo("estoque.txt");
}