#include "tabelaSimbolos.h"

// Insere o identificador indicado na Tabela de Simbolos, assim como suas infos e categoria
void insere(char* identificador, char* categoria, int nivel_lexico, int deslocamento, Tabela* tabela)
{
    printf("Inserindo identificador '%s', sua caregoria '%s' e suas infos '%i %i'\n", identificador, categoria, nivel_lexico, deslocamento);
    if(tabela->topo == tabela->max) // se cheia ... realloc talvez seja necessario
    {
        printf("Tabela cheia ...\nAumentando Tamanho ...");
        tabela->simbolos = realloc(tabela->simbolos, (tabela->max + tabela->topo) * sizeof(char));
        tabela->max = tabela->max + tabela->topo;
    }
    tabela->topo++;
    tabela->simbolos[tabela->topo].identificador = malloc ( strlen (identificador) * sizeof(char));
    strcpy(tabela->simbolos[tabela->topo].identificador, identificador);
    tabela->simbolos[tabela->topo].categoria = malloc ( strlen (categoria) * sizeof(char));
    strcpy(tabela->simbolos[tabela->topo].categoria, categoria);
    tabela->simbolos[tabela->topo].infos = malloc (sizeof(Infos));
    tabela->simbolos[tabela->topo].infos->nivel_lexico = nivel_lexico;
    tabela->simbolos[tabela->topo].infos->deslocamento = deslocamento;
    printf("Simbolo inserido com sucesso na Tabela de Simbolos\n");
} 

// Retorna a entrada (as infos) da Tabela de Simbolos, associado ao idenficador procurado
Infos* busca(char* identificador, Tabela* tabela) 
{
    printf("Buscando '%s' na tabela\n", identificador);
    int i = tabela->topo; // indice da pilha
    while (i >= 0)
    {
        if (strcmp(tabela->simbolos[i].identificador, identificador))
        {
            return tabela->simbolos[i].infos; // retorna nivel lexico, deslocamento e tipo
        }
        i--;
    }
    return NULL;
}

// Retira as ultimas n entradas da Tabela de Simbolos
void retira(int n, Tabela* tabela)
{
    printf("Retirando %i identificadores da pilha\n", n);
    if ((tabela->topo - n) < 0)
    {
        printf("ERRO: A pilha possui menos de %i valores\n", n);
    }
    tabela->topo = tabela->topo - n;
}

void imprime(Tabela* tabela) {
    int i = tabela->topo; // indice da pilha
    printf("\nTABELA DE SIMBOLOS:\n\n");
    while (i > 0)
    {
        printf("%s %s [%i, %i, %s]\n", tabela->simbolos[i].identificador, tabela->simbolos[i].categoria, tabela->simbolos[i].infos->nivel_lexico, tabela->simbolos[i].infos->deslocamento, tabela->simbolos[i].infos->tipo);
         i--;
    }
    printf("\n");
}
