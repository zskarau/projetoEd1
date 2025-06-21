#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

Produto *alocarProduto(int codigo, char nome[], char categoria[], int quantidade){
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

void insereProduto(Produto **p, int codigo, char nome[], int quantidade, char categoria[]){
    Produto *aux = NULL;
    aux = alocarProduto(codigo, nome, categoria, quantidade);
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

        fclose(arquivo);
        printf("Estoque Carregado!\n");
    }
}

HistoricoVendas *alocarHistorico(int codigo, int vendas[]){
//laço para alocar o historico usando for, pq e necessário um vetor de 4 inteiros nas vendas
    int i;
    HistoricoVendas *novo = NULL;
    novo = (HistoricoVendas *)malloc(sizeof(HistoricoVendas));

    if(novo){
        novo->codigo = codigo;

        for(i = 0; i < 4; i++){
            novo->vendas[i] = vendas[i];
        }
        novo->prox = NULL;
    }

    return novo;
}

void insereHistorico(HistoricoVendas **hv, int codigo, int vendas[]){
//insere o historico na lista
    HistoricoVendas *aux = NULL;

    aux = alocarHistorico(codigo, vendas);

    if(aux){
        aux->prox = *hv;
        *hv = aux;
    }
}

void carregar_historico(char *tipo_arquivo, HistoricoVendas **hv){
//carrega o historico em um laço e coloca dentro da lista 
    FILE *arquivo = fopen(tipo_arquivo, "r");

    if(!arquivo){
        printf("Não foi possível abrir o arquivo.");
    }

    else{
        int codigo, vendas[4];

        while(fscanf(arquivo, "%d%d%d%d%d", &codigo, &vendas[0], &vendas[1], &vendas[2], &vendas[3]) != EOF){
            insereHistorico(hv, codigo, vendas);
        }

        fclose(arquivo);
        printf("Historico Carregado!\n");
    }
}

void imprimirHistorico(HistoricoVendas *hv){
//imprime o historico de vendas
    HistoricoVendas *temp = hv;

    if(temp == NULL){
        printf("\nLista vazia\n");
        return;
    }

    while(temp){
        printf("Codigo: %d Venda 1: %d Venda 2: %d Venda 3: %d Venda 4: %d\n", temp->codigo, temp->vendas[0], temp->vendas[1], temp->vendas[2], temp->vendas[3]);
        temp = temp->prox;
    }
}

Cliente *alocarCliente(int id_cliente, char nome[]){
    
    Cliente *cl = NULL;
    cl = (Cliente *)malloc(sizeof(Cliente));

    if(cl){
        cl->id_cliente = id_cliente;
        strcpy(cl->nome, nome);
        cl->pedidos = NULL;
        cl->prox = NULL;
    }

    return cl;
}

void insereCliente(Cliente **cl, int id_cliente, char nome[], int id_pedido, int id_codigo_produto, int quantidade){

    Cliente *novo = buscarCliente(*cl, id_cliente, nome);

    if(!novo){
        novo = alocarCliente(id_cliente, nome);
        novo->prox = *cl;
        *cl = novo;
    }

    inserePedido(&(novo->pedidos), id_pedido, id_codigo_produto, quantidade);

}

Cliente *buscarCliente(Cliente *cl, int id_cliente, char nome[]){

    while(cl){
        if(cl->id_cliente == id_cliente && !strcmp(cl->nome, nome)){
            return cl;
        }
        cl = cl->prox;
    }
    return NULL;
}

Pedido *alocarPedido(int id_pedido){

    Pedido *novoP = NULL;
    novoP = (Pedido *)malloc(sizeof(Pedido));

    if(novoP){
        
        novoP->id_pedido = id_pedido;
        novoP->itens = NULL;
        novoP->prox = NULL;
    }

    return novoP;
}

void inserePedido(Pedido **pedidos, int id_pedido, int id_codigo_produto, int quantidade){

    Pedido *aux = *pedidos;

    while(aux){
    
        if(aux->id_pedido == id_pedido){
            insereItens(&(aux->itens), id_codigo_produto, quantidade);
            return;
        }

        aux = aux->prox;
    }

    Pedido *novo = NULL;
    novo = alocarPedido(id_pedido);
    
    if(novo){
        novo->prox = *pedidos;
        *pedidos = novo;
    }

}

PedidoItem *alocarItens(int codigo_produto, int quantidade){
    
    PedidoItem *novoPI = NULL;
    novoPI = (PedidoItem *)malloc(sizeof(PedidoItem));

    if(novoPI){
        
        novoPI->codigo_produto = codigo_produto;
        novoPI->quantidade = quantidade;
        novoPI->prox = NULL;
    }

    return novoPI;
}

void insereItens(PedidoItem **pedidoitem, int codigo_produto, int quantidade){
    
    PedidoItem *novo = NULL;
    novo = alocarItens(codigo_produto, quantidade);
    
    if(novo){
        novo->prox = *pedidoitem;
        *pedidoitem = novo;
    }

}

void carregar_clientes_pedidos(char *tipo_arquivo, Cliente **cl){
    FILE *arquivo = fopen(tipo_arquivo, "r");

    if(!arquivo){
        printf("Não foi possível abrir o arquivo.");
    }

    else{
        int id_cliente, id_pedido, id_codigo_produto, quantidade;
        char nome[30];

        while(fscanf(arquivo, "%d%s%d%d%d", &id_cliente, nome, &id_pedido, &id_codigo_produto, &quantidade) != EOF){
            
            insereCliente(cl, id_cliente, nome, id_pedido, id_codigo_produto, quantidade);

        }

        fclose(arquivo);
        printf("Historico Carregado!\n");
    }
}

void processar_pedidos(Produto *p, Cliente *cl){
    
}

void prever_compras(HistoricoVendas *hv){
//prever compra de cada codigo de produto do historico de vendas usando while
    HistoricoVendas *temp = hv;
    float mediavendas = 0;

    if(temp == NULL){

        printf("\nNenhum historico de vendas encontrado.\n");
        return;
    }

    while(temp){

        mediavendas = (temp->vendas[0] + temp->vendas[1] + temp->vendas[2] + temp->vendas[3]) / 4.0;
        printf("Produto %d - Media = %.2f unidades vendidas\n", temp->codigo, mediavendas);
        temp = temp->prox;
    }
}