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

typedef struct incidentEdge {
	int other_connet_vertex, weight;
	struct incidentEdge *next;
}INCE;

typedef struct edge {
	int weight, two_connet_vertex[2];
}EDGE;


void initgraph(GRAPH *graph);
void init_set(GRAPH *graph, int a, int b, int w);
void input_op_a(GRAPH *graph, int n);
void input_op_m(GRAPH *graph, int n1, int n2, int w);

int main() {
	char op = "\0";
	int nodeA, nodeB, weight;

	GRAPH *graph = (GRAPH *)malloc(sizeof(GRAPH));
	initgraph(graph);

	while (1) {
		scanf("%c", &op);
		switch (op){
		case 'a':
			scanf("%d", &nodeA);
			getchar();
			input_op_a(graph, nodeA);
			break;

		case 'm':
			scanf("%d %d %d", &nodeA, &nodeB, &weight);
			getchar();
			input_op_m(graph, nodeA, nodeB, weight);
			break;

		default:
			free(graph);
			return;
		}
	}

}

void initgraph(GRAPH *graph) {
	graph->vertices = (VERT *)calloc(7, sizeof(VERT));
	for (int i = 1; i < 7; i++) {
		graph->vertices[i].incEdge = (INCE *)calloc(1, sizeof(INCE));
	}

	init_set(graph, 1, 2, 1);
	init_set(graph, 1, 3, 1);
	init_set(graph, 1, 4, 1);
	init_set(graph, 1, 6, 2);
	init_set(graph, 2, 1, 1);
	init_set(graph, 2, 3, 1);
	init_set(graph, 3, 1, 1);
	init_set(graph, 3, 2, 1);
	init_set(graph, 3, 5, 4);
	init_set(graph, 4, 1, 1);
	init_set(graph, 5, 3, 4);
	init_set(graph, 5, 5, 4);
	init_set(graph, 5, 6, 3);
	init_set(graph, 6, 1, 2);
	init_set(graph, 6, 5, 3);
}

void init_set(GRAPH *graph, int a, int b, int w) {
	INCE *tmp = graph->vertices[a].incEdge;
	INCE *new = (INCE *)malloc(sizeof(INCE));
	new->other_connet_vertex = b;
	new->weight = w;

	for (;; tmp = tmp->next) {
		if (tmp->next == NULL) {
			new->next = tmp->next;
			tmp->next = new;
			return;
		}
		else if (tmp->next->other_connet_vertex > b) {
			new->next = tmp->next;
			tmp->next = new;
			return;
		}
	}
}

void input_op_a(GRAPH *graph, int n) {


	INCE *tmp = graph->vertices[n].incEdge;
	if (n <= 0 || n >= 7 || tmp->next == NULL) {
		printf("-1\n");
		return;
	}


	tmp = tmp->next;
	for (; tmp!=NULL; tmp = tmp->next) {
		printf(" %d %d", tmp->other_connet_vertex, tmp->weight);
	}
	printf("\n");
}


void input_op_m(GRAPH *graph, int n1, int n2, int w){
	if (n1 <= 0 || n2 <= 0 || n1 >= 7 || n2 >= 7) {
		printf("-1\n");
		return;
	}


	if (w == 0) {
		INCE *tmp = graph->vertices[n1].incEdge;
		INCE *new = (INCE *)malloc(sizeof(INCE));
		for (; ; tmp = tmp->next) {
			if (tmp->next == NULL) return;
			if (tmp->next->other_connet_vertex == n2) {
				break;
			}
		}
		new = tmp->next;
		tmp->next = new->next;
		free(new);

		if (n1 == n2) return;
		INCE *new2 = (INCE *)malloc(sizeof(INCE));
		tmp = graph->vertices[n2].incEdge;
		for (; ; tmp = tmp->next) {
			if (tmp->next->other_connet_vertex == n1) {
				break;
			}
		}
		new2 = tmp->next;
		tmp->next = new2->next;
		free(new2);
	}
	else {
		INCE *tmp = graph->vertices[n1].incEdge;

		//없는경우 추가
		for (;; tmp = tmp->next) {
			if (tmp->next==NULL || tmp->next->other_connet_vertex > n2) {
				INCE *new = (INCE *)malloc(sizeof(INCE));
				new->other_connet_vertex = n2;
				new->weight = w;
				new->next = tmp->next;
				tmp->next = new;
				break;
			}
			if (tmp->next->other_connet_vertex == n2) {
				tmp->next->weight = w;
				break;
			}
		}

		tmp = graph->vertices[n2].incEdge;
		for (;; tmp = tmp->next) {
			if (tmp->next==NULL || tmp->next->other_connet_vertex > n1) {
				INCE *new2 = (INCE *)malloc(sizeof(INCE));
				new2->other_connet_vertex = n1;
				new2->weight = w;
				new2->next = tmp->next;
				tmp->next = new2;
				break;
			}
			if (tmp->next->other_connet_vertex == n1) {
				tmp->next->weight = w;
				break;
			}
		}
	}
}