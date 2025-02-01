#include "Graph.hpp"

int main() {
    Graph g(6); // Grafo com 5 vértices
    
    // Adicionando arestas
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(0, 5);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(4, 5);
    
    // Testando BFS e DFS
    g.BFS(0); // Busca em largura a partir do vértice 0
    g.DFS(0); // Busca em profundidade a partir do vértice 0
    
    return 0;
}