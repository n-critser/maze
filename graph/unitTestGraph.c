#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "graph.h"
int main(int argv, char ** argc){
        Graph G1;
        int vertices=12;
        G1=graph_init(vertices);
        assert(G1);
        //assert(G1->vertices);


        graph_alloc_adjList(G1);
        graph_set_adjList_default_values(G1);

        int retVal=graph_add_edge(G1,1,2,5.8);
        assert(retVal>-1);
        int i;
        for (i = 0; i < vertices; i++){
                int sink = i+1 < vertices ? i+1:0;
                retVal=graph_add_edge(G1,i,sink,1.3*i);
                //printf("retVal : %d\n",retVal);
                assert(retVal > -1);
                retVal=graph_has_edge(G1,i,sink);
                assert(retVal > -1);
                // test sink greater than vertices has_edge
                retVal=graph_has_edge(G1,i,sink+(2*vertices));
                assert(retVal < 0);
        }

        graph_destroy(G1);
        return 0;
}
