#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

int main(){
    Produto *lista = NULL;
    carregar_estoque("estoque.txt", &lista);
    imprimir(lista);

    HistoricoVendas *hv = NULL;
    carregar_historico("historico_vendas.txt", &hv);
    imprimirHistorico(hv);
}