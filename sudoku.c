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
    List* lista = createList();
    int i, j, numero;
    for(i=0;i<9;i++)
    {
      for(j=0;j<9;j++)
      {
        numero = n->sudo[i][j];
        if(numero == 0)
        {
          continue;
        }
        if(existe(numero,lista))
        {
          return 0;
        }
        pushBack(lista,&numero);
        if(j+1 == 9)
        {
          clean(lista);
        }
      }
    }
    clean(lista);
    for(i=0;i<9;i++)
    {
      for(j=0;j<9;j++)
      {
        numero = n->sudo[j][i];
        if(numero == 0)
        {
          continue;
        }
        if(existe(numero,lista))
        {
          return 0;
        }
        pushBack(lista,&numero);
        if(j+1 == 9)
        {
          clean(lista);
        }
      }
    }
    clean(lista);
    for(i=0;i<3;i++)
    {
      for(j=0;j<3;j++)
      {
        int i2= i*3;
        int j2= j*3;
        for(int aux=i2; aux<i2+3;aux++)
        {
          for(int aux2=j2; aux2<j2+3;aux2++)
          {
            numero = n->sudo[aux][aux2];
            if(numero == 0)continue;
            if(existe(numero,lista))return 0;
            pushBack(lista, &numero);
            if(aux2+1 == j2+3)
            {
              clean(lista);
            }
          }
        }
      }
    }
    clean(lista);

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