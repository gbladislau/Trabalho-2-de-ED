all: decodificador codificador

decodificador: Arvore.o Bitindex.o bitmap.o Decodificador.o
	gcc -o decodificador Arvore.o Bitindex.o bitmap.o Decodificador.o

codificador: Arvore.o Bitindex.o bitmap.o Codificador.o ListaArv.o Listagen.o Vetchar.o
	gcc -o codificador Arvore.o Bitindex.o bitmap.o Codificador.o ListaArv.o Listagen.o Vetchar.o

Arvore.o: Arvore.c Arvore.h bitmap.h Bitindex.h
	gcc -o Arvore.o Arvore.c -c

Bitindex.o: Bitindex.c bitmap.h
	gcc -o Bitindex.o Bitindex.c -c

bitmap.o: bitmap.c bitmap.h
	gcc -o bitmap.o bitmap.c -c

Codificador.o: Codificador.c Codificador.h Arvore.h Vetchar.h ListaArv.h
	gcc -o Codificador.o Codificador.c -c

ListaArv.o: ListaArv.c ListaArv.h Listagen.h Arvore.h Vetchar.h
	gcc -o ListaArv.o ListaArv.c -c

Listagen.o: Listagen.c Listagen.h
	gcc -o Listagen.o Listagen.c -c

Vetchar.o: Vetchar.c Listagen.h Vetchar.h
	gcc -o Vetchar.o Vetchar.c -c

Decodificador.o: Decodificador.c Decodificador.h Arvore.h
	gcc -o Decodificador.o Decodificador.c -c