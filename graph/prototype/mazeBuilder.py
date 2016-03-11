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
def maze_check_legal_move(graph,source,sink):

    if source == 0 or  source ==graph.n-(graph.dim-1):
        print "found a left corner"
    elif source == graph.dim -1 or source ==graph.n:
        print "found a right corner"
    #top row not a corner
    elif source / graph.dim == 0:
        print "****top row not a corner"
    #bottom row not a corner
    elif (source/graph.dim) == (graph.n-1)/graph.dim:
        print "****not a corner botton row"
        print "(source/graph.dim)",(source/graph.dim)
        print "graphn-1/grpha.dim:",(graph.n-1)/graph.dim

    elif (source % graph.dim) == 0:
        print "left column"

    elif (source % graph.dim) ==graph.dim-1:
        print "right column"
    print "divide",source/graph.dim
    print "mod",source%graph.dim
    # elif left column
    # elif right column
    # else out of bounds ?
        
    return True

def maze_add_edge(graph,source,sink):
    if (maze_check_legal_move(graph,source,sink)):
        graph.graph_add_edge(source,sink)
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
maze_add_edge(graph,3,6)
maze_add_edge(graph,6,9)
maze_add_edge(graph,8,9)
maze_add_edge(graph,15,14)
maze_add_edge(graph,30,31)
maze_add_edge(graph,26,18)
print graph
print graph.graph_show_graph()
