all:
	bison -v -d yaya.y
	mv yaya.tab.h yaya.h
	mv yaya.tab.c  yaya.y.c
	flex yaya.l
	mv lex.yy.c yaya.l.c
	gcc -c yaya.l.c -o yaya.l.o
	gcc -c yaya.y.c -o yaya.y.o
	gcc -o yaya yaya.l.o table_symbole.c yaya.y.o -ll -lm
test:all
	./yaya < test.c

clean:
	rm yaya.h yaya.l.c yaya.y.c *.o
