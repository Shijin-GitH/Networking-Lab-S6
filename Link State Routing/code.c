#include <stdio.h>
#include <limits.h>

void main() {
    int numNodes, numLinks, sourceNode;
    printf("Enter number of nodes: ");
    scanf("%d", &numNodes);
    printf("Enter number of links: ");
    scanf("%d", &numLinks);
    int matrix[numNodes + 1][numNodes + 1], dist[numNodes + 1], visited[numNodes + 1];

    for (int i = 1; i <= numNodes; i++) {
        for (int j = 1; j <= numNodes; j++) {
            matrix[i][j] = 0; // Initialize adjacency matrix to 0
        }
        dist[i] = INT_MAX; // Initialize distances
        visited[i] = 0; // Initialize visited array to 0
    }

    printf("Enter the links (node1 node2 cost):\n");
    for (int i = 1; i <= numLinks; i++) {
        int node1, node2, cost;
        scanf("%d %d %d", &node1, &node2, &cost);
        matrix[node1][node2] = cost;
        matrix[node2][node1] = cost; // Assuming undirected graph
    }

    printf("Enter source node: ");
    scanf("%d", &sourceNode);
    dist[sourceNode] = 0; // Distance to source node is 0
    for (int i = 1; i <= numNodes; i++)
    {
        int min = INT_MAX, minIndex = -1;
        for (int j = 1; j <= numNodes; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                minIndex = j;
            }
        }
        if (minIndex == -1) break; // All reachable nodes are visited
        visited[minIndex] = 1; // Mark the node as visited

        for (int j = 1; j <= numNodes; j++) {
            if (!visited[j] && matrix[minIndex][j] != 0 && dist[minIndex] != INT_MAX && dist[minIndex] + matrix[minIndex][j] < dist[j]) {
                dist[j] = dist[minIndex] + matrix[minIndex][j]; // Update distance
            }
        }
    }
        
    printf("Shortest distances from node %d:\n", sourceNode);
    for (int i = 1; i <= numNodes; i++) {
        if (dist[i] == INT_MAX) {
            printf("Node %d: Unreachable\n", i);
        } else {
            printf("Node %d: %d\n", i, dist[i]);
        }
    }
}