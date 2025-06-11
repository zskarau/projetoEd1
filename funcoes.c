#include <stdio.h>
#include "funcoes.h"

void ler_arquivo(const char *tipo_arquivo){
    FILE *arquivo = fopen(tipo_arquivo, "r");
    if(!arquivo) printf("Não foi possível abrir o arquivo.");
    else{
        int cod, qntd;
        char nome[20], cat[20];
        while(fscanf(arquivo, "%d%s%d%s", &cod, nome, &qntd, cat) != EOF){
            printf("Cod: %d Nome: %s Qntd: %d Cat: %s\n", cod, nome, qntd, cat);
        }
    }
}