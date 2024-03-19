#include "TabelaSimbolos.h"

int main ()
{
    tabela* tabela = malloc(sizeof(tabela));
    tabela->topo = 0;
    tabela->max = 100;
    tabela->simbolos = malloc(tabela->max * sizeof(char));
    insere('a', "+ - birulaibe", tabela);
    insere('b', "sqrt biruleibe", tabela);
    insere('c', "vrau biruliibe", tabela);
    printf("Atributos encontrados para 'a': %s\n", busca('a', tabela));
    retira(3, tabela);
}