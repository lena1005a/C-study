#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>  
#include <stdlib.h> 
#include <stdbool.h>


//kruskal
//모든 정점 각각 배낭처리, 배낭밖의 간선들을 우선순위 큐저장

typedef struct graph {
	struct vertex *vertices;
	struct edge *edges;
	int numOfvertex, numOfedge;
} GRAPH;

typedef struct vertex {
	int name;
} VERT;

typedef struct edge {
	int weight;
	struct vertex *endpoint1, *endpoint2;
} EDGE;

typedef struct kruskalQueue {
	struct edge *edge;
} KRQ;

typedef struct kruskalDisjointSet {
	struct vertex *vertex;
	int subset_ID;
} KDS;

GRAPH* buildGraph();
void set_graph(GRAPH *graph);
GRAPH *kruskalMST(GRAPH *graph);
KRQ *init_queue(GRAPH *graph);
KDS *init_disjointset(GRAPH *graph);
GRAPH *spanning_subgraph(GRAPH *graph);
EDGE *removeMin(GRAPH *graph, KRQ *queue);
bool isInSameSubset(GRAPH *graph, KDS *disjSet, VERT *v1, VERT *v2);
void addEdge(GRAPH *graph, VERT *endpoint1, VERT *endpoint2, int weight);
void merge_Subset(GRAPH *graph, KDS *disjSet, VERT *v1, VERT *v2);
bool isQueueEmpty(GRAPH *graph, KRQ *queue);
bool isEdgeListFull(GRAPH *graph);
void print_MST(GRAPH *MST);

int main() {
	GRAPH *graph = buildGraph();
	GRAPH *MST = kruskalMST(graph);
	print_MST(MST);
}

GRAPH *buildGraph() {
	GRAPH *new_graph = (GRAPH *)malloc(sizeof(GRAPH));
	scanf("%d %d", &new_graph->numOfvertex, &new_graph->numOfedge);

	new_graph->vertices = (VERT *)calloc(new_graph->numOfvertex + 1, sizeof(VERT));
	new_graph->edges = (EDGE *)calloc(new_graph->numOfedge, sizeof(EDGE));
	for (int i = 1; i <= new_graph->numOfvertex; i++)
		new_graph->vertices[i].name = i;


	set_graph(new_graph);
	return new_graph;
}

void set_graph(GRAPH *graph) {
	int v1, v2, w;
	for (int i = 0; i < graph->numOfedge; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		graph->edges[i].endpoint1 = &graph->vertices[v1];
		graph->edges[i].endpoint2 = &graph->vertices[v2];
		graph->edges[i].weight = w;
	}
}

GRAPH *kruskalMST(GRAPH *graph) {
	KRQ *queue = init_queue(graph); //간선 큐
	KDS *disjSet = init_disjointset(graph); //정점 큐
	GRAPH *MST = spanning_subgraph(graph); //반환할 그래프

	while (!isEdgeListFull(MST)) {
		EDGE *edge = removeMin(graph, queue);

		if (!isInSameSubset(MST, disjSet, edge->endpoint1, edge->endpoint2)) {
			addEdge(MST, edge->endpoint1, edge->endpoint2, edge->weight);
			merge_Subset(MST, disjSet, edge->endpoint1, edge->endpoint2);
		}
	}
	free(queue);
	free(disjSet);
	return MST;
}

KRQ *init_queue(GRAPH *graph) {
	KRQ *newQueue = (KRQ *)calloc(graph->numOfedge, sizeof(KRQ));
	for (int i = 0; i < graph->numOfedge; i++)
		newQueue[i].edge = &graph->edges[i];
	return newQueue;
}

KDS *init_disjointset(GRAPH *graph) {
	KDS *newDisjSet = (KDS *)calloc(graph->numOfvertex, sizeof(KDS));
	for (int i = 0; i < graph->numOfvertex; i++) {
		newDisjSet[i].vertex = &graph->vertices[i + 1];
		newDisjSet[i].subset_ID = i + 1;
	}
	return newDisjSet;
}

GRAPH *spanning_subgraph(GRAPH *graph) {
	GRAPH *spanSubgraph = (GRAPH *)malloc(sizeof(GRAPH));
	spanSubgraph->numOfvertex = graph->numOfvertex;
	spanSubgraph->numOfedge = graph->numOfvertex - 1;

	spanSubgraph->vertices = (VERT *)calloc(spanSubgraph->numOfvertex + 1, sizeof(VERT));
	spanSubgraph->edges = (EDGE *)calloc(spanSubgraph->numOfedge, sizeof(EDGE));
	for (int i = 1; i <= spanSubgraph->numOfvertex; i++)
		spanSubgraph->vertices[i] = graph->vertices[i];

	return spanSubgraph;
}

EDGE *removeMin(GRAPH *graph, KRQ *queue) {
	EDGE *min_ret = NULL;
	int index = 0;

	for (int i = 0; i < graph->numOfedge; i++) { //임의 하나 택.
		if (queue[i].edge != NULL) {
			min_ret = queue[i].edge;
			index = i;
			break;
		}
	}

	for (int i = 0; i < graph->numOfedge; i++) {
		if (queue[i].edge != NULL)
			if (queue[i].edge->weight < min_ret->weight) { //잴 작은 것 택.
				min_ret = queue[i].edge;
				index = i;
			}
	}

	queue[index].edge = NULL; //큐에서 제거
	return min_ret;
}

bool isInSameSubset(GRAPH *graph, KDS *disjSet, VERT *v1, VERT *v2) {
	int subset1 = 0, subset2 = 0;

	for (int i = 0; i < graph->numOfvertex; i++) {
		if (disjSet[i].vertex == v1) subset1 = disjSet[i].subset_ID;
		if (disjSet[i].vertex == v2) subset2 = disjSet[i].subset_ID;
	}

	if (subset1 == subset2) return true;
	else return false;
}

void addEdge(GRAPH *graph, VERT *endpoint1, VERT *endpoint2, int weight) {
	for (int i = 0; i < graph->numOfvertex; i++)
		if (graph->edges[i].endpoint1 == NULL) {
			graph->edges[i].endpoint1 = endpoint1;
			graph->edges[i].endpoint2 = endpoint2;
			graph->edges[i].weight = weight;
			return;
		}
}

void merge_Subset(GRAPH *graph, KDS *disjSet, VERT *v1, VERT *v2) {
	int subset1 = 0, subset2 = 0;

	for (int i = 0; i < graph->numOfvertex; i++) {
		if (disjSet[i].vertex == v1) subset1 = disjSet[i].subset_ID;
		if (disjSet[i].vertex == v2) subset2 = disjSet[i].subset_ID;
	}

	for (int i = 0; i < graph->numOfvertex; i++) {
		if (disjSet[i].subset_ID == subset2) 
			disjSet[i].subset_ID = subset1;
	}
}

bool isQueueEmpty(GRAPH *graph, KRQ *queue) {
	for (int i = 0; i < graph->numOfedge; i++) {
		if (queue[i].edge != NULL) return false;
	}
	return true;
}

bool isEdgeListFull(GRAPH *graph) {
	for (int i = 0; i < graph->numOfedge; i++) { //정점수 - 1
		if (graph->edges[i].endpoint1 == NULL) return false;
	}
	return true;
}

void print_MST(GRAPH *MST) {
	int min_result = 0;
	for (int i = 0; i < MST->numOfedge; i++) {
		printf(" %d", MST->edges[i].weight);
		min_result += MST->edges[i].weight;
	}
	printf("\n%d", min_result);
}

