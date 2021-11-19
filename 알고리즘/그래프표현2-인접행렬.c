#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph {
	struct vertex *vertices;
	struct edge *edges;
	struct incidentEdge **adjMatrix;
} GRAPH;

typedef struct vertex {
	int vertex_value;
} VERT;

typedef struct incidentEdge {
	int weight;
} INCE;

typedef struct edge {
	int weight, endpoint[2];
} EDGE;

void initGraph();
void modifyWeight();
void modifyEdge();
void addEdge();
void printAdjacent();

int main() {
	char op = '\0';
	int nodeA, nodeB, weight;
	GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
	initGraph(graph);

	while (op != 'q') {
		scanf(" %c", &op);
		switch (op) {
		case 'a':
			scanf("%d", &nodeA);
			printAdjacent(graph, nodeA);
			break;

		case 'm':
			scanf("%d %d %d", &nodeA, &nodeB, &weight);
			modifyWeight(graph, nodeA, nodeB, weight);
			break;

		default:
			break;
		}
	}
	free(graph);
}

void initGraph(GRAPH *graph) {
	graph->vertices = (VERT *)calloc(7, sizeof(VERT));
	graph->adjMatrix = (INCE **)calloc(6, sizeof(INCE *));

	for (int i = 0; i < 7; i++)
		graph->adjMatrix[i] = (INCE *)calloc(6, sizeof(INCE));
	graph->edges = (EDGE *)calloc(21, sizeof(EDGE));

	modifyEdge(graph, 1, 2, 1);
	modifyEdge(graph, 1, 3, 1);
	modifyEdge(graph, 1, 4, 1);
	modifyEdge(graph, 1, 6, 2);
	modifyEdge(graph, 2, 3, 1);
	modifyEdge(graph, 3, 5, 4);
	modifyEdge(graph, 5, 5, 4);
	modifyEdge(graph, 5, 6, 3);

	addEdge(graph, 1, 2, 1);
	addEdge(graph, 1, 3, 1);
	addEdge(graph, 1, 4, 1);
	addEdge(graph, 1, 6, 2);
	addEdge(graph, 2, 3, 1);
	addEdge(graph, 3, 5, 4);
	addEdge(graph, 5, 5, 4);
	addEdge(graph, 5, 6, 3);
}
void modifyWeight(GRAPH *graph, int nodeA, int nodeB, int weight) {
	if (nodeA > 6 || nodeB > 6 || nodeA < 1 || nodeB < 1) {
		printf("-1\n");
		return;
	}
	modifyEdge(graph, nodeA, nodeB, weight);
	addEdge(graph, nodeA, nodeB, weight);
}
void modifyEdge(GRAPH *graph, int vertFrom, int vertTo, int weight) {
	graph->adjMatrix[vertFrom - 1][vertTo - 1].weight = weight;
	graph->adjMatrix[vertTo - 1][vertFrom - 1].weight = weight;
}

void addEdge(GRAPH *graph, int endpoint1, int endpoint2, int weight) {
	EDGE* edges = graph->edges;

	for (int i = 0; i < 21; i++)
		if ((edges[i].endpoint[0] == endpoint1 && edges[i].endpoint[1] == endpoint2) || (edges[i].endpoint[0] == endpoint2 && edges[i].endpoint[1] == endpoint1)) {
			if (weight == 0) {
				edges[i].weight = 0;
				edges[i].endpoint[0] = 0;
				edges[i].endpoint[1] = 0;
			}
			else
				edges[i].weight = weight;
			return;
		}
	for (int i = 0; i < 21; i++)
		if (edges[i].endpoint[0] == edges[i].endpoint[1] == 0) {
			if (weight != 0) {
				edges[i].weight = weight;
				edges[i].endpoint[0] = endpoint1;
				edges[i].endpoint[1] = endpoint2;
			}
			return;
		}
}

void printAdjacent(GRAPH *graph, int nodeNum) {
	if (nodeNum < 1 || nodeNum > 6) {
		printf("-1\n");
		return;
	}
	INCE *incEdge = graph->adjMatrix[nodeNum - 1];
	for (int i = 0; i < 6; i++)
		if (incEdge[i].weight != 0)
			printf(" %d %d", i + 1, incEdge[i].weight);
	printf("\n");
}