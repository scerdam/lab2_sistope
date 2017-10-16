#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "main.h"
#include <pthread.h>


char**soup;


int main (int argc, char **argv){

  char *file_name, *out_file = NULL;
  int n_threads, quantity_words, flag_show_results = 0;
  int width,length;
  int index;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "i:h:c:n:m:s:d")) != -1)
    switch (c)
      {
      case 'i':
        file_name = optarg;
        break;
      case 'h':
         n_threads = atoi(optarg);
        break;
      case 'c':
        quantity_words = atoi(optarg);
        break;
      case 'n':
        length = atoi(optarg); // cantidad columnas
        break;
      case 'm':
        width= atoi(optarg); // cantidad filas
        break;
      case 's':
        out_file  = optarg;
        break;
      case 'd':
        flag_show_results = 1;
        break;
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Opcion -%c requiere un argumento.\n", optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Opcion desconocida `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Opcion con caracter desconocido `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        abort ();
      }


  for (index = optind; index < argc; index++) printf ("No existe opcion para agumento: %s\n", argv[index]);

  hilo* threads;
  pthread_t hola[9];
   int j = 0;

  initiateStructures(&threads,n_threads, width, length);
  initiateSoup(width,length);


  while(j < n_threads){

   pthread_create(&(threads[j].thread), NULL, ubicar, (void *) threads);
   j++;

  }





  j = 0;
  while(j < n_threads){  // esperar a que todas las hebras terminen

   pthread_join(threads[j].thread, NULL);
   j++;

  }

  //Rellenar los espacios vacios/zeros ' ' ó '0' con letras aleatorias en minuscula

  // test soup soup[fila][columna]
  soup[1][2] = 'C';
  soup[1][3] = 'H';
  soup[1][4] = 'I';

  if(flag_show_results) printSoup(width,length);  // imprime la sopa si esta la flag de mostrar resuletado
  return 0;
}


void initiateStructures(hilo **threads, int n_threads, int width, int length){


  *threads= (hilo*)malloc(sizeof(hilo)*n_threads);
  int i;
  int j;
  char **wordList;
  // int wordsByThread = getWordsByThread(n_threads,)
  while(i < n_threads)
    {
      (*threads)[i].id = i;
       pthread_mutex_init(&((*threads)[i].mute), NULL);
       wordList = (*threads)[i].list;

       wordList = (char**)malloc(sizeof(char*)*width);
       for(j=0;j<width;j++){
         wordList[j] = (char*)malloc(sizeof(char)*length);
        }
       i++;
    }


}



void *ubicar(void* id){
  hilo * unhilo = (hilo*) id;
 printf("hola soy una hebra \n");



}


void printSoup(int width, int length){
int row, columns;
  for (int row=0; row<width; row++)
  {
      for(int columns=0; columns<length; columns++)
          {
           printf("%c  ", soup[row][columns]);
          }
      printf("\n");
   }
}


void initiateSoup(int width,int length){ // reserva memoria para la matriz Soup e inicializa su casilla con '0' despues cambiar a ' '
  //Matriz de sopa de letras
    int i = 0;
    soup = (char**)malloc(sizeof(char*)*width);
    for(i=0;i<width;i++){
        soup[i] = (char*)malloc(sizeof(char)*length);
    }

    int row, columns;
      for (int row=0; row<width; row++)
      {
          for(int columns=0; columns<length; columns++)
              {
               soup[row][columns]='0';
              }
       }

}





int getStartLine(int i,int n_processes, int file_lines ){ // funcion que calcula la linea de comienzo de lectura para cada proceso(pasada como argumento al programa comparador) en funcion de los argumentos recibidos
  int line = 0;

  if(i==0) line = 1;
  else{
    if(i<n_processes){
      line = (file_lines/n_processes)*i +1;
    }
    else{
      line = -1;
    }
  }

  return line;

}

int getLinesToRead(int i,int n_processes, int file_lines ){ // funcion que calcula la cantidad de lineas que debe leer cada proceso(pasada como argumento al programa comparador)
  int line = 0;

  if(i<n_processes-1){
    line = (file_lines/n_processes);
  }
  else{
    line = file_lines - (file_lines/n_processes)*i-1;
  }


  return line;

}

int countLines(const char *file_name){ // funcion para contar las lineas del archivo pasado como arguemento
     int ch = 0;
     int count = 0;
     FILE *fileHandle;

     if ((fileHandle = fopen(file_name, "r")) == NULL) {
        return -1;
     }

     do {
        ch = fgetc(fileHandle);
        if ( ch == '\n')
           count++;
     } while (ch != EOF);
     count++;
     fclose(fileHandle);

     return count;
}

char* concat(const char *s1, const char *s2)  //funcion que concatena 2 string
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}
