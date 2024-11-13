#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5  // Number of vertices in the graph

// Function to find the vertex with minimum distance value
int minDistance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (visited[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V];     // dist[i] will hold the shortest distance from src to i
    int visited[V];  // visited[i] is 1 if vertex i is processed

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visited[i] = 0;

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < V; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}
