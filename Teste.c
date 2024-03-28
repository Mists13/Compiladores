#include "TabelaSimbolos.h"

int main ()
{
    tabela* tabela = malloc(sizeof(tabela));
    tabela->topo = 0;
    tabela->max = 100;
    tabela->simbolos = malloc(tabela->max * sizeof(char));
    insere('a', "VS", "[0, 0, char]", tabela);
    insere('b', "VS", "[0, 1, char]", tabela);
    insere('c', "VS", "[0, 2, char]", tabela);
    printf("Atributos encontrados para 'a': %s\n", busca('a', tabela));
    retira(3, tabela);
}
