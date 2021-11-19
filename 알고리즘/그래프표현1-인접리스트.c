#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct graph {
	struct vertex *vertices;
	struct edge *edges;
}GRAPH;

typedef struct vertex {
	struct incidentEdge *incEdge;
}VERT;

typedef struct edge {
	int weight, endpoint[2]; 
}EDGE;

typedef struct incidentEdge {
	int otherEndVertex, weight;
	struct incidentEdge *next;
}INCE;


void initGraph(GRAPH *graph);
void modifyWeight(GRAPH *graph, int nodeA, int nodeB, int weight);
void modifyEdge(GRAPH *graph, int vertFrom, int vertTo, int weight);
void printAdjacent(GRAPH *graph, int nodeNum);

void addEdge(GRAPH *graph, int endpoint1, int endpoint2, int weight); //간선 배열 생성


int main() {
	char op = '\0';
	int nodeA, nodeB, weight;

	GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
	initGraph(graph);

	while (1) {
		scanf("%c", &op);
		switch (op) {
		case 'a':
			scanf("%d", &nodeA);
			getchar();
			printAdjacent(graph, nodeA);
			break;
		case 'm':
			scanf("%d %d %d", &nodeA, &nodeB, &weight);
			getchar();
			modifyWeight(graph, nodeA, nodeB, weight);
			break;

		case 'q':
			return;

		default:
			break;
		}
	}
	free(graph);
}


void initGraph(GRAPH *graph) {
	graph->vertices = (VERT *)calloc(7, sizeof(VERT));

	for (int i = 1; i < 7; i++)
		graph->vertices[i].incEdge = (INCE *)calloc(1, sizeof(INCE));

	modifyEdge(graph, 1, 2, 1);
	modifyEdge(graph, 1, 3, 1);
	modifyEdge(graph, 1, 4, 1);
	modifyEdge(graph, 1, 6, 2);
	modifyEdge(graph, 2, 1, 1);
	modifyEdge(graph, 2, 3, 1);
	modifyEdge(graph, 3, 1, 1);
	modifyEdge(graph, 3, 2, 1);
	modifyEdge(graph, 3, 5, 4);
	modifyEdge(graph, 4, 1, 1);
	modifyEdge(graph, 5, 3, 4);
	modifyEdge(graph, 5, 5, 4);
	modifyEdge(graph, 5, 6, 3);
	modifyEdge(graph, 6, 1, 2);
	modifyEdge(graph, 6, 5, 3);


	//간선 배열 지정
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
	modifyEdge(graph, nodeB, nodeA, weight);
	addEdge(graph, nodeA, nodeB, weight); //간선도 수정
}


void modifyEdge(GRAPH *graph, int vertFrom, int vertTo, int weight) {
	INCE *tempEdge = graph->vertices[vertFrom].incEdge, *newEdge;
	for (; 1; tempEdge = tempEdge->next)
		if (tempEdge->next == NULL || tempEdge->next->otherEndVertex > vertTo) {
			if (weight == 0)
				return;
			else {
				newEdge = (INCE *)malloc(sizeof(INCE));
				newEdge->otherEndVertex = vertTo;
				newEdge->weight = weight;
				newEdge->next = tempEdge->next;
				tempEdge->next = newEdge;
				return;
			}
		}
		else if (tempEdge->next->otherEndVertex == vertTo)
			if (weight == 0) { 
				newEdge = tempEdge->next;
				tempEdge->next = newEdge->next;
				free(newEdge);
				return;
			}
			else {
				tempEdge->next->weight = weight;
				return;
			}
}



void printAdjacent(GRAPH *graph, int nodeNum) {
	if (nodeNum < 1 || nodeNum > 6) {
		printf("-1\n");
		return;
	}

	INCE *incEdge = graph->vertices[nodeNum].incEdge;
	if (incEdge->next == NULL) {
		printf("-1\n");
		return;
	}

	for (incEdge = incEdge->next; incEdge != NULL; incEdge = incEdge->next)
		printf(" %d %d", incEdge->otherEndVertex, incEdge->weight);
	printf("\n");
}



void addEdge(GRAPH *graph, int endpoint1, int endpoint2, int weight) {
	EDGE *edges = graph->edges;
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