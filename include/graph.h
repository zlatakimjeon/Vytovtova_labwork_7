#ifndef GRAPH_H
#define GRAPH_H

typedef struct {
    int *data;
    int size;
    int capacity;
} Vector;

typedef struct {
    int n;
    Vector *adj;
} Graph;

Graph* graph_create(int n);
void graph_add_edge(Graph *g, int u, int v);
void graph_free(Graph *g);
int graph_diameter(Graph *g);

typedef struct {
    Graph *g;
    int current;
} GraphIterator;

GraphIterator graph_iter(Graph *g);
int graph_next(GraphIterator *it);

#endif
