#ifndef TABELA_SIMBOLOS
#define TABELA_SIMBOLOS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int nivel_lexico;
    int deslocamento;
    char* tipo;
}Infos;

typedef struct 
{
    char* identificador;
    char* categoria; // Categoria do identificador, algo como 'VS' 
    Infos* infos; // Nivel lexico e deslocamento, algo como '[0, 0, int]'
}Simbolo;

typedef struct 
{
    int max;
    int topo;
    Simbolo* simbolos;
}Tabela;

// Insere o identificador indicado na Tabela de Simbolos, assim como suas infos e categoria
void insere(char* identificador, char* categoria, int nivel_lexico, int deslocamento, Tabela* tabela);

// Retorna a entrada (as infos) da Tabela de Simbolos, associado ao idenficador procurado
Infos* busca(char* identificador, Tabela* tabela);

// Retira as ultimas n entradas da Tabela de Simbolos
void retira(int n, Tabela* tabela);

void imprime(Tabela* tabela);

#endif
