
// Testar se funciona corretamente o empilhamento de par�metros
// passados por valor ou por refer�ncia.


%{
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "compilador.h"

int num_vars;
int nivel_lexico;
int desloc;
Tabela *ts;

%}

%token PROGRAM ABRE_PARENTESES FECHA_PARENTESES
%token VIRGULA PONTO_E_VIRGULA DOIS_PONTOS PONTO
%token T_BEGIN T_END VAR IDENT ATRIBUICAO
%token MENOR_OU_IGUAL MAIOR_QUESimbolo
%token THEN WHILE MAIOR_OU_IGUAL MAIS
%token ARRAY TYPE LABEL PROCEDURE GOTO IF ELSE DO OR DIV AND NOT MENOS MULTI
%token ABRE_CHAVE FECHA_CHAVE ABRE_COLCHETE FECHA_COLCHETE NUMERO DIVISAO
%token READ WRITE TRUE FALSE OF FUNCTION 

%%

programa    :{
             geraCodigo (NULL, "INPP");
             }
             PROGRAM IDENT
             ABRE_PARENTESES lista_idents FECHA_PARENTESES PONTO_E_VIRGULA
             bloco PONTO {
             geraCodigo (NULL, "PARA");
             }
;

bloco       :
              parte_declara_vars
              {
              }

              comando_composto
              {
               int dmem_var = 0;
               int i = ts->topo;
              while( i>0 && ts->simbolos[i].infos->nivel_lexico == nivel_lexico) 
               {
                  dmem_var++;
                  i--;
               }
               retira(dmem_var, ts);
               char buffer[15] = "DMEM ";
               sprintf(buffer + strlen(buffer), "%d", dmem_var);
               geraCodigo(NULL, buffer);
               imprime(ts);
              }
              ;




parte_declara_vars:  var
;


var         : {} VAR declara_vars
            |
;

declara_vars: declara_vars declara_var
            | declara_var
;

declara_var : { num_vars = 0;}
              lista_id_var DOIS_PONTOS
              tipo
              {
                  char buffer[15] = "AMEM ";
                  sprintf(buffer + strlen(buffer), "%d", num_vars);
                  geraCodigo(NULL, buffer);
              }
              PONTO_E_VIRGULA 
;

tipo        : IDENT
            
            {

               for (int i = ts->topo; i > ts->topo - num_vars; i--) {
                  ts->simbolos[i].infos->tipo = malloc ( TAM_TOKEN * sizeof(char));
                  strcpy(ts->simbolos[i].infos->tipo, token);
               }
               imprime(ts);
            }
;

lista_id_var: lista_id_var VIRGULA IDENT
              {
                  /* insere ultima vars na tabela de s�mbolos */
                  insere(token, "VS", nivel_lexico, desloc, ts);
                  desloc++;
                  num_vars++;
              }
            | IDENT { 
                     /* insere vars na tabela de s�mbolos */
                     insere(token, "VS", nivel_lexico, desloc, ts);
                     desloc++;
                     num_vars++;
                     }
;

lista_idents: lista_idents VIRGULA IDENT
            | IDENT
;


comando_composto: T_BEGIN comandos T_END

comandos:
;


%%

int main (int argc, char** argv) {
   FILE* fp;
   extern FILE* yyin;
   
   if (argc<2 || argc>2) {
         printf("usage compilador <arq>a %d\n", argc);
         return(-1);
      }

   fp=fopen (argv[1], "r");
   if (fp == NULL) {
      printf("usage compilador <arq>b\n");
      return(-1);
   }


/* -------------------------------------------------------------------
 *  Inicia a Tabela de S�mbolos
 * ------------------------------------------------------------------- */
   ts = malloc(sizeof(Tabela));
   ts->topo = 0;
   ts->max = 100;
   ts->simbolos = malloc(ts->max * sizeof(char));
   yyin=fp;
   yyparse();

   return 0;
}
