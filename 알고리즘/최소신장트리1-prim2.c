#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>  
#include <stdlib.h> 
#include <stdbool.h>

typedef struct GRAPH {
	struct vertex *vertices;
	struct edge *edges;
	int numOfvertex, numOfedge;
}GRAPH;


typedef struct vertex {
	int vertex_name, w_distance;
	struct incident *incEdge;
	struct edge *parentEdge;

}VERT;

typedef struct edge {
	int vertex1, vertex2, weight;
}EDGE;

typedef struct incident {
	struct incident *next;
	int oppsite_vertex, edge_index;
}INCE;

typedef struct prim_queue {
	struct vertex *prq_vertex;
} PRQ;

GRAPH *init_graph();
void prim_MST(GRAPH *graph);

VERT *removeMin(GRAPH *graph, PRQ *queue);
bool isEmpty_queue(PRQ *queue, int vertex_cnt);
bool isElement(PRQ *queue, VERT *vertex, int vertex_cnt);

int main() {
	GRAPH *graph = init_graph();
	prim_MST(graph);
}

GRAPH *init_graph() {
	GRAPH *new_graph = (GRAPH *)malloc(sizeof(GRAPH));
	scanf("%d %d", &new_graph->numOfvertex, &new_graph->numOfedge);

	new_graph->vertices = (VERT *)calloc(new_graph->numOfvertex, sizeof(VERT));
	new_graph->edges = (EDGE *)calloc(new_graph->numOfedge, sizeof(EDGE));
	for (int i = 0; i < new_graph->numOfvertex; i++) {
		new_graph->vertices[i].incEdge = (INCE *)calloc(1, sizeof(INCE));
		new_graph->vertices[i].vertex_name = i;
	}

	int v1, v2, w;
	for (int i = 0; i < new_graph->numOfedge; i++) {
		scanf("%d %d %d", &v1, &v2, &w);
		v1--;
		v2--;
		new_graph->edges[i].vertex1 = v1;
		new_graph->edges[i].vertex2 = v2;
		new_graph->edges[i].weight = w;

		INCE *e1 = (INCE *)calloc(1, sizeof(INCE));
		INCE *e2 = (INCE *)calloc(1, sizeof(INCE));
		e1->oppsite_vertex = v2;
		e2->oppsite_vertex = v1;
		e1->edge_index = e2->edge_index = i;

		//.
		e1->next = new_graph->vertices[v1].incEdge->next;
		e2->next = new_graph->vertices[v2].incEdge->next;

		new_graph->vertices[v1].incEdge->next = e1;
		new_graph->vertices[v2].incEdge->next = e2;
	}

	return new_graph;
}


void prim_MST(GRAPH *graph) {
	int result_min_w = 0;
	PRQ *queue = (PRQ *)calloc(graph->numOfvertex, sizeof(PRQ));

	for (int i = 0; i < graph->numOfvertex; i++) {
		graph->vertices[i].w_distance = -1;
		queue[i].prq_vertex = &graph->vertices[i];
	}

	//처음 정점부터 시작
	graph->vertices[0].w_distance = 0;
	while (!(isEmpty_queue(queue, graph->numOfvertex))) {
		VERT *v_tmp = removeMin(graph, queue);
		EDGE *e_tmp = graph->edges;
		printf(" %d", v_tmp->vertex_name + 1);


		for (INCE *e = v_tmp->incEdge->next; e != NULL; e = e->next) {
			VERT *v = &graph->vertices[e->oppsite_vertex];

			if (isElement(queue, v, graph->numOfvertex)) {
				if (v->w_distance == -1 || e_tmp[e->edge_index].weight < v->w_distance) {
					v->w_distance = e_tmp[e->edge_index].weight;
					v->parentEdge = &e_tmp[e->edge_index];
				}
			}
		}	
	}
	for (int i = 0; i < graph->numOfvertex; i++) {
		if (graph->vertices[i].parentEdge != NULL) {
			result_min_w += graph->vertices[i].parentEdge->weight;
		}
	}
	printf("\n%d", result_min_w);

}

VERT *removeMin(GRAPH *graph, PRQ *queue) {
	VERT *tmp = NULL;
	int min_index = 0;
	for (int i = 0; i < graph->numOfvertex; i++) {
		if (queue[i].prq_vertex != NULL && queue[i].prq_vertex->w_distance != -1) {
			tmp = queue[i].prq_vertex;
			min_index = i;
			break;
		}
	}


	for (int i = 0; i < graph->numOfvertex; i++) {
		if (queue[i].prq_vertex != NULL) {
			if (queue[i].prq_vertex->w_distance != -1 && queue[i].prq_vertex->w_distance < tmp->w_distance) {
				tmp = queue[i].prq_vertex;
				min_index = i;
			}
		}
	}

	queue[min_index].prq_vertex = NULL;
	return tmp;
}

bool isEmpty_queue(PRQ *queue, int vertex_cnt) {
	for (int i = 0; i < vertex_cnt; i++) {
		if (queue[i].prq_vertex != NULL) return false;
	}
	return true;
}
bool isElement(PRQ *queue, VERT *vertex, int vertex_cnt) {
	for (int i = 0; i < vertex_cnt; i++) {
		if (vertex == queue[i].prq_vertex) return true;
	}
	return false;
}

