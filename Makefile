 # -------------------------------------------------------------------
 #            Arquivo: Makefile
 # -------------------------------------------------------------------
 #              Autor: Bruno Müller Junior
 #               Data: 08/2007
 #      Atualizado em: [09/08/2020, 19h:01m]
 #
 # -------------------------------------------------------------------

$DEPURA=1

compilador: lex.yy.c compilador.tab.c tabelaSimbolos.o compilador.o
	gcc lex.yy.c compilador.tab.c tabelaSimbolos.o compilador.o -o compilador -ll

lex.yy.c: compilador.l compilador.h
	flex compilador.l

compilador.tab.c: compilador.y compilador.h 
	bison compilador.y -d -v

compilador.o : compilador.h compiladorF.c
	gcc -c compiladorF.c -o compilador.o

tabelaSimbolos.o : tabelaSimbolos.c tabelaSimbolos.h
	gcc -c tabelaSimbolos.c -o tabelaSimbolos.o

clean :
	rm -f compilador.tab.* lex.yy.c compilador.o compilador compilador.output tabelaSimbolos.o
