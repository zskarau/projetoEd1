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

//carregar estoque
Produto *alocarProduto(int codigo, char nome[], char categoria[], int quantidade);
void insereProduto(Produto **p, int codigo, char nome[], int quantidade, char categoria[]);
void imprimeEstoque(Produto *p);
void carregar_estoque(char *tipo_arquivo, Produto **p);

//carregar historico
HistoricoVendas *alocarHistorico(int codigo, int vendas[]);
void insereHistorico(HistoricoVendas **hv, int codigo, int vendas[]);
void carregar_historico(char *tipo_arquivo, HistoricoVendas **hv);
void imprimeHistorico(HistoricoVendas *hv);

//carregar pedidos
Cliente *alocarCliente(int id_cliente, char nome[]);
Pedido *alocarPedidos(int id_pedido);
PedidoItem *alocarItens(int codigo_produto, int quantidade);
void insereCliente(Cliente **cl, int id_cliente, char nome[], int id_pedido, int id_codigo_produto, int quantidade, Produto *estoque);
void inserePedido(Pedido **pedidos, int id_pedido, int id_codigo_produto, int quantidade, Produto *estoque);
void insereItens(PedidoItem **pedidoitem, int codigo_produto, int quantidade, Produto *estoque);
void carregar_clientes_pedidos(char *tipo_arquivo, Cliente **cl, Produto *estoque);
void imprimeClientes(Cliente *cl);
Produto *processar_pedidos(int codigo_produto, Produto *estoque);

void prever_compras(HistoricoVendas *hv);

#endif