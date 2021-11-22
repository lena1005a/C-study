#pragma warning(disable:4996)
#include <stdio.h>
#include <string.h>  
#include <stdlib.h> 
#include <stdbool.h>

//DAG (Directed acyclic graph)���� �����Ŭ: �������Ŭ�� ������ϴ� ����׷���
//topological order �������
//����׷����� DAG�� ��������̰� ��������̸� DAG��.

//topologicalSort : ������ ���������� �̿��� ��������
//���� ���� �����ϸ� �����ϴµ�, ���԰����� ���°� �����ϸ� ����Ŭ �����ϴ°���
//ó���� ���԰����� ���� �������� ���
//���԰��� ���� ������ ť�� ����.
//ť���� �̾� ���Ļ��� �����. �ϳ��� ���������� ���԰����� �ʱ�ȭ�ʿ� ->0�Ǹ� ť�� ����
//ť ���������� �ݺ���, ��������� ���ĵǸ� �������ĿϷ�, �ƴϸ� �������Ŭ ����

typedef struct graph {
	struct vertex *vertices;
	struct edge *edges;
	int numOf_vertex, numOf_edge;
}GRAPH;

typedef struct vertex {
	char vertex_name;
	struct incidentEdge *inEdges, *outEdges;
	int inDegree, order_num;
}VERT;

typedef struct edge {
	int originVERTIndex, destinVERTIndex;
} EDGE;

typedef struct incidentEdge {
	int otherEndVERTIndex, EDGEIndex;
	struct incidentEdge *next;
}INCE;


GRAPH *buildGraph();
void insertVertex(GRAPH *graph);
void insertDirEdge(GRAPH *graph);
void insertIncEdge(GRAPH *graph, int originVERTIndex, int destinVERTIndex, int EDGEIndex);
int indexVERT(GRAPH *graph, char v);

void printTopologicalOrder(GRAPH *graph, int *order_arr);
int *topologicalSort(GRAPH *graph);
void enqueue(GRAPH *graph, VERT **queue, VERT* vertex);
VERT *dequeue(GRAPH *graph, VERT **queue);
bool isEmpty(GRAPH *graph, VERT **queue);
bool isFull(GRAPH *graph, VERT **queue);

int main() {
	GRAPH *graph = buildGraph();
	printTopologicalOrder(graph, topologicalSort(graph));
}

GRAPH *buildGraph() {
	GRAPH *make_graph = (GRAPH *)malloc(sizeof(GRAPH));
	insertVertex(make_graph);
	insertDirEdge(make_graph);
	return make_graph;
}

void insertVertex(GRAPH *graph) {
	scanf("%d", &graph->numOf_vertex);
	graph->vertices = (VERT *)calloc(graph->numOf_vertex, sizeof(VERT));
	
	for (int i = 0; i < graph->numOf_vertex; i++) {
		scanf(" %c", &graph->vertices[i].vertex_name);
		graph->vertices[i].inEdges = (INCE *)calloc(1, sizeof(INCE));
		graph->vertices[i].outEdges = (INCE *)calloc(1, sizeof(INCE));
	}
}

void insertDirEdge(GRAPH *graph) {
	char v1, v2;
	scanf("%d", &graph->numOf_edge);
	graph->edges = (EDGE *)calloc(graph->numOf_edge, sizeof(EDGE));

	for (int i = 0; i < graph->numOf_edge; i++) {
		scanf(" %c %c", &v1, &v2);
		graph->edges[i].originVERTIndex = indexVERT(graph, v1);
		graph->edges[i].destinVERTIndex = indexVERT(graph, v2);
		insertIncEdge(graph, graph->edges[i].originVERTIndex, graph->edges[i].destinVERTIndex, i);
	}
}
int indexVERT(GRAPH *graph, char v) {
	for (int i = 0; i < graph->numOf_vertex; i++)
		if (graph->vertices[i].vertex_name == v)
			return i;
}


