#include "list.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int sudo[9][9];
} Node;

Node *createNode() {
  Node *n = (Node *)malloc(sizeof(Node));
  return n;
}

Node *copy(Node *n) {
  Node *new = (Node *)malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node *read_file(char *file_name) {
  Node *n = createNode();
  FILE *file = fopen(file_name, "r");
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++) {
      if (!fscanf(file, "%d", &n->sudo[i][j]))
        printf("failed to read data!");
    }
  }

  fclose(file);
  return n;
}

void print_node(Node *n) {
  int i, j;
  for (i = 0; i < 9; i++) {
    for (j = 0; j < 9; j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node *n) {
  int fila[10];
  int columna[10];
  int submatriz[10];

  for (int i = 0; i < 9; i++) {
    for (int k = 0; k < 10; k++) {
      fila[k] = 0;
      columna[k] = 0;
    }

    for (int j = 0; j < 9; j++) {
      int num_fila = n->sudo[i][j];
      if (num_fila != 0) {
        if (fila[num_fila] == 1) {
          return 0;
        } else {
          fila[num_fila] = 1;
        }
      }

      int num_columna = n->sudo[j][i];
      if (num_columna != 0) {
        if (columna[num_columna] == 1) {
          return 0;
        } else {
          columna[num_columna] = 1;
        }
      }
    }
  }

  for (int k = 0; k < 9; k++) {
    for (int p = 0; p < 10; p++) {
      submatriz[p] = 0;
    }

    for (int p = 0; p < 9; p++) {
      int i = 3 * (k / 3) + (p / 3);
      int j = 3 * (k % 3) + (p % 3);
      int num_submatriz = n->sudo[i][j];

      if (num_submatriz != 0) {
        if (submatriz[num_submatriz] == 1) {
          return 0;
        } else {
          submatriz[num_submatriz] = 1;
        }
      }
    }
  }
  return 1;
}

List* get_adj_nodes(Node* n)
{
  List* list = createList();
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      if (n->sudo[i][j] == 0)
      {
        for (int num = 1; num <= 9; num++)
        {

          Node* newNode = copy(n);
          newNode->sudo[i][j] = num;
          if (is_valid(newNode))
            pushBack(list, newNode);
          else 
            free(newNode);
        }
        return list;
      }
    }
  }return list;
}

int is_final(Node *n) {
  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if (n->sudo[i][j] == 0) {
        return 0;
      }
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
   Stack* stack = createStack();
   push(stack, initial);

   while (!is_empty(stack))
      {
         Node *current = top (stack);
         pop(stack);

         if (is_final(current))
         {
            return current;
         }

         List* adj = get_adj_nodes(current);
         Node* aux = first(adj);

         while (aux != NULL)
            {
               push(stack, aux);
               aux = next(adj);
            } 

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