.PHONY: parser clean distclean
.PHONY: interpreteur clean distclean

all:parser interpreteur
	
parser : 
	#parser	
	bison -v -d parser/yaya.y
	mv yaya.tab.h parser/yaya.h
	mv yaya.tab.c  parser/yaya.y.c
	flex parser/yaya.l
	mv lex.yy.c parser/yaya.l.c
	mv yaya.output parser/yaya.output
	gcc -c parser/yaya.l.c -o parser/yaya.l.o
	gcc -c parser/yaya.y.c -o parser/yaya.y.o
	gcc -o parser/yaya parser/yaya.l.o parser/table_symbole.c parser/gestion_fonction.c parser/yaya.y.o -ll -lm

interpreteur : 
	#interpreteur	
	bison -v -d interpreteur/interpreteur.y
	mv interpreteur.tab.h interpreteur/interpreteur.h
	mv interpreteur.tab.c  interpreteur/interpreteur.y.c
	flex interpreteur/interpreteur.l
	mv lex.yy.c interpreteur/interpreteur.l.c
	mv interpreteur.output interpreteur/interpreteur.output
	gcc -c interpreteur/interpreteur.l.c -o interpreteur/interpreteur.l.o
	gcc -c interpreteur/interpreteur.y.c -o interpreteur/interpreteur.y.o
	gcc -o interpreteur/interpreteur interpreteur/interpreteur.l.o interpreteur/memoire.c interpreteur/interpreteur.y.o -ll -lm

testParser:parser
	./parser/yaya < parser/test.c

testInterpreteur:interpreteur testParser
	./interpreteur/interpreteur < assembleur.txt > fic.txt

clean:
	rm parser/yaya.h parser/yaya.l.c parser/yaya.y.c parser/*.o parser/yaya.output
	rm interpreteur/interpreteur.h interpreteur/interpreteur.l.c interpreteur/interpreteur.y.c interpreteur/*.o interpreteur/interpreteur.output
