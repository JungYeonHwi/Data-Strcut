#ifndef __GRAPH_H__
#define __GRAPH_H__

#define MAX_VERTICES 10

typedef struct {
   int leftmost;
   int rightmost;
} interval;

typedef struct node {
   interval item;
   struct node* next;
} node;

typedef struct {
   int num_vertices;
   node* adj_list[MAX_VERTICES];
   interval map_interval[MAX_VERTICES];
} Graph;

node* add_node(node* n, interval v);
node* delete_node(node* n, interval v);
void construct(Graph* g, char* file);
void print_graph(Graph* g);
int adjacent(Graph* g, interval v, interval u);
int degree(Graph* g, interval v);
void add_vertex(Graph* g, interval v);
void delete_vertex(Graph* g, interval v);
int connectivity(Graph* g);
int two_connectivity(Graph* g);
int two_edge_connectivity(Graph* g);
int shortest_path(Graph* g, interval v, interval u);
void print_error(void);

#endif