#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(){
    int opc = -1;

    Produto *lista = NULL;
    HistoricoVendas *hv = NULL;
    Cliente *cl = NULL;

    do{
        printf("\n==========|||||==========\n");
        printf("\nMenu AgroTec, escolha o que deseja: \n");
        printf("\n0 - Sair \n1 - Carregar Dados do Estoque \n2 - Carregar Precos \n3 - Carregar Historico\n4 - Carregar Pedidos\n");
        printf("5 - Inserir Novo Produto \n6 - Inserir Nova Venda \n7 - Inserir Novo Cliente \n8 - Processar Pedidos\n");
        printf("9 - Prever Compras \n10 - Gerar Relatorio Final\n");
        printf("\n==========|||||==========\n");   
        printf("\n");     
        scanf("%d", &opc);

        switch(opc){   

            case 0:
                printf("Desligando...");
            break;

            case 1:
                carregar_estoque("estoque.txt", &lista);    
                imprimeEstoque(lista);
            break;

            case 2:
                //carregar_precos();
            break;

            case 3:
                carregar_historico("historico_vendas.txt", &hv);
                imprimeHistorico(hv);
            break;

            case 4:
                carregar_clientes_pedidos("clientes_pedidos.txt", &cl, lista);
                imprimeClientes(cl);
            break;

            case 5:{

                int codigo, quantidade;
                char nome[30], categoria[30];

                printf("Digite o codigo do produto: \n");
                scanf("%d", &codigo);
                printf("Digite o nome do produto: \n");
                scanf("%s", nome);
                printf("Digite a categoria do produto: \n");
                scanf("%s", categoria);
                printf("Digite a quantidade de estoque: \n");
                scanf("%d", &quantidade);

                insereProduto(&lista, codigo, nome, quantidade, categoria);

                printf("\nProduto Inserido!\n");

                break;
            }

            case 6:{
                
                int id_pedido, id_cliente, id_codigo_produto, quantidade;
                char nome[30];
                
                printf("Digite o ID do cliente: \n");
                scanf("%d", &id_cliente);
                printf("Digite o nome do cliente: \n");
                scanf("%s", nome);
                printf("Digite o ID do pedido: \n");
                scanf("%d", &id_pedido);
                printf("Digite o ID codigo do produto: \n");
                scanf("%d", &id_codigo_produto);
                printf("Digite a quantidade: \n");
                scanf("%d", &quantidade);

                insereCliente(&cl, id_cliente, nome, id_pedido, id_codigo_produto, quantidade, lista);
                
                printf("\nNova venda inserida!\n");

                break;
            }
                
            case 7:{

                int id_cliente;
                char nome_cliente[30];

                printf("Digite o ID do novo cliente: \n");
                scanf("%d", &id_cliente);
                printf("Digite o nome do novo cliente: \n");
                scanf("%s", nome_cliente);

                Cliente *existe = buscarCliente(cl, id_cliente, nome_cliente);//busca para ver se ja existe

                if(existe){

                    printf("\nCliente ja cadastrado!\n");
                }

                else{
                    //se caso nao existe, ira alocar normalmente um novo cliente
                    Cliente *novo = alocarCliente(id_cliente, nome_cliente);
                    
                    novo->prox = cl; 
                    cl = novo; 

                    printf("\nCliente novo cadastrado!\n");
                }

                break;
            }

            case 8:
               //processar_pedidos();
            break;

            case 9:
                prever_compras(hv);
            break;

            case 10:
                //relatorio_final();
            break;
            
            default:
                printf("\nOpcao invalida, tente novamente.\n");
        }

    }while(opc != 0);

    //liberar_memoria();

    return 0;
}