#include <stdio.h>
#define INF 99999

void main() {
    typedef struct {
        int node1, node2, cost;
    } Link;

    typedef struct {
        int weight, parent;
    } Node;

    int numNodes, numLinks, sourceNode, currentNode;
    printf("Enter number of nodes: ");
    scanf("%d", &numNodes);
    printf("Enter number of links: ");
    scanf("%d", &numLinks);
    Link links[numLinks + 1];
    Node nodes[numNodes + 1];
    int visited[numNodes + 1];
    for (int i = 1; i <= numNodes; i++) {
        visited[i] = 0; // Initialize visited array to 0
    }

    for (int i = 1; i <= numLinks; i++) {
        printf("Enter link %d (node1 node2 cost): ", i);
        scanf("%d %d %d", &links[i].node1, &links[i].node2, &links[i].cost);
    }
    for (int i = 1; i <= numNodes; i++) {
        nodes[i].weight = INF; // Initialize weights to infinity
        nodes[i].parent = -1;   // Initialize parents to -1
    }
    printf("Enter source node: ");
    scanf("%d", &sourceNode);
    nodes[sourceNode].weight = 0; // Set source node weight to 0
    nodes[sourceNode].parent = sourceNode; // Set source node parent to itself

    visited[sourceNode] = 1; // Mark source node as visited
    currentNode = sourceNode;
    while (1) {
        int minWeight = INF;
        int nextNode = -1;
        for (int i = 1; i < numLinks; i++) {
            if (links[i].node1 == currentNode && !visited[links[i].node2]) {
                if (nodes[links[i].node2].weight > nodes[currentNode].weight + links[i].cost) {
                    nodes[links[i].node2].weight = nodes[currentNode].weight + links[i].cost;
                    nodes[links[i].node2].parent = currentNode;
                }
            } else if (links[i].node2 == currentNode && !visited[links[i].node1]) {
                if (nodes[links[i].node1].weight > nodes[currentNode].weight + links[i].cost) {
                    nodes[links[i].node1].weight = nodes[currentNode].weight + links[i].cost;
                    nodes[links[i].node1].parent = currentNode;
                }
            }
        }
        for (int i = 1; i <= numNodes; i++) {
            if (!visited[i] && nodes[i].weight < minWeight) {
                minWeight = nodes[i].weight;
                nextNode = i;
            }
        }
        if (nextNode == -1) break; // No more reachable nodes
        visited[nextNode] = 1; // Mark next node as visited
        currentNode = nextNode; // Move to the next node
    }
    printf("Shortest paths from source node %d:\n", sourceNode);
    for (int i = 1; i <= numNodes; i++) {
        if (nodes[i].weight != INF) {
            printf("Node %d: Cost = %d, Parent = %d\n", i, nodes[i].weight, nodes[i].parent);
        } else {
            printf("Node %d: Unreachable\n", i);
        }
    }
}