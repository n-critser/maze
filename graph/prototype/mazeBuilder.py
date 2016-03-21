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
    """create list of legal moves based on graph dims"""
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
    moveList=maze_init_legal_move_list(graph,source)
    if sink in moveList:
        print "move **IS** legal"
        return True
    else:
        print "move is *NOT* legal"
        return False

    
def maze_add_edge(graph,source,sink):
    """adds edge from source to sink
    after testing if move is legal"""
    if (maze_check_legal_move(graph,source,sink)):
        # directed graph add only single edge
        graph.graph_add_edge(source,sink)
        # undirected graph add reverse edge 
        graph.graph_add_edge(sink,source)
        return True
    print "source: %d , sink: %d"%(source,sink)
    print graph.graph_return_stats()
    return False

def maze_init(vertices,dimension):
    """initialize a maze  """
    mGraph=gh.Graph(vertices,dimension)
    return mGraph


def maze_build_path(graph,source,sink,searchMethod):
    # use dfs or bfs to build a path from source to sink
    path = []
    
    if maze_add_edge(graph,source,sink):
        return 0
    else :
        moveList=maze_init_legal_move_list(graph,source)
        while(source != sink):
            maze_add_edge(graph,source,moveList[1])
        
    return 1

#int number_of_walls = 2*m*n - m - n;
#		bool is_wall[number_of_walls];


# format and print behavior from 
# Douglas Wilhelm Harder
# https://ece.uwaterloo.ca/~dwharder/aads/Algorithms/Maze_generation/
def maze_print(graph):
    n = graph.n/graph.dim
    m = graph.dim
    print "n: %d , m: %d"%(n,m)
    is_wall=[]
    for r in range(0,(2*m*n-m-n)):
        is_wall.append(True)
    topString=""

    print "+  +",
    
    for i in range(0, n - 1 ):
        print "--+",
        wall_counter = 0
    print ""
    for i in range(0, m - 1):
        # Print the vertical walls of the ith row.
        print "|",
        for j in range(0,n-1):
            if ( is_wall[wall_counter] ) :
                    print "  |",
            else :
                print "   ",
            ++wall_counter
        # end inner vertical wall 
        print "  |" 
        
        # Print the horizontal walls of the ith row:
        #  - these are the walls between the ith and (i + 1)st rows.
        print "+",
        for j in range(0, n ):
            if ( is_wall[wall_counter] ) :
                print "--+",
            else :
                print "  +",
		

            ++wall_counter
        print ""
        # end horizontal walls of ith row
    # end ith row printing 
    #Print the horizontal(vertical?) walls of the last row.
    print "|",
    for k in range(0,n-1):
        if ( is_wall[wall_counter] ):
            print "  |",
        else :
            print "   ",
            
                
        ++wall_counter
    print "  |" 
    # end
    #Print the bottom border.
    for p in range(0,n-1):
        print "+--",
    print "+  +\n" 
    # end

#################################################
## testing 
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
#print graph.graph_show_graph()
maze_print(graph)
