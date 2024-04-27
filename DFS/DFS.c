#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int matrix[MAX][MAX], adjList[MAX][MAX];
int visited[MAX], vertex, count;

void open(char* filename) {
    int k = 1;
    char sym;

    FILE* file;
    file = fopen(filename, "r+");
    if (file == NULL) {
        printf("Error");
        exit(0);
    }

    fscanf(file, "%i %i", &vertex, &count);

    sym = fgetc(file);
    int i = -1, j = 0; 
    while (sym != EOF) {
        adjList[i][j] = atoi(&sym);
        while (sym != '\n' && sym != EOF) {
            if (sym != ' '){
                adjList[i][j] = atoi(&sym);
                j++; 
            }
            sym = fgetc(file);
        }
        i++;
        j = 0;
        k += 1;
        sym = fgetc(file);
    }
    fclose(file);
}

int way[MAX];
void PrintWay() {
    int way2[MAX];
    for (int i = 0; i < vertex; i++) {
        way2[way[i]] = i + 1;
    }
    for (int i = 1; i < vertex; i++) {
        if(way2[i]>0)
            printf("%d ", way2[i]);
    }
}

void ConvertToAdjMatrix(int adjList[MAX][MAX], int matrix[MAX][MAX]) {
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            matrix[i][j] = 0; // »нициализируем матрицу нул€ми
        }
    }
    for (int i = 0; i < vertex; i++) {
        int j = 0;
        while (adjList[i][j] != 0) {
            int neighbour = adjList[i][j];
            matrix[i][neighbour-1] = 1;  // ”станавливаем 1, если вершина существует в списке смежностей
            j++;
        }
    }
}


int Cycle(int v, int parent, int n, int edges, int counter, int matrix [MAX][MAX]) {
    visited[v] = 1;
    int sup = 0;
    if (way[v] == 0) {
        for (int i = 0; i < n; i++)
            way[v] += visited[i];
    }
   
    for (int i = 0; i < n; i++) {
        if (matrix[v][i]) {
            if (!visited[i]) {
                if (Cycle(i, v, n, edges, counter + 1, matrix)) {
                    return 1;
                }
                visited[i] = 0;
            }
            else {
                sup = 0;
                for (int q = 0; q < n; q++) {
                    sup += visited[q];
                }
                if (i != parent && (counter+1) >= edges) {
                    return 1;
                }
            }
                
        }
    }
    way[v] = 0;
    return 0;
}



int main() {
    open("test.txt");

    int matrix[MAX][MAX];

    ConvertToAdjMatrix(adjList, matrix);

   /* printf("adjacency matrix\n");
    for (int i = 0; i < vertex; i++) {
        for (int j = 0; j < vertex; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }*/

    for (int i = 0; i < vertex; i++) {
        visited[i] = 0;
    }
    
    int cycleExists = 0;
    for (int i = 0; i < vertex; i++) {
        if (!visited[i]) {
            if (Cycle(i, -1, vertex, count, 0, matrix)) {
                cycleExists = 1;
                break;
            }
        }
    }


    if (cycleExists) {
        printf("The graph contains a cycle with at least %d edges.\n", count);
        PrintWay();
    }
    else {
        printf("The graph does not contain a cycle with at least %d edges.\n", count);
    }
    return 0;
}
