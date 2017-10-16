all: main.c main.h
	gcc -o ejecutable main.c main.h -pthread
	./ejecutable -i ejemplo1.txt -h 3 -c 5 -n 5 -m 3 -s out.txt -d
