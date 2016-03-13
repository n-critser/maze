#! /usr/bin/env python
#import prettyprint
import json
import pprint
import random
import graph as gh

# classes necessary representing a graph
# vertex, edge , graph
"""
maze requirements
1. graph
2. dimensions to determine potential moves
3. Graph(int vertices, int dimesion ) :
    # of vertices can be anything
    dimension is the dimension square of the maze
4. what happens if the dimension and vertices don't divide evenly ?
    maze will add vertices to create a complete graph for the whole maze
5. based on (vertices,dim) maze will be constructed by
   making edges between vertices that are LEGAL.
6. the resulting maze will be saved to a file named by its graph information
   - degree , vertices, edges, edge list, +++
7. 

"""
moves=("north","east","south","west")
print moves
print moves[1]
def maze_init_legal_move_list(graph,source):
    legalMoves=[]
    if (source % graph.dim) == 0:
        assert source % graph.dim ==0
        legalMoves.append(source+1)
        
        print "left column"
        #if source == 0 or  source ==graph.n-(graph.dim-1):
        #    print "found a left corner"
            # add source+1 and source+graph.dim (if source+graph.dim < graph.n)
        if source+graph.dim < graph.n:
            legalMoves.append(source+graph.dim)
        if source-graph.dim > 0:
            legalMoves.append(source-graph.dim)
    elif (source % graph.dim) ==graph.dim-1:
        legalMoves.append(source-1)
        print "right column"
        #if source == graph.dim -1 or source ==graph.n-1:
        #print "found a right corner"
        if (source+graph.dim) < graph.n:
            legalMoves.append((source)+graph.dim)
        if (source-graph.dim) > 0:
            legalMoves.append(source-graph.dim)
    #top row not a corner
    elif source / graph.dim == 0:
        assert source - graph.dim < 0
        assert source + graph.dim < graph.n
        legalMoves.append(source-1)
        legalMoves.append(source+1)
        if (source + graph.dim < graph.n):
            legalMoves.append(source+graph.dim)
        print "****top row not a corner"
    #bottom row not a corner
    elif (source/graph.dim) == (graph.n-1)/graph.dim:
        assert source - graph.dim < graph.n
        assert source + graph.dim > graph.n
        print "****not a corner botton row"
        legalMoves.append(source-1)
        legalMoves.append(source+1)
        if (source - graph.dim < graph.n and source - graph.dim > 0):
            legalMoves.append(source-graph.dim)
        #print "(source/graph.dim)",(source/graph.dim)
        #print "graphn-1/grpha.dim:",(graph.n-1)/graph.dim
    else :
        # we should only reach this else when the source is valid
        # and when source is not an edge node so add all 4 legal moves
        assert source >= 0
        assert source < graph.n
        print "*ELSE* CONdition 4 legal moves"
        legalMoves.append(source-1)
        legalMoves.append(source+1)
        legalMoves.append(source+graph.dim)
        legalMoves.append(source-graph.dim)
        
    # else out of bounds ?
    print legalMoves
    return legalMoves
def maze_check_legal_move(graph,source,sink):
    moves=maze_init_legal_move_list(graph,source)
    if sink in moves:
        print "move **IS** legal"
        return True
    else:
        print "move is *NOT* legal"
        return False
def maze_add_edge(graph,source,sink):
    if (maze_check_legal_move(graph,source,sink)):
        # directed graph add only single edge
        graph.graph_add_edge(source,sink)
        # undirected graph add reverse edge 
        graph.graph_add_edge(sink,source)
    print "source: %d , sink: %d"%(source,sink)
    print graph.graph_return_stats()
    return 0
def maze_init(vertices,dimension):
    """initialize a maze  """
    mGraph=gh.Graph(vertices,dimension)
    # create legal move list
    # create
    print mGraph.graph_return_stats()    
    return mGraph

graph = maze_init(32,8)

maze_add_edge(graph,1,2)
maze_add_edge(graph,0,1)
maze_add_edge(graph,2,3)
maze_add_edge(graph,3,11)
maze_add_edge(graph,7,6)
maze_add_edge(graph,15,14)
maze_add_edge(graph,10,18)
maze_add_edge(graph,30,31)
maze_add_edge(graph,26,18)
print graph
print graph.graph_show_graph()
