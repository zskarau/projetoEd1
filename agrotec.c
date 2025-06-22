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

            case 5:
                //inserir_novo_produto();
            break;

            case 6:
                //inserir_nova_venda();
            break;

            case 7:
                //inserir_novo_cliente();
            break;

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