void insertIncEdge(GRAPH* graph, int originVERTIndex, int destinVERTIndex, int EDGEIndex) {
	INCE *originOutEdge = (INCE *)malloc(sizeof(INCE));
	INCE *destinInEdge = (INCE *)malloc(sizeof(INCE));
	originOutEdge->EDGEIndex = destinInEdge->EDGEIndex = EDGEIndex;

	originOutEdge->otherEndVERTIndex = destinVERTIndex;
	destinInEdge->otherEndVERTIndex = originVERTIndex;

	originOutEdge->next = graph->vertices[originVERTIndex].outEdges->next;
	graph->vertices[originVERTIndex].outEdges->next = originOutEdge;
	destinInEdge->next = graph->vertices[destinVERTIndex].inEdges->next;
	graph->vertices[destinVERTIndex].inEdges->next = destinInEdge;
	graph->vertices[destinVERTIndex].inDegree++;
}


int *topologicalSort(GRAPH *graph) {
	VERT **queue = (VERT **)calloc(graph->numOf_vertex, sizeof(VERT *));
	int *order_arr = (int *)malloc((graph->numOf_vertex + 1) * sizeof(int));
	int order_rank = 0;

	for (int i = 0; i < graph->numOf_vertex; i++)
		if (graph->vertices[i].inDegree == 0)
			enqueue(graph, queue, &graph->vertices[i]); //ť�� �������� ����

	while (!isEmpty(graph, queue)) {
		VERT *vertex = dequeue(graph, queue);
		vertex->order_num = ++order_rank;
		order_arr[order_rank] = indexVERT(graph, vertex->vertex_name);

		for (INCE *vertexOutEdge = vertex->outEdges->next; vertexOutEdge != NULL; vertexOutEdge = vertexOutEdge->next) {
			graph->vertices[vertexOutEdge->otherEndVERTIndex].inDegree--;

			if (graph->vertices[vertexOutEdge->otherEndVERTIndex].inDegree == 0)
				enqueue(graph, queue, &graph->vertices[vertexOutEdge->otherEndVERTIndex]);
		}
	}
	free(queue);

	if (order_rank == graph->numOf_vertex) order_arr[0] = 1; //��� ����
	else order_arr[0] = 0; //�������Ŭ����
	return order_arr;
}

void enqueue(GRAPH *graph, VERT **queue, VERT *vertex) {
	if (isEmpty(graph, queue))
		queue[0] = vertex;

	else {
		for (int i = 0, j = graph->numOf_vertex; i < j; i++)
			if (queue[i % j] != NULL && queue[(i + 1) % j] == NULL) {
				queue[(i + 1) % j] = vertex;
				return;
			}
	}
}

VERT *dequeue(GRAPH *graph, VERT **queue) {
	VERT *vertex;
	if (isFull(graph, queue)) {
		vertex = queue[0];
		queue[0] = NULL;
		return vertex;
	}

	else {
		for (int i = 0, queueSize = graph->numOf_vertex; i < queueSize; i++)
			if (queue[i % queueSize] == NULL && queue[(i + 1) % queueSize] != NULL) {
				vertex = queue[++i % queueSize];
				queue[i % queueSize] = NULL;
				return vertex;
			}
	}
}

bool isEmpty(GRAPH *graph, VERT **queue) {
	for (int i = 0; i < graph->numOf_vertex; i++)
		if (queue[i] != NULL)
			return false;
	return true;
}

bool isFull(GRAPH *graph, VERT **queue) {
	for (int i = 0; i < graph->numOf_vertex; i++)
		if (queue[i] == NULL)
			return false;
	return true;
}


void printTopologicalOrder(GRAPH *graph, int *order_arr) {
	if (order_arr[0])
		for (int i = 1; i <= graph->numOf_vertex; i++)
			printf("%c ", graph->vertices[order_arr[i]].vertex_name);

	else
		printf("0");

	free(order_arr);
	return;
}