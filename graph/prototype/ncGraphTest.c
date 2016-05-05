#include "graph.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define TEST1_SIZE (31)
#define TEST2_SIZE (2)


int main(int argc, char ** argv){
        // pointer of type graph from graph.h
        Graph gh;
        int rows;
        int cols;
        
        
        gh = graph_create(TEST1_SIZE);
        assert(graph_vertex_count(gh) == TEST1_SIZE);

        /* */
        graph_add_edge(gh,1,2);
        assert(graph_edge_count(gh)==1);
        assert(graph_has_edge(gh,1,2));
        assert(graph_out_degree(gh,1)==1);
        /*
          graphs are directed so below fails
          assert(graph_has_edge(gh,2,1));       
        */
        
        return 0;
}
