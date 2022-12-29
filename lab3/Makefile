all: clean yacc lexx compile  
yacc: 
	yacc -d yacc4.y -Wcounterexamples
lexx:
	lex lex4.l
compile: 
	gcc y.tab.c lex.yy.c  -o main
clean: 
	rm -rf y.tab.c rm -rf y.tab.h
