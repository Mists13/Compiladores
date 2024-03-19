#ifndef TABELA_SIMBOLOS
#define TABELA_SIMBOLOS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    char identificador;
    // char* categoria; adcionei esse tbm no tablet mas n lembro o pq
    char* atributos;
}simbolo;

typedef struct 
{
    int max;
    int topo;
    simbolo* simbolos;
}tabela;

// Insere o identificador indicado na Tabela de Simbolos, assim como seus atributos
void insere(char identificador, char* atributos, tabela* tabela)
{
    printf("Inserindo identificador '%c' e seus atributos '%s'\n", identificador, atributos);
    if(tabela->topo == tabela->max) // se cheia ... realloc talvez seja necessario
    {
        printf("Tabela cheia ...\nAumentando Tamanho ...");
        tabela->simbolos = realloc(tabela->simbolos, (tabela->max + tabela->topo) * sizeof(char));
        tabela->max = tabela->max + tabela->topo;
    }
    tabela->topo++;
    tabela->simbolos[tabela->topo].identificador = identificador;
    tabela->simbolos[tabela->topo].atributos = malloc(strlen(atributos) * sizeof(char));
    strcpy(tabela->simbolos[tabela->topo].atributos, atributos);
    printf("Inserido com sucesso\n");
} 

// Retorna a entrada (os atributos) da Tabela de Simbolos, associado ao idenficador procurado
char* busca(char identificador, tabela* tabela) 
{
    printf("Buscando '%c' na tabela\n", identificador);
    int i = tabela->topo; // indice da pilha
    while (i >= 0)
    {
        if (tabela->simbolos[i].identificador == identificador)
        {
            return tabela->simbolos[i].atributos;
        }
        i--;
    }
    return "Not found";
}

// Retira as ultimas n entradas da Tabela de Simbolos
void retira(int n, tabela* tabela)
{
    printf("Retirando %i identificadores da pilha\n", n);
    if ((tabela->topo - n) < 0)
    {
        printf("ERRO: A pilha possui menos de %i valores\n", n);
    }
    tabela->topo = tabela->topo - n;
}

#endif