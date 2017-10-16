#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

typedef struct hilos{
    int id,x,y;
    pthread_t thread;
    char**list;
    pthread_mutex_t mute;
}hilo;

void *ubicar(void* id);
void initiateStructures(hilo **threads, int n_threads, int width, int length);
void printSoup(int width, int length);
void initiateSoup(int width,int length);

int countLines(const char *file_name);
int getStartLine(int i,int n_processes, int file_lines );
int getLinesToRead(int i,int n_processes, int file_lines );
char* concat(const char *s1, const char *s2);
void escritor(char *nucleotidos,FILE *salidaP, int afirmacion, int largo);
void buscador(int numProceso,char * chain, char* nombreFp, int posLinea, int lines, int cant);
