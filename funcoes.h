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

//Estoque
Produto *alocarProduto(int codigo, char nome[], char categoria[], int quantidade);
Produto *buscarProduto(Produto *p, int codigo);
void insereProduto(Produto **p, int codigo, char nome[], int quantidade, char categoria[]);
void imprimeEstoque(Produto *p);
void carregar_estoque(char *tipo_arquivo, Produto **p);
int atualizar_estoque(Produto *estoque, int codigo_produto, int quantidade);
void carregar_precos(char *tipo_arquivo, Produto *estoque);

//Historico Vendas
HistoricoVendas *alocarHistorico(int codigo, int vendas[]);
void insereHistorico(HistoricoVendas **hv, int codigo, int vendas[]);
void carregar_historico(char *tipo_arquivo, HistoricoVendas **hv);
void imprimeHistorico(HistoricoVendas *hv);

//Clientes, Pedidos e Itens de Pedidos
Cliente *alocarCliente(int id_cliente, char nome[]);
Pedido *alocarPedidos(int id_pedido);
PedidoItem *alocarItens(int codigo_produto, int quantidade);
void insereCliente(Cliente **cl, int id_cliente, char nome[], int id_pedido, int id_codigo_produto, int quantidade, Produto *estoque);
void inserePedido(Pedido **pedidos, int id_pedido, int id_codigo_produto, int quantidade, Produto *estoque);
void insereItens(PedidoItem **pedidoitem, int codigo_produto, int quantidade, Produto *estoque);
void carregar_clientes_pedidos(char *tipo_arquivo, Cliente **cl, Produto *estoque);
Cliente *buscarCliente(Cliente *cl, int id_cliente);
void imprimeClientes(Cliente *cl);
void processar_pedidos(Cliente *cl, Produto *p);

//Funcoes Extras
void prever_compras(HistoricoVendas *hv);
void relatorioFinal(Produto *p, HistoricoVendas *hv);
void liberarEstoque(Produto **estoque);
void liberarHistorico(HistoricoVendas **hv);
void liberarClientes(Cliente **cl);
void liberarPedidosItens(PedidoItem *itens);
void liberarPedidos(Pedido *pedidos);
float funcaoMediaVendas(HistoricoVendas *hv);
float funcaoMediaPrecos(Produto *estoque);

#endif