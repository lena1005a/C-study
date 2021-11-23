#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>  
#include <stdlib.h> 
#include <stdbool.h>

typedef struct graph {
	struct vertex *vertices;
	struct edge *edges;
	int numOfvertex, numOfedge;
} GRAPH;

typedef struct vertex {
	struct incidentEdge *incEdge;
	int vertex_name, distance;
	struct edge *parentEdge;
} VERT;

typedef struct incidentEdge {
	int otherEndVERTIndex, EDGEIndex;
	struct incidentEdge *next;
} INCE;

typedef struct edge {
	int weight, endpoint1, endpoint2;
} EDGE;

typedef struct prim_Queue {
	struct vertex *vertex;
} PRQ;

GRAPH* buildGraph();
void set_graph(GRAPH* graph);
void prim_MST(GRAPH* graph);
bool isEmpty(GRAPH* graph, PRQ* queue);
VERT* removeMin(GRAPH* graph, PRQ* queue);
bool isElement(GRAPH* graph, PRQ* queue, VERT* vertex);

int main() {
	GRAPH *graph = buildGraph();
	prim_MST(graph);
	return 0;
}

GRAPH *buildGraph() {
	GRAPH *new_graph = (GRAPH *)malloc(sizeof(GRAPH));
	scanf("%d %d", &new_graph->numOfvertex, &new_graph->numOfedge);
	new_graph->vertices = (VERT *)calloc(new_graph->numOfvertex + 1, sizeof(VERT));
	new_graph->edges = (EDGE *)calloc(new_graph->numOfedge, sizeof(EDGE));

	for (int i = 1; i <= new_graph->numOfvertex; i++) {
		new_graph->vertices[i].incEdge = (INCE *)calloc(1, sizeof(INCE));
		new_graph->vertices[i].vertex_name = i;
	}

	set_graph(new_graph);
	return new_graph;
}

void set_graph(GRAPH *graph) {
	int v1, v2, w;

	for (int i = 0; i < graph->numOfedge; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		graph->edges[i].endpoint1 = v1;
		graph->edges[i].endpoint2 = v2;
		graph->edges[i].weight = w;

		INCE *incEdge1 = (INCE *)calloc(1, sizeof(INCE));
		INCE *incEdge2 = (INCE *)calloc(1, sizeof(INCE));
		incEdge1->EDGEIndex = i;
		incEdge2->EDGEIndex = i;
		incEdge1->otherEndVERTIndex = v2;
		incEdge2->otherEndVERTIndex = v1;

		incEdge1->next = graph->vertices[v1].incEdge->next;
		incEdge2->next = graph->vertices[v2].incEdge->next;
		graph->vertices[v1].incEdge->next = incEdge1;
		graph->vertices[v2].incEdge->next = incEdge2;
	}
}

void prim_MST(GRAPH *graph) {
	PRQ *queue = (PRQ *)calloc(graph->numOfvertex, sizeof(PRQ));
	int min_result = 0;
	for (int i = 0; i < graph->numOfvertex; i++) {
		graph->vertices[i + 1].distance = -1; //무한
		queue[i].vertex = &graph->vertices[i + 1];
	}

	graph->vertices[1].distance = 0;
	while (!isEmpty(graph, queue)) {
		VERT *vertex = removeMin(graph, queue);
		EDGE *edge = graph->edges;
		printf(" %d", vertex->vertex_name);

		for (INCE *incEdge = vertex->incEdge->next; incEdge != NULL; incEdge = incEdge->next) { //해당 정점의 인접간선들 최소로 업데이트
			VERT *endVertex = &graph->vertices[incEdge->otherEndVERTIndex];
			if (isElement(graph, queue, endVertex)) //반대가 큐에 있는지 확인
				if (endVertex->distance == -1 || edge[incEdge->EDGEIndex].weight < endVertex->distance) {
					endVertex->distance = edge[incEdge->EDGEIndex].weight;
					endVertex->parentEdge = &edge[incEdge->EDGEIndex];
				}
		}
	}

	for (int i = 1; i <= graph->numOfvertex; i++) {
		if (graph->vertices[i].parentEdge != NULL) min_result += graph->vertices[i].parentEdge->weight;
	}
	printf("\n%d", min_result);
}

VERT *removeMin(GRAPH *graph, PRQ *queue) {
	VERT *minVertex = NULL;
	int minIndex = 0;
	for (int i = 0; i < graph->numOfvertex; i++) {
		if (queue[i].vertex != NULL && queue[i].vertex->distance != -1) {
			minVertex = queue[i].vertex;
			minIndex = i;
			break;
		}
	}

	for (int i = 0; i < graph->numOfvertex; i++) {
		if (queue[i].vertex != NULL) {
			if (queue[i].vertex->distance != -1 && queue[i].vertex->distance < minVertex->distance) {
				minVertex = queue[i].vertex;
				minIndex = i;
			}
		}
	}

	queue[minIndex].vertex = NULL;
	return minVertex;
}


bool isEmpty(GRAPH *graph, PRQ *queue) {
	for (int i = 0; i < graph->numOfvertex; i++) {
		if (queue[i].vertex != NULL) return false;
	}
	return true;
}

bool isElement(GRAPH *graph, PRQ *queue, VERT *vertex) {
	for (int i = 0; i < graph->numOfvertex; i++) {
		if (vertex == queue[i].vertex) return true;
	}
	return false;
}
