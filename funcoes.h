#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

typedef struct produto{
    int codigo;     
    char nome[30];
    char categoria[30];    
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

Produto *alocar(int codigo, char nome[], char categoria[], int quantidade);
void inserirProduto(Produto **p, int codigo, char nome[], int quantidade, char categoria[]);
void imprimir(Produto *p);
void carregar_estoque(char *tipo_arquivo, Produto **p);
void carregar_historico(char *tipo_arquivo, Produto **p);
void processar_pedidos(char *tipo_arquivo, Produto **p)

#endif