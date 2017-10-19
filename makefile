all: main.c main.h
	gcc -o ejecutable main.c main.h -pthread
	./ejecutable -i diccionario.txt -h 5 -c 6 -n 16 -m 6 -s out.txt -d
