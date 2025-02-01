#include <stdio.h>
#include "Queue.hpp"
#include "Stack.hpp"

#define MAX 100  // Tamanho máximo do grafo

class Graph {
private:
    int adjMatrix[MAX][MAX];
    int V; // Número de vértices
    
public:
    Graph(int vertices) {
        V = vertices;
        
        // Inicializa a matriz de adjacências com 0 (nenhuma aresta)
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }
    
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1; // Adiciona uma aresta de u para v
        adjMatrix[v][u] = 1; // Para grafos não direcionados
    }
    
    void BFS(int start) {
        bool visited[MAX] = { false };
        Queue q;
        
        visited[start] = true;
        q.enqueue(start);
        
        printf("BFS a partir do vértice %d: ", start);
        
        while (!q.isEmpty()) {
            int current = q.dequeue();
            printf("%d ", current);
            
            // Visita todos os vizinhos não visitados
            for (int i = 0; i < V; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    visited[i] = true;
                    q.enqueue(i);
                }
            }
        }
        printf("\n");
    }
    
    void DFS(int start) {
        bool visited[MAX] = { false };
        Stack s;
        
        s.push(start);
        
        printf("DFS a partir do vértice %d: ", start);
        
        while (!s.isEmpty()) {
            int current = s.pop();
            
            if (!visited[current]) {
                visited[current] = true;
                printf("%d ", current);
            }
            
            // Empilha os vizinhos não visitados
            for (int i = 0; i < V; i++) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    s.push(i);
                }
            }
        }
        printf("\n");
    }
};