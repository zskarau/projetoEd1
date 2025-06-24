#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

//ESTOQUE
Produto *alocarProduto(int codigo, char nome[], char categoria[], int quantidade){

    Produto *novo = NULL;
    novo = (Produto *)malloc(sizeof(Produto));
    if(novo){
        novo->codigo = codigo;
        strcpy(novo->nome, nome);
        strcpy(novo->categoria, categoria);
        novo->quantidade = quantidade;
        novo->precos[0] = 0;
        novo->precos[1] = 0;
        novo->precos[2] = 0;
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

void imprimeEstoque(Produto *aux){

    if(!aux){
        printf("\nEstoque Vazio!\n");
        return;
    }

    while(aux){
        printf("Cod: %d Nome: %s \nQntd: %d Cat: %s\n", aux->codigo, aux->nome, aux->quantidade, aux->categoria);
        printf("P1: R$%.2f P2: R$%.2f P3: R$%.2f\n\n", aux->precos[0], aux->precos[1], aux->precos[2]);
        aux = aux->prox;
    }
}

void carregar_estoque(char *tipo_arquivo, Produto **p){
    
    FILE *arquivo = fopen(tipo_arquivo, "r");
    if(!arquivo) printf("Não foi possível abrir o arquivo.");
    else{
        if(*p){
            printf("\nEstoque Ja Carregado!\n");
            return;
        }

        int codigo, quantidade;
        char nome[20], categoria[20];
        while(fscanf(arquivo, "%d%s%d%s", &codigo, nome, &quantidade, categoria) != EOF){
            insereProduto(p, codigo, nome, quantidade, categoria);
        }

        fclose(arquivo);
        printf("\nEstoque Carregado!\n");
    }
}

void carregar_precos(char *tipo_arquivo, Produto *estoque){

    FILE *arquivo = fopen(tipo_arquivo, "r");
    if (!arquivo) {
        printf("\nNao foi possivel abrir o arquivo de precos.\n");
        return;
    }

    int codigo;
    float preco1, preco2, preco3;

    if(!estoque){
        printf("\nEstoque inexistente!\n");
        return;
    }

    while (fscanf(arquivo, "%d%f%f%f", &codigo, &preco1, &preco2, &preco3) != EOF){
        Produto *aux = estoque;
        while(aux){
            if (aux->codigo == codigo){
                aux->precos[0] = preco1;
                aux->precos[1] = preco2;
                aux->precos[2] = preco3;
                break;
            }
            aux = aux->prox;
        }
    }

    fclose(arquivo);
    printf("\nPrecos Carregados!\n");
}

//HISTORICO
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

        if(*hv){
            printf("\nHistorico Ja Carregado!\n");
            return;
        }

        int codigo, vendas[4];

        while(fscanf(arquivo, "%d%d%d%d%d", &codigo, &vendas[0], &vendas[1], &vendas[2], &vendas[3]) != EOF){
            insereHistorico(hv, codigo, vendas);
        }

        fclose(arquivo);
        printf("Historico Carregado!\n");
    }
}

void imprimeHistorico(HistoricoVendas *temp){
//imprime o historico de vendas
    if(!temp){
        printf("\nHistorico Vazio!\n");
        return;
    }

    while(temp){
        printf("Codigo: %d \nVenda 1: %d Venda 2: %d Venda 3: %d Venda 4: %d\n\n", temp->codigo, temp->vendas[0], temp->vendas[1], temp->vendas[2], temp->vendas[3]);
        temp = temp->prox;
    }
}

//CLIENTES, PEDIDOS E ITENS DE PEDIDO
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

    PedidoItem *novo = NULL;
    novo = alocarItens(codigo_produto, quantidade);
    
    if(novo){
        novo->prox = *pedidoItem;
        *pedidoItem = novo;
    }
}

void carregar_clientes_pedidos(char *tipo_arquivo, Cliente **cl, Produto *estoque){
    FILE *arquivo = fopen(tipo_arquivo, "r");

    if(!arquivo){
        printf("\nNão foi possível abrir o arquivo.\n");
        return;
    }

    if(*cl){

        printf("\nClientes Ja Carregados!\n");
        return;
    }

    int id_cliente, id_pedido, id_codigo_produto, quantidade;
    char nome[30];

    while(fscanf(arquivo, "%d%s%d%d%d", &id_cliente, nome, &id_pedido, &id_codigo_produto, &quantidade) != EOF){
        
        insereCliente(cl, id_cliente, nome, id_pedido, id_codigo_produto, quantidade, estoque);

    }

    fclose(arquivo);
    printf("\nClientes Carregados!\n");
}

