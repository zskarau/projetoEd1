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

void imprimeEstoque(Produto *p){

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
            insereProduto(p, codigo, nome, quantidade, categoria);
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

void imprimeHistorico(HistoricoVendas *hv){
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

Cliente *buscarCliente(Cliente *cl, int id_cliente, char nome[]){

    while(cl){
        if(cl->id_cliente == id_cliente && !strcmp(cl->nome, nome)){
            return cl;
        }
        cl = cl->prox;
    }
    return NULL;
}

void insereCliente(Cliente **cl, int id_cliente, char nome[], int id_pedido, int id_codigo_produto, int quantidade, Produto *estoque){

    Cliente *novo = buscarCliente(*cl, id_cliente, nome);

    if(!novo){
        novo = alocarCliente(id_cliente, nome);
        novo->prox = *cl;
        *cl = novo;
    }

    inserePedido(&(novo->pedidos), id_pedido, id_codigo_produto, quantidade, estoque);

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

void inserePedido(Pedido **pedidos, int id_pedido, int id_codigo_produto, int quantidade, Produto *estoque){

    Pedido *aux = *pedidos;

    while(aux){
    
        if(aux->id_pedido == id_pedido){
            insereItens(&(aux->itens), id_codigo_produto, quantidade, estoque);
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

    insereItens(&(novo->itens), id_codigo_produto, quantidade, estoque);
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

void insereItens(PedidoItem **pedidoItem, int codigo_produto, int quantidade, Produto *estoque){

    Produto *aux = processar_pedidos(codigo_produto, estoque);

    if(!aux){
        printf("Produto Não Encontrado!\n");
        return;
    }

    if(aux->quantidade < quantidade){
        printf("Quantidade em Estoque Não Suficente!\n");
        return;
    }

    PedidoItem *novo = NULL;
    novo = alocarItens(codigo_produto, quantidade);
    
    if(novo){
        novo->prox = *pedidoItem;
        *pedidoItem = novo;
        aux->quantidade -= quantidade;
    }
}

void carregar_clientes_pedidos(char *tipo_arquivo, Cliente **cl, Produto *estoque){
    FILE *arquivo = fopen(tipo_arquivo, "r");

    if(!arquivo){
        printf("Não foi possível abrir o arquivo.\n");
        return;
    }

    if(!estoque){ //não há produtos no estoque
        printf("Estoque Vazio!\n");
    }

    else{
        int id_cliente, id_pedido, id_codigo_produto, quantidade;
        char nome[30];

        while(fscanf(arquivo, "%d%s%d%d%d", &id_cliente, nome, &id_pedido, &id_codigo_produto, &quantidade) != EOF){
            
            insereCliente(cl, id_cliente, nome, id_pedido, id_codigo_produto, quantidade, estoque);

        }

        fclose(arquivo);
        printf("Historico Carregado!\n");
    }
}

void imprimeClientes(Cliente *cl){
    
    while(cl){
        printf("Id: %d Nome: %s\n", cl->id_cliente, cl->nome);
        Pedido *pedido = cl->pedidos;

        while(pedido){
            printf("Id Pedido: %d\n", pedido->id_pedido);
            PedidoItem *itens = pedido->itens;

            while(itens){
                printf("Id Item: %d Quantidade: %d\n", itens->codigo_produto, itens->quantidade);
                itens = itens->prox;
            }

            pedido = pedido->prox;
        }
        cl = cl->prox;
    }

}

Produto *processar_pedidos(int codigo_produto, Produto *estoque){
    
    Produto *aux = estoque;

    while(aux){
        if(aux->codigo == codigo_produto){ //achou o produto que o cliente pediu
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
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