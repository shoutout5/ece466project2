all:
	bison -d -o project2.y.c project2.y
	flex -oproject2.lex.c project2.lex
	gcc -g -o project2 project2.lex.c project2.y.c functions.c -ll

clean:
	rm -Rf project2.lex.c project2.y.c project2.y.h project2 *~