void imprimeClientes(Cliente *cl){
    
    if(!cl){
        printf("\nNao Ha Clientes!\n");
        return;
    }

    while(cl){
        printf("\nId: %d Nome: %s\n", cl->id_cliente, cl->nome);
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

int atualizar_estoque(Produto *estoque, int codigo_produto, int quantidade){
    Produto *paux = estoque;

    while(paux){
        if(paux->codigo == codigo_produto){ //achou o produto pedido
            if(paux->quantidade >= quantidade) { //verifica se ha quantidade em estoque
                paux->quantidade -= quantidade;
                return 1;

            } 
            else{
                printf("Nao Ha Produto %d Suficiente!\n", codigo_produto);
                return 0;
            }
        }
        paux = paux->prox;
    }

    printf("Produto %d Nao Encontrado!\n", codigo_produto);
    return 0;
}


void processar_pedidos(Cliente *cl, Produto *p){
    
    if (!cl){
        printf("\nNao Ha Clientes!\n");
        return;
    }

    if (!p){
        printf("\nNao Ha Produtos!\n");
        return;
    }

    Cliente *claux = cl;

    while (claux){
        printf("\nPedidos do Cliente %d: %s\n", claux->id_cliente, claux->nome);

        Pedido *pedido = claux->pedidos;

        if (!pedido) printf("Cliente %s Sem Pedidos!\n", claux->nome);

        while (pedido){
            PedidoItem *item = pedido->itens;

            while (item){
                if (atualizar_estoque(p, item->codigo_produto, item->quantidade))
                    printf("%d do Produto %d Adquiridos!\n", item->quantidade, item->codigo_produto);

                item = item->prox;
            }
            pedido = pedido->prox;
        }
        claux = claux->prox;
    }
}

float funcaoMediaVendas(HistoricoVendas *hv){
    
    float soma = 0.0;
    int i;

    for(i = 0; i < 4; i++){
        soma += hv->vendas[i];
        
    }
    
    return soma / 4;
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

        mediavendas = funcaoMediaVendas(temp);
        printf("Produto %d - Media = %.2f unidades vendidas\n", temp->codigo, mediavendas);
        temp = temp->prox;
    }
}

void liberarEstoque(Produto **estoque){
    
    Produto *temp = NULL;
    
    while(*estoque){

        temp = *estoque;
        *estoque = (*estoque)->prox;
        free(temp);
    }
    
    printf("\nMemoria do estoque liberado!\n");
}

void liberarHistorico(HistoricoVendas **hv){
    
    HistoricoVendas *temp = NULL;

    while(*hv){
        temp = *hv;
        *hv = (*hv)->prox;
        free(temp);
    }

    printf("\nMemoria do historico de vendas liberada!\n");
}

void liberarPedidosItens(PedidoItem *itens){
    PedidoItem *aux = NULL;

    while(itens){
        aux = itens;
        itens = itens->prox;
        free(aux);
    }
}

void liberarPedidos(Pedido *pedidos){
    Pedido *aux = NULL;

    while(pedidos){
        liberarPedidosItens(pedidos->itens);
        aux = pedidos;
        pedidos = pedidos->prox;
        free(aux);
    }
}

void liberarClientes(Cliente **cl){
    Cliente *temp = NULL;

    while(*cl){
        temp = *cl;
        *cl = (*cl)->prox;

        liberarPedidos(temp->pedidos);
        free(temp);
    }

    printf("\nMemoria dos clientes liberada!\n");
}

float funcaoMediaPrecos(Produto *estoque){
    

    float soma = 0.0;
    int i;

    for(i=0; i < 3; i++){
        
        soma += estoque->precos[i];      
    }
    
    return soma / 3;
}

void relatorioFinal(Produto *p, HistoricoVendas *hv){
    FILE *arquivo = fopen("relatorio.txt", "w");

    if(!arquivo){
        printf("\nErro ao criar arquivo!\n");
        return;
    }

    Produto *paux = p;

    while(paux){
        int e = 0;
        HistoricoVendas *phv = hv;

        while(phv){
            if(paux->codigo == phv->codigo){
                fprintf(arquivo, "Produto %d\n", paux->codigo);
                fprintf(arquivo, "Qntd: %d\n", paux->quantidade);
                if(paux->quantidade == 0) fprintf(arquivo, "(Necessário Reposição do Produto!)\n");
                fprintf(arquivo, "Media Precos: R$%.2f\n", funcaoMediaPrecos(paux));
                fprintf(arquivo, "Sugestao Reposicao: %.2f unidades\n\n", funcaoMediaVendas(phv) * 1.2);
                e = 1;
                break;
            }
            phv = phv->prox;
        }

        if(!e){
            fprintf(arquivo, "Produto %d sem vendas registradas!\n\n", paux->codigo);
        }

        paux = paux->prox;
    }
}