typedef struct graph * Graph;
void graph_alloc_adjList(Graph);
void graph_set_adjList_default_values(Graph);
int graph_add_edge(Graph , int , int , double );
Graph graph_init(int);
int graph_has_edge(Graph , int , int );
void graph_destroy(Graph );
