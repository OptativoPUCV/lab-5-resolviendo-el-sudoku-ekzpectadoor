#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int existe(int numero, List* lista)
{
  if(lista == NULL) return 1;
  
  void* dato = first(lista);
  while(dato != NULL)
  {
    int* num = (int*)dato;
    if((*num) == numero) return 0;
    dato = next(lista);
  }
  return 1;
}
int is_valid(Node* n){
    List* columna = createList();
    List* fila = createList();
    List* cuadricula = createList();
    int i, j, numero1, numero2,numero3,numFila,numCol;
    for(i=0;i<9;i++)
    {
      for(j=0;j<9;j++)
      {
        numero1 = n->sudo[i][j];
        numero2 = n->sudo[j][i];  
        if((existe(numero1, columna) == 0) || (existe(numero2,fila)==0))
        {
          return 0;
        }
        pushBack(columna, &numero1);
        pushBack(fila,&numero2);
        if(i<3 && j<3)
        {
          numFila = j *3;
          numCol =i*3;
          for(int aux = numFila; aux< numFila+3; aux++)
          {
            for(int aux2=numCol;aux<numCol+3;aux++)
            {
              numero3 = n->sudo[aux][aux2];
              if(existe(numero3, cuadricula) == 0) return 0;
              pushBack(cuadricula, &numero3);
            }
          }
        }
      }
    }
    clean(columna);
    clean(fila);
    clean(cuadricula);
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j;
    for(i=0;i<9;i++)
    {
      for(j=0;j<9;j++)
      {
        if(n->sudo[i][j] == 0)
        {
          for(int numero=1; numero<10; numero++)
          {
            Node* adjunto = copy(n);
            adjunto->sudo[i][j]= numero;
            pushBack(list, adjunto);  
          }
        }
      }
    }  
    return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/