#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"

#define INIT_CAPACITY 4

static void vector_init(Vector *v) {
    v->size = 0;
    v->capacity = INIT_CAPACITY;
    v->data = (int*)malloc(v->capacity * sizeof(int));
    if (!v->data) exit(1);
}

static void vector_push_back(Vector *v, int x) {
    if (v->size == v->capacity) {
        v->capacity *= 2;
        int *tmp = (int*)realloc(v->data, v->capacity * sizeof(int));
        if (!tmp) exit(1);
        v->data = tmp;
    }
    v->data[v->size++] = x;
}

static void vector_free(Vector *v) {
    free(v->data);
}

typedef struct {
    int *data;
    int head, tail;
    int capacity;
} Queue;

static Queue* queue_create(int capacity) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(capacity * sizeof(int));
    q->head = q->tail = 0;
    q->capacity = capacity;
    return q;
}

static int queue_empty(Queue *q) {
    return q->head == q->tail;
}

static void queue_push(Queue *q, int x) {
    q->data[q->tail++] = x;
}

static int queue_pop(Queue *q) {
    return q->data[q->head++];
}

static void queue_free(Queue *q) {
    free(q->data);
    free(q);
}

Graph* graph_create(int n) {
    Graph *g = (Graph*)malloc(sizeof(Graph));
    if (!g) exit(1);
    g->n = n;
    g->adj = (Vector*)malloc(n * sizeof(Vector));
    if (!g->adj) exit(1);
    for (int i = 0; i < n; ++i) vector_init(&g->adj[i]);
    return g;
}

void graph_add_edge(Graph *g, int u, int v) {
    if (!g || u < 0 || v < 0 || u >= g->n || v >= g->n) return;
    vector_push_back(&g->adj[u], v);
    vector_push_back(&g->adj[v], u);
}

void graph_free(Graph *g) {
    if (!g) return;
    for (int i = 0; i < g->n; ++i) vector_free(&g->adj[i]);
    free(g->adj);
    free(g);
}

static int find_farthest(Graph *g, int start, int *dist, int *visited) {
    for (int i = 0; i < g->n; ++i) dist[i] = -1;
    Queue *q = queue_create(g->n);
    dist[start] = 0;
    queue_push(q, start);
    int farthest = start;
    while (!queue_empty(q)) {
        int v = queue_pop(q);
        visited[v] = 1;
        for (int i = 0; i < g->adj[v].size; ++i) {
            int u = g->adj[v].data[i];
            if (dist[u] == -1) {
                dist[u] = dist[v] + 1;
                queue_push(q, u);
                if (dist[u] > dist[farthest]) farthest = u;
            }
        }
    }
    queue_free(q);
    return farthest;
}

int graph_diameter(Graph *g) {
    if (!g || g->n == 0) return 0;
    int *dist = (int*)malloc(g->n * sizeof(int));
    int *visited = (int*)calloc(g->n, sizeof(int));
    if (!dist || !visited) exit(1);
    int max_diameter = 0;
    for (int i = 0; i < g->n; ++i) {
        if (!visited[i]) {
            int v1 = find_farthest(g, i, dist, visited);
            int v2 = find_farthest(g, v1, dist, visited);
            if (dist[v2] > max_diameter) max_diameter = dist[v2];
        }
    }

    free(dist);
    free(visited);
    return max_diameter;
}

GraphIterator graph_iter(Graph *g) {
    GraphIterator it = { g, 0 };
    return it;
}

int graph_next(GraphIterator *it) {
    if (it->current >= it->g->n) return -1;
    return it->current++;
}
