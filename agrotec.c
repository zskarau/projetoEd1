#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(){
    int opcao;

    Produto *estoque = NULL; //ponteiro para o estoque
    HistoricoVendas *hv = NULL; //ponteiro para o historico de vendas
    Cliente *cl = NULL; //ponteiro para o primeiro cliente

    do{
        printf("\n==========|||||==========\n");
        printf("\nMenu AgroTec, escolha o que deseja: \n");
        printf("\n0 - Sair \n1 - Carregar Dados do Estoque \n2 - Carregar Precos \n3 - Carregar Historico\n4 - Carregar Pedidos\n");
        printf("5 - Inserir Novo Produto \n6 - Inserir Nova Venda \n7 - Inserir Novo Cliente \n8 - Processar Pedidos\n");
        printf("9 - Estoque \n10 - Clientes e Pedidos \n11 - Historico Vendas\n");
        printf("12 - Prever Compras \n13 - Gerar Relatorio Final\n");
        printf("\n==========|||||==========\n");   
        printf("\n");     
        scanf("%d", &opcao);

        switch(opcao){   

            case 0:
                printf("Desligando...");
            break;

            case 1:
                carregar_estoque("estoque.txt", &estoque);
            break;

            case 2:
                //carregar_precos();
            break;

            case 3:
                carregar_historico("historico_vendas.txt", &hv);
            break;

            case 4:
                carregar_clientes_pedidos("clientes_pedidos.txt", &cl, estoque);
            break;

            case 5:{

                int codigo, quantidade;
                char nome[30], categoria[30];

                printf("Digite o Codigo do Produto: \n");
                scanf("%d", &codigo);
                printf("Digite o Nome do Produto: \n");
                scanf("%s", nome);
                setbuf(stdin, NULL);
                printf("Digite a Categoria do Produto: \n");
                scanf("%s", categoria);
                setbuf(stdin, NULL);
                printf("Digite a Quantidade de Estoque: \n");
                scanf("%d", &quantidade);

                insereProduto(&estoque, codigo, nome, quantidade, categoria);

                printf("\nProduto Inserido!\n");

            } break;

            case 6:{
                
                int id_pedido, id_cliente, id_codigo_produto, quantidade;
                char nome[30];
                
                printf("Digite o ID do Cliente: \n");
                scanf("%d", &id_cliente);
                printf("Digite o Nome do Cliente: \n");
                scanf("%s", nome);
                setbuf(stdin, NULL);
                printf("Digite o ID do Pedido: \n");
                scanf("%d", &id_pedido);
                printf("Digite o ID do Produto: \n");
                scanf("%d", &id_codigo_produto);
                printf("Digite a Quantidade: \n");
                scanf("%d", &quantidade);

                insereCliente(&cl, id_cliente, nome, id_pedido, id_codigo_produto, quantidade, estoque);
                
                printf("\nNova Venda Inserida!\n");

            } break;
                
            case 7:{

                int id_cliente;
                char nome_cliente[30];

                printf("Digite o ID do novo cliente: \n");
                scanf("%d", &id_cliente);
                printf("Digite o nome do novo cliente: \n");
                scanf("%s", nome_cliente);
                setbuf(stdin, NULL);

                Cliente *existe = buscarCliente(cl, id_cliente, nome_cliente); //verificar se o cliente existe

                if(existe){

                    printf("\nCliente Ja Cadastrado!\n");
                }

                else{ //caso nao exista, aloque o novo cliente
                    
                    Cliente *novo = alocarCliente(id_cliente, nome_cliente);
                    
                    novo->prox = cl; 
                    cl = novo; 

                    printf("\nCliente Novo Cadastrado!\n");
                }

                break;
            }

            case 8:
                processar_pedidos(cl, estoque);
            break;

            case 9:
                imprimeEstoque(estoque);
            break;

            case 10:
                imprimeClientes(cl);
            break;
            
            case 11:
                imprimeHistorico(hv);
            break;

            case 12:
                prever_compras(hv);
            break;

            case 13:
                //relatorio_final();
            break;

            default:
                printf("\nOpcao invalida, tente novamente.\n");
        }

    }while(opcao != 0);

    //liberar_memoria();

    return 0;
}