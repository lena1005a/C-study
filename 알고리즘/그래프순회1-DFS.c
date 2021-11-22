#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>  
#include <stdlib.h> 


typedef struct graph {
	struct vertex *vertics;
	struct edge *edges;
}GRAPH;

typedef struct vertex {
	int label;
	struct incidentEdge *incEdge;
}VERT;

typedef struct edge {
	int label, e1, e2;
}EDGE;

typedef struct incidentEdge {
	int E_index, opposite_v;
	struct incidentEdge *next;
}INCE;

void init_graph(GRAPH *graph, int n, int m);
void set_graph(GRAPH *graph, int v1, int v2);
int find_edge_index(GRAPH *graph, int v1, int v2);
void DFS(GRAPH *graph, int n, int m, int s);
void rDFS(GRAPH *graph, int pivot_v);

int main() {
	int n, m, s, v1, v2;
	scanf("%d %d %d", &n, &m, &s);

	GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
	init_graph(graph, n, m);

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &v1, &v2);
		set_graph(graph, v1, v2);
	}
	DFS(graph, n, m, s);
}

void init_graph(GRAPH *graph, int n, int m) {
	graph->vertics = (VERT *)calloc(n + 1, sizeof(VERT));
	graph->edges = (EDGE *)calloc(m, sizeof(EDGE));

	for (int i = 1; i <= n; i++) {
		graph->vertics[i].incEdge = (INCE *)calloc(1, sizeof(INCE));
	}
}

void set_graph(GRAPH *graph, int v1, int v2) {
	int e_index = find_edge_index(graph, v1, v2);

	INCE *tmp = graph->vertics[v1].incEdge;
	for (;; tmp = tmp->next) {
		if (tmp->next == NULL || tmp->next->opposite_v > v2) {
			INCE *new = (INCE *)malloc(sizeof(INCE));
			new->opposite_v = v2;
			new->E_index = e_index;
			new->next = tmp->next;
			tmp->next = new;
			break;
		}
	}

	tmp = graph->vertics[v2].incEdge;
	for (;; tmp = tmp->next) {
		if (tmp->next == NULL || tmp->next->opposite_v > v1) {
			INCE *new2 = (INCE *)malloc(sizeof(INCE));
			new2->opposite_v = v1;
			new2->E_index = e_index;
			new2->next = tmp->next;
			tmp->next = new2;
			return;
		}
	}
}

int find_edge_index(GRAPH *graph, int v1, int v2) {
	EDGE *e = graph->edges;
	for (int i = 0; ; i++) {
		if (e[i].e1 == 0 && e[i].e2 == 0) {
			e[i].e1 = v1;
			e[i].e2 = v2;
			return i;
		}
	}
}

void DFS(GRAPH *graph, int n, int m, int s) {
	VERT *v = graph->vertics;
	for (int i = 1; i <= n; i++) {
		v[i].label = 0;
	}

	EDGE *e = graph->edges;
	for (int i = 0; i < m; i++) {
		e[i].label = 0;
	}

	for (int i = 1, pivot_s = s; i <= n; i++, pivot_s = pivot_s % n + 1) {
		if (v[pivot_s].label == 0) rDFS(graph, pivot_s);
	}
}

void rDFS(GRAPH *graph, int pivot_v) {
	VERT *vertex = graph->vertics;
	EDGE *edge = graph->edges;

	printf("%d\n", pivot_v);
	vertex[pivot_v].label = 1;


	INCE *incEdge = graph->vertics[pivot_v].incEdge->next;
	for (; incEdge != NULL; incEdge = incEdge->next) {
		if (edge[incEdge->E_index].label == 0) { //초기는 다 0일것.
			if (vertex[incEdge->opposite_v].label == 0) {
				edge[incEdge->E_index].label = 1;
				rDFS(graph, incEdge->opposite_v);
			}
			else {
				edge[incEdge->E_index].label = 2; //백
			}
		}
	}
}