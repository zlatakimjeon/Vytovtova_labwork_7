#include <stdio.h>
#include <assert.h>
#include "../include/graph.h"

void test_empty() {
    Graph *g = graph_create(0);
    assert(graph_diameter(g) == 0);
    graph_free(g);
    printf("test_empty passed\n");
}

void test_line() {
    Graph *g = graph_create(4);
    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 2, 3);
    assert(graph_diameter(g) == 3);
    graph_free(g);
    printf("test_line passed\n");
}

void test_cycle() {
    Graph *g = graph_create(4);
    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 2, 3);
    graph_add_edge(g, 3, 0);
    assert(graph_diameter(g) == 2);
    graph_free(g);
    printf("test_cycle passed\n");
}

void test_iterator() {
    Graph *g = graph_create(5);
    GraphIterator it = graph_iter(g);
    int count = 0;
    while (graph_next(&it) != -1) count++;
    assert(count == 5);
    graph_free(g);
    printf("test_iterator passed\n");
}

void test_disconnected() {
    Graph *g = graph_create(6);
    graph_add_edge(g, 0, 1);
    graph_add_edge(g, 1, 2);
    graph_add_edge(g, 3, 4);
    assert(graph_diameter(g) == 2);
    graph_free(g);
    printf("test_disconnected passed\n");
}

int main() {
    test_empty();
    test_line();
    test_cycle();
    test_iterator();
    test_disconnected();
    printf("All tests passed\n");
    return 0;
}
