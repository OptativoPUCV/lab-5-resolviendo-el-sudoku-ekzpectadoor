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


int is_valid(Node* n){
    int i, j;
    for(i=0;i<9;i++)
    {
      int visitado[10]= {0};
      for(j=0;j<9;j++)
      {
        int numero = n->sudo[i][j];
        if(numero == 0)
        {
          continue;
        }
        if(visitado[numero])return 0;
        visitado[numero] =1;

        
      }
    }
    for(i=0;i<9;i++)
    {
      int visitado[10]= {0};
      for(j=0;j<9;j++)
      {
        int numero = n->sudo[j][i];
        if(numero == 0)
        {
          continue;
        }
        if(visitado[numero])return 0;
        visitado[numero] =1;
    
      }
    }
    for (int k = 0; k < 9; k++) { 
      int visitado[10] = {0};
      for (int p = 0; p < 9; p++) 
      { 
        int i = 3 * (k / 3) + (p / 3);
        int j = 3 * (k % 3) + (p % 3);
        int num = n->sudo[i][j];
        if (num == 0) continue;
        if (num < 1 || num > 9) return 0;
        if (visitado[num]) return 0;
        visitado[num] = 1;
      }
    }

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
            if(is_valid(adjunto) == 1)
            {
              pushBack(list, adjunto);
              
            }
            else{
              free(adjunto);
            }  
          }
          return list;
        }
      }
    }  
    return list;
}


int is_final(Node* n){
    int i, j;
    for(i=0;i<9;i++)
    {
      for(j=0;j<9;j++)
      {
        int numero = n->sudo[i][j];
        if(numero == 0)
        {
          return 0;
        }
      }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack * pila = createStack();
  *cont = 0;
  push(pila, initial);
  while(top(pila) != NULL)
  {
    Node * n = top(pila);
    pop(pila);
    if(is_final(n)==1)
    {
      return n;
    }
    List* lista =get_adj_nodes(n);
    Node * current = first(lista);
    while(current != NULL)
    {
      push(pila, current);
      current = next(lista);
      (*cont)++;
    }
    free(lista);
    free(current);
  }
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