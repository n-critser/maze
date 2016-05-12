#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "graph.h"
#include "mazeSearch.h"
/*srand for now*/
#include <time.h>




/* create an array of n ints initialized to SEARCH_INFO_NULL */
static int *
create_empty_array(int n)
{
    int *a;
    int i;

    a = malloc(sizeof(*a) * n);
    assert(a);

    for(i = 0; i < n; i++) {
        a[i] = SEARCH_INFO_NULL;
    }

    return a;
}

/* used inside search routines */
struct edge {
        int u;          /* source */
        int v;          /* sink */
        int w;          /* weight */
};

/*create a heap of edges for now can be a sorted array of edges */
struct heap {
        struct edge *e;
        int partition;
        int min;
};

/* FIXME: add asserts and  unit test heap */
/* FIXME: add heapInsert , percolateDown, and getMin for heap*/
struct heap * initEdgeHeap(Graph g){
        struct heap * eH;
        eH = malloc(sizeof(*eH));
        eH->e = malloc(sizeof(*eH->e) * (graph_edge_count(g) + 1));
        assert(eH);
        return eH;
};
        

/* allocate and initialize search results structure */
/* you need to do this before passing it to dfs or bfs */
struct search_info *
search_info_create(Graph g)
{
    struct search_info *s;
    int n;
    srand(time(NULL));
    s = malloc(sizeof(*s));
    assert(s);

    s->graph = g;
    s->reached = 0;

    n = graph_vertex_count(g);

    s->preorder = create_empty_array(n);
    s->time = create_empty_array(n);
    s->parent = create_empty_array(n);
    s->depth = create_empty_array(n);
    s->edgeHeap=initEdgeHeap(g);
    return s;
} 

/* free search_info data---does NOT free graph pointer */
void
search_info_destroy(struct search_info *s)
{
    free(s->depth);
    free(s->parent);
    free(s->time);
    free(s->preorder);
    free(s);
}


/* stack/queue */
struct queue {
    struct edge *e;
    int bottom;
    int top;
};

static void
push_edge(Graph g, int u, int v, void *data)
{
    struct queue *q;

    q = data;

    assert(q->top < graph_edge_count(g) + 1);
    /*FIXME: weight function needs to be at Graph level */
    /*FIXME: sort by weight needs full list of edges ie: another array in the search_info struct*/
    /* add random edge weight for now  */
    int r = rand();
    assert (r);
    printf ("random weight: %d\n",r);
    q->e[q->top].w = r;
    q->e[q->top].u = u;
    q->e[q->top].v = v;
    q->top++;
}

/* this rather horrible function implements dfs if use_queue == 0 */
/* and bfs if use_queue == 1 */
static void
generic_search(struct search_info *r, int root, int use_queue)
{
    /* queue/stack */
    struct queue q;

    /* edge we are working on */
    struct edge cur;
    
    /* start with empty q */
    /* we need one space per edge */
    /* plus one for the fake (root, root) edge */
    q.e = malloc(sizeof(*q.e) * (graph_edge_count(r->graph) + 1));
    assert(q.e);
    
    q.bottom = q.top = 0;
    
    /* push the root */
    push_edge(r->graph, root, root, &q);

    /* while q.e not empty */
    while(q.bottom < q.top) {
            //printf ("q.top: %d, q.bottom: %d" ,q.top,q.bottom);
        if(use_queue) {
            cur = q.e[q.bottom++];
        } else {
            cur = q.e[--q.top];
        }
        
        /* did we visit sink already? */
        if(r->parent[cur.v] != SEARCH_INFO_NULL) continue;

        /* no */
        assert(r->reached < graph_vertex_count(r->graph));
        r->parent[cur.v] = cur.u;
        r->time[cur.v] = r->reached;
        r->preorder[r->reached++] = cur.v;
        if(cur.u == cur.v) {
            /* we could avoid this if we were certain SEARCH_INFO_NULL */
            /* would never be anything but -1 */
            r->depth[cur.v] = 0;
        } else {
            r->depth[cur.v] = r->depth[cur.u] + 1;
            printf( "r->depth[%d] :%d\n",cur.v,r->depth[cur.v]);
        }

        /* push all outgoing edges */
        graph_foreach(r->graph, cur.v, push_edge, &q);
    }

    free(q.e);
}

void
dfs(struct search_info *results, int root)
{
    generic_search(results, root, 0);
}

void
bfs(struct search_info *results, int root)
{
    generic_search(results, root, 1);
}

int isConnected(struct search_info *results){
        generic_search(results,0,0);
        int edgeCount;
        int edgeValidation;
        int sizeOfPreOrder;
        int i;
        int nullParent;
        nullParent=1;
        for (i=0 ; i < graph_vertex_count(results->graph);i++){
                if (results->parent[i]==SEARCH_INFO_NULL){
                        nullParent=0;
                        break;
                }
        }
        edgeCount=graph_edge_count(results->graph) ;
        
        edgeValidation=(edgeCount>=graph_vertex_count(results->graph)) ? 1 : 0;
        sizeOfPreOrder=(sizeof(results->preorder)/sizeof(int));
        printf ("sizeOfPreOrder:%d",sizeOfPreOrder);
        return nullParent && edgeValidation;
}

/*converts the graph associated with results into a MST graph with the save V,E */
int kruskalMST(struct search_info * results){
        Graph gTemp;
        assert(gTemp);
        return -9;
}
