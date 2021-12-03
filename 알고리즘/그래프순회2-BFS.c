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
	int label;
} VERT;

typedef struct incidentEdge {
	int coffee;
} INCE;

typedef struct edge {
	int endpoint1, endpoint2, label;
} EDGE;

GRAPH* initGraph(int vertices, int edges);
void addEdge(GRAPH *graph, int vertex1, int vertex2);
void addINCE(GRAPH *graph, int vertex1, int vertex2, int EDGEIndex);
int addEDGE(GRAPH *graph, int vertex1, int vertex2);
void BFS(GRAPH *graph, int numOfVertices, int numOfEdges, int startVERTIndex);
void BFS0(GRAPH *graph, int VERTIndex, int numOfVertices);
void enqueue(int queue[], int queueSize, int n);
int dequeue(int queue[], int queueSize);
bool isEmpty(int queue[], int queueSize);
bool isFull(int queue[], int queueSize);

int main() {
	int numOfVertices, numOfEdges, startVert, endV1, endV2;
	scanf("%d %d %d", &numOfVertices, &numOfEdges, &startVert);
	GRAPH *graph = initGraph(numOfVertices, numOfEdges);
	for (int i = 0; i < numOfEdges; i++) {
		scanf("%d %d", &endV1, &endV2);
		addEdge(graph, endV1, endV2);
	}
	BFS(graph, numOfVertices, numOfEdges, startVert);
	free(graph);
}

GRAPH* initGraph(int vertices, int edges) {
	GRAPH *graph = (GRAPH *)calloc(1, sizeof(GRAPH));
	graph->vertices = (VERT *)calloc(vertices + 1, sizeof(VERT));
	graph->edges = (EDGE *)calloc(edges, sizeof(EDGE));
	graph->adjMatrix = (INCE **)calloc(vertices, sizeof(INCE *));
	for (int i = 0; i < vertices; i++) {
		graph->adjMatrix[i] = (INCE *)malloc(vertices * sizeof(INCE));
		for (int j = 0; j < vertices; j++)
			graph->adjMatrix[i][j].coffee = -1;
	}
	return graph;
}
void addEdge(GRAPH *graph, int vertex1, int vertex2) {
	addINCE(graph, vertex1, vertex2, addEDGE(graph, vertex1, vertex2));
}
int addEDGE(GRAPH *graph, int vertex1, int vertex2) {
	EDGE *edges = graph->edges;
	for (int index = 0; 1; index++)
		if (edges[index].endpoint1 == 0 && edges[index].endpoint2 == 0) {
			edges[index].endpoint1 = vertex1;
			edges[index].endpoint2 = vertex2;
			return index;
		}
}
void addINCE(GRAPH *graph, int vertex1, int vertex2, int EDGEIndex) {
	graph->adjMatrix[vertex1 - 1][vertex2 - 1].coffee = EDGEIndex;
	graph->adjMatrix[vertex2 - 1][vertex1 - 1].coffee = EDGEIndex;
}

void BFS(GRAPH *graph, int numOfVertices, int numOfEdges, int startVERTIndex) {
	VERT *vertex = graph->vertices;
	EDGE *edge = graph->edges;
	for (int i = 1; i <= numOfVertices; i++)
		vertex[i].label = 0;
	for (int i = 0; i < numOfEdges; i++)
		edge[i].label = 0;
	for (int i = 0, VERTIndex = startVERTIndex; i < numOfVertices; i++, VERTIndex = VERTIndex % numOfVertices + 1)
		if (vertex[VERTIndex].label == 0)
			BFS0(graph, VERTIndex, numOfVertices);
}
void BFS0(GRAPH *graph, int VERTIndex, int numOfVertices) {
	VERT *vertex = graph->vertices;
	INCE **adjMat = graph->adjMatrix;
	EDGE *edge = graph->edges;
	int *BFSQueue = (int*)calloc(numOfVertices, sizeof(int));
	printf("%d\n", VERTIndex);
	vertex[VERTIndex].label = 1;
	enqueue(BFSQueue, numOfVertices, VERTIndex);
	while (!isEmpty(BFSQueue, numOfVertices)) {
		int vertexIndex = dequeue(BFSQueue, numOfVertices);
		for (int i = 1; i <= numOfVertices; i++) {
			if (adjMat[vertexIndex - 1][i - 1].coffee != -1)
				if (edge[adjMat[vertexIndex - 1][i - 1].coffee].label == 0) {
					if (vertex[i].label == 0) {
						edge[adjMat[vertexIndex - 1][i - 1].coffee].label = 1;
						printf("%d\n", i);
						vertex[i].label = 1;
						enqueue(BFSQueue, numOfVertices, i);
					}
					else
						edge[adjMat[vertexIndex - 1][i - 1].coffee].label = 2;
				}
		}
	}
	free(BFSQueue);
}

void enqueue(int queue[], int queueSize, int n) {
	if (isEmpty(queue, queueSize))
		queue[0] = n;
	else
		for (int i = 0; 1; i++)
			if (queue[i % queueSize] != 0 && queue[(i + 1) % queueSize] == 0) {
				queue[(i + 1) % queueSize] = n;
				return;
			}
}

int dequeue(int queue[], int queueSize) {
	int n;
	if (isFull(queue, queueSize)) {
		n = queue[0];
		queue[0] = 0;
		return n;
	}
	for (int i = 0; 1; i++)
		if (queue[i % queueSize] == 0 && queue[(i + 1) % queueSize] != 0) {
			n = queue[(i + 1) % queueSize];
			queue[(i + 1) % queueSize] = 0;
			return n;
		}
}
bool isEmpty(int queue[], int queueSize) {
	for (int i = 0; i < queueSize; i++)
		if (queue[i] != 0)
			return false;
	return true;
}
bool isFull(int queue[], int queueSize) {
	for (int i = 0; i < queueSize; i++)
		if (queue[i] == 0)
			return false;
	return true;
}