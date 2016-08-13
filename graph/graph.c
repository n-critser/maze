#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "graph.h"
#define INFINITY 99999999.999999
struct listElement {
        int sink;
        double weight;
};

/*
  a simple directed weighted graph 
  adjList is an 2d-array size == vertices
  adjList[vertices][vertices]
 */
struct graph {
        int vertices;
        int edges;
        
        struct listElement**  adjList;
};



void graph_alloc_adjList(Graph g){
        assert (g);
        assert (g->vertices && (g->vertices > 0));
        g->adjList=malloc(sizeof(struct listElement *)* g->vertices);
        int i;
        for ( i = 0 ; i < g->vertices; i++){
                g->adjList[i]=malloc(sizeof(struct listElement) * g->vertices);
                assert(g->adjList[i]);
        }
        assert(i == g->vertices);
}

void graph_set_adjList_default_values(Graph g){
        int i,j;
        for (i =0 ; i < g->vertices; i++){
                for(j=0; j< g->vertices; j++){
                        g->adjList[i][j].sink=-1;
                        g->adjList[i][j].weight=INFINITY;
                        //printf("adkList[%d][%d].sink= %d\n",i,j,g->adjList[i][j].sink);
                        //printf("adkList[%d][%d].weight= %f\n",i,j,g->adjList[i][j].weight);
                }
        }
        /*
          if sink != -1 then this is a valid edge
          if weight != INFINITY then edge is weighted

         */
}

int graph_add_edge(Graph g , int source , int sink , double weight){
        assert(source >= 0);
        assert(source < g->vertices);
        assert(sink >=0);
        assert(sink < g->vertices);
        printf("source:%d , sink:%d , weight:%f\n",source,sink,weight);
        if (g->adjList[source][sink].sink==-1){
                g->adjList[source][sink].sink=sink;
                g->adjList[source][sink].weight=weight;
                return 0;
        } else  if (g->adjList[source][sink].sink!=-1){
                g->adjList[source][sink].weight=weight;
                return 1;
        }
        return -1;
}


/*
  Can we create a graph whose vertices count can be increased
  or decreased? 
 */
Graph graph_init(int vertices){
        Graph G1;

        G1=malloc(sizeof(struct graph));
        if ( !G1){
                return NULL;
        }
        G1->vertices=vertices;
        return G1;
}

int graph_has_edge(Graph g, int source, int sink){
        if (((source <0 )||(sink < 0)) ||
            ((source >g->vertices)|| (sink > g->vertices))){
                return -1;
        }
                
        return g->adjList[source][sink].sink;
}

void graph_destroy(Graph g){

        int i ;
        for ( i = 0; i < g->vertices ; i++){
                free( g->adjList[i]);
        }
        free(g->adjList);
        free(g);
}
