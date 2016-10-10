#! /usr/bin/env python
#import prettyprint
import json
import pprint
import random
import graph as gh
import logging
from collections import deque

import inspect

def lineno():
    """Returns the current line number in our program."""
    return inspect.currentframe().f_back.f_lineno
FORMAT = '%(asctime)-15s %(linenum)s %(method)-8s %(message)s'
logging.basicConfig(format=FORMAT, level=logging.DEBUG)
d = {'linenum': lineno(), 'method': 'main'}
logger = logging.getLogger('mazeBuilder')
logger.warning('Starting File: %s', 'mazeBuilder.py', extra=d)

# classes necessary representing a maze
#  graph, search, maze 
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
#print moves
#print moves[1]
def maze_init_legal_move_list(graph,source):
    """create list of legal moves based on graph dims"""
    assert(source < graph.n)
    assert(source >= 0)
    legalMoves=[-1,-1,-1,-1]
    # north
    if source-graph.dim > 0 :
        legalMoves[0]=(source-graph.dim)
    #south
    if source+graph.dim < graph.n:
        legalMoves[3]=source+graph.dim

    # left column
    if (source % graph.dim) == 0:
        assert source % graph.dim ==0
        #print "left column"
        # east
        legalMoves[1]=source+1
        # west
    # right column
    elif (source % graph.dim) ==graph.dim-1:
        #print "right column"
        #east nop
        #west
        legalMoves[2]=source-1
    #top row not a corner
    elif source / graph.dim == 0:
        assert source - graph.dim < 0
        assert source + graph.dim < graph.n
        #east 
        legalMoves[1]=source+1
        #west
        legalMoves[2]=source-1
        #print "****top row not a corner"
    #bottom row not a corner
    elif (source/graph.dim) == (graph.n-1)/graph.dim:
        assert source - graph.dim < graph.n
        assert source + graph.dim > graph.n
        #print "****not a corner botton row"
        #east 
        legalMoves[1]=source+1
        #west
        legalMoves[2]=source-1
    else :
        # we should only reach this else when the source is valid
        # and when source is not an edge node so add all 4 legal moves
        #print "*ELSE* CONdition 4 legal moves"
        #east 
        legalMoves[1]=source+1
        #west
        legalMoves[2]=source-1
        
    # else out of bounds ?
    #print legalMoves
    return legalMoves

def maze_check_legal_move(graph,source,sink):
    moveList=maze_init_legal_move_list(graph,source)
    if sink in moveList:
        #print "move **IS** legal"
        return True
    else:
        #print "move is *NOT* legal"
        return False

        
    
def maze_add_edge(graph,source,sink):
    """adds edge from source to sink
    after testing if move is legal"""
    if (maze_check_legal_move(graph,source,sink)):
        # directed graph add only single edge
        theWall= maze_find_wall_between_vertices(graph,source,sink)
        graph.is_wall[theWall]=False
        graph.graph_add_edge(source,sink)
        # undirected graph add reverse edge 
        graph.graph_add_edge(sink,source)
        #maze_print(graph)
        return True
    
    print "source: %d , sink: %d"%(source,sink)
    #print graph.graph_return_stats()
    return False

# global vars to be moved into class

def maze_init(vertices,dimension):
    is_wall=[]
    wallCount=-1
    """initialize a maze  """
    mGraph=gh.Graph(vertices,dimension)
    n = mGraph.dim
    m = mGraph.n/mGraph.dim
    e = mGraph.m
    print "n: %d , m: %d"%(n,m)

    wallCount=(2*m*n)-m-n
    mGraph.wallCount=wallCount
    
    for r in range(0,wallCount): #(2*m*n-m-n)
        is_wall.append(True)
    mGraph.is_wall=is_wall
    print "mGraph.is_wall:",mGraph.is_wall
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
    logger.warning('starting %s ', 'maze_print', extra={'linenum': lineno(),'method':''})
    n = graph.dim # columns
    m = graph.n/graph.dim # rows
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
            if ( graph.is_wall[wall_counter] ) :
                    print "  |",
            else :
                print "   ",
            wall_counter+=1
        # end inner vertical wall 
        print "  |" 
        
        # Print the horizontal walls of the ith row:
        #  - these are the walls between the ith and (i + 1)st rows.
        print "+",
        for j in range(0, n ):
            if ( graph.is_wall[wall_counter] ) :
                print "--+",
            else :
                print "  +",
		

            wall_counter+=1
        print ""
        # end horizontal walls of ith row
    # end ith row printing 
    #Print the horizontal(vertical?) walls of the last row.
    print "|",
    for k in range(0,n-1):
        if ( graph.is_wall[wall_counter] ):
            print "  |",
        else :
            print "   ",
            
                
        wall_counter+=1
    print "  |" 
    # end
    #Print the bottom border.
    for p in range(0,n-1):
        print "+--",
    print "+  +\n"
    # end
    # end of maze_print
"""
need to do the reverse of this
###############################
void find_adjacent_rooms( int room[2], int wall, int n ) {
		// Determine which row and column 
		int row =    wall / (2*n - 1);
		int column = wall % (2*n - 1);

		// Determine which rooms they connect
		if ( column < n - 1 ) {
			// A vertical wall
			room[0] = n*row + column;
			room[1] = n*row + column + 1;
		} else {
			// A horizontal wall
			column += 1 - n;

			room[0] = n* row      + column;
			room[1] = n*(row + 1) + column;
		}
	}
"""

def maze_find_move_direction(graph,source,sink):
    assert (source >= 0 )
    assert (source < graph.n)
    assert (sink >= 0 )
    assert (sink < graph.n)
    if (sink == source-graph.dim):
        return 0
    elif (sink == source +1):
        return 1
    elif (sink == source -1):
        return 2
    elif (sink == source + graph.dim):
        return 3
    else:
        raise Exception("Error calculating move direction")
    
def maze_find_wall_between_vertices(graph,source,sink):
    assert (source >= 0 )
    assert (source < graph.n)
    assert (sink >= 0 )
    assert (sink < graph.n)
    wall = -1
    moveDir=maze_find_move_direction(graph,source,sink)
    moveList=maze_init_legal_move_list(graph,source)
    direction=maze_find_move_direction(graph,source,sink)
    sourceRow=source/graph.dim
    sourceCol=source%graph.dim
    # make a list of available walls corresponding to adjacent nodes
    wallList=[-1,-1,-1,-1]
    # NORTHWALL goes negative if the source node is on the top row
    # this goes after the legal move test , so northwall negative doesn't matter now
    northWall=(((source/graph.dim)*(graph.dim-1)+((source/graph.dim)-1)*graph.dim)+ source%graph.dim)
    wallList[0]=northWall
    rightWall=northWall+graph.dim
    wallList[1]=rightWall
    leftWall=northWall+graph.dim-1
    wallList[2]=leftWall
    bottomWall=rightWall+graph.dim-1
    wallList[3]=bottomWall
    #print "wallList:",wallList
    #print "source:%d , sink:%d, sourceRow:%d , sourceCol:%d "%(source, sink, sourceRow,sourceCol), "\nmoveList:",moveList , "\nWall:%d"%(wallList[moveDir])
    return wallList[moveDir]#northWall#littleNode  #  
"""
wallCount = 2*m*n-m-n
m : 8 , n : 4
+  + --+ --+ --+ 
|   |   |   |   |
+ --+ --+ --+ --+ 
|   |   |   |   |
+ --+ --+ --+ --+ 
|   |   |   |   |
+ --+ --+ --+ --+ 
|   |   |   |   |
+ --+ --+ --+ --+ 
|   |   |   |   |
+ --+ --+ --+ --+ 
|   |   |   |   |
+ --+ --+ --+ --+ 
|   |   |   |   |
+ --+ --+ --+ --+ 
|   |   |   |   |
+-- +-- +-- +  +

internal vertical = graph.dim -1 (0-graph.dim-2)
internal horizontal= graph.dim
each row has = graph.dim-2 + graph.dim = 14 walls
wallX % graph.dim

take the bottom wall from your upstairs neighbor.(your top wall)

node0: (wall0,wall7)
node1: (wall0,wall1,wall8)
node8: (wall7,wall15,wall22)
node16: (wall22,above+graph.dim=w30rightwall,rightwall+graph.dim-1=37bottomwall)
16srow=16/graph.dim=2 ( row 2 of 0,1,2) ( 2 vertical and 1 horizontal wall rows above)
( 16srow*(graph.dim-1)+(16srow-1)*graph.dim ) = 2*7+1*8 = 22

Wall count starts at first internal vertical wall.
    | w0                 | w6 - graph.dim-2 =7
    v                       v 
+  + --+ --+ --+ --+ --+ --+ --+ 
|   |   |   |   |   |   |   |   | <--V--w(0-6) graph.dim-1 * graph.n / graph.dim 
+ --+ --+ --+ --+ --+ --+ --+ --+ <--H--w(7-14) graph.dim * (graph.n/graph.dim) -1
|   |   |   |   |   |   |   |   | <--V--w(15-21)
+ --+ --+ --+ --+ --+ --+ --+ --+ <--H--w(22-29)
|   |   |   |   |   |   |   |   | <--V--w(30-36)
+ --+ --+ --+ --+ --+ --+ --+ --+ <--H--w(37-44)
|   |   |   |   |   |   |   |   | <--V--w(45-51)
+-- +-- +-- +-- +-- +-- +-- +  +

28+24=52

m : 4 , n : 8 --TODO: CHANGE to cols and rows

wallCount mod graph.dim: 4  
wallCount: 52

from source to sink

if direction is east or west wall will be
if source = 8 vertical walls start at 15 ( 8*2-1)=
A nodes north wall =  (((node/graph.dim)*(graph.dim-1)+((node/graph.dim)-1)*graph.dim)+ node%graph.dim) = 
if source = 16 horizontal wall at ((2*(7)+(2-1)*8)+ 0) =14+8=22
"""
    
#################################################
## testing 
#graph = maze_init(32,8)
graph = maze_init(16,4)
maze_add_edge(graph,1,2)

maze_add_edge(graph,0,1)
maze_add_edge(graph,2,3)
maze_add_edge(graph,3,11)
maze_add_edge(graph,7,6)
maze_add_edge(graph,15,14)
maze_print(graph)
#maze_add_edge(graph,10,18)
#maze_add_edge(graph,30,31)
#maze_add_edge(graph,26,18)
#print graph
#print graph.graph_show_graph()
#for k in range(0,graph.dim):
#    graph.is_wall[k]=False
"""
theWall= maze_find_wall_between_vertices(graph,13,14)
graph.is_wall[theWall]=False
print graph.is_wall
maze_print(graph)
theWall= maze_find_wall_between_vertices(graph,2,3)
graph.is_wall[theWall]=False
print graph.is_wall
maze_print(graph)
theWall= maze_find_wall_between_vertices(graph,0,1)
graph.is_wall[theWall]=False
print graph.is_wall
maze_print(graph)
"""
#print "wall: %d"%theWall 
#print "wallCount:",graph.wallCount 


# kruskals algorithm :

class edge:
    def __init__(self,u,v,wall):
        self.u=u
        self.v=v
        self.wall=wall
        self.cost=999999

    def set_cost(self,cost):
        assert cost>0
        self.cost=cost

        

def get_span_tree(size, dim):
    """get_span_tree:
    using maze functions and graph class create a maze using
    Ideas of kurskals algorithm:
    Only we don't care about a minimum spanning tree
    a maze only has to be a spanning tree 
    from : Algorithmic graph theory : 
    Input A connected weighted graph G = (V, E) with weight function w.
    Output A spanning tree of G.
    Kruskals:
    sort the edges by lowest weight then add the next lowest edge
    until the graph has all vetices connected
    get_span_tree:
    since the edges don't have weight they are sorted from 0-n
    with 0 being the root node of out spanning tree.
    We then add vertices to the spanning tree
    Based on the edge list of each vertex. 
    """
    # size = m
    # T = graph we are building from the connected , weighted graph
    # how to test if acyclic ? need some way to search the graph 
    # 
    print "************kruskal***********"
    logger.warning('size: %d , dim: %d',size,dim , extra={'linenum': lineno(), 'method':"maze_connect_graph"})
    T = maze_init(size,dim)
    G = maze_init(size,dim)
    maze_print(G)
    nodeList=[0 for x in range(size)]
    nodeList[0]=1
    openList=list()
    for elem in range(size):
        openList.append(elem)
    print "openList:",openList
    print "openList length:", len(list(openList))
    edgeList=[]
    print "nodeList:",nodeList, "\nlength:",len(nodeList)
    maze_connect_graph(G)
    maze_add_edge(G,1,2)
    maze_print(G)
    maze_print(T)
    vertex=openList.pop(0)
    #for vertex in range(G.n):
    while len(list(openList)) > 0:
        # get the edge list for the vertex
        choice=None #random.randint(0,len(G.graph_edge_list(vertex))-1)
        edges=G.graph_edge_list(vertex)
        
        sink=find_open_edge(edges,nodeList)
        if nodeList[vertex] and vertex!= 0:
            print "already  have :",vertex
        else:
            print "adding: vertex %d"%vertex
            print edges
            print "sink: ", sink
            nodeList[vertex]=1
            maze_add_edge(T,vertex,sink)
            if (sink in openList):
                vertex=openList.pop(openList.index(sink))
            else :
                
                print "unable to pull vertex from openList"
                return -1
    print nodeList
    maze_print(T)
    print T
    root = 0 # always start root at node 0 for now
    dist=0 # distance from root
    return T

def find_open_edge(edgeList,closedArray):
    print closedArray
    # need to add randomness to the process otherwise is always the same graph
    #random.randint(0,len(G.graph_edge_list(vertex))-1)
    tempList=list(edgeList)
    # copy edgeList, remove closedArray elements, then random shuffle
    # tempList.shuffle()
    for edge in edgeList:
        if (not closedArray[edge]):
            return edge
    return -1
    
def maze_connect_graph(graph):
    """connect all vertices in graph using each edge """
    logger.warning('starting %s ', 'maze_connect_graph', extra={'linenum': lineno(), 'method':"maze_connect_graph"})
    edgeLists=[]
    #print graph
    for vertex in range(graph.n):
        print "vertex:%d"%vertex
        moveList=maze_init_legal_move_list(graph,vertex)
        print "moveList:",moveList
        for move in moveList:
            #print "move:",move
            if move  > 0:
                maze_add_edge(graph,vertex,move)
        edgeLists.append(graph.graph_edge_list(vertex))
    #print "vertex edge lists:",edgeLists
    #maze_print(graph)
    return graph

maze1=get_span_tree(16,4)
print maze1

def write_maze_file(aMaze):
    # add the sha512 hash of the maze_print(graph) to the file name
    # this writes the specs of the graph but doesn't output the
    # maze as seen by the user
    logger.warning('starting %s ', 'write_maze_file', extra={'linenum': lineno(), 'method':""})
    fileName="v"+str(aMaze.n)+"e"+str(aMaze.m)+"d"+str(aMaze.dim)
    fileName+=".mz"
    with open (fileName,'w')as mz:
        mz.write(aMaze.__str__())
        mz.close()

def write_maze_userView(aMaze):
    # add the sha512 hash of the maze_print(graph) to the file name
    # this writes the specs of the graph but doesn't output the
    # maze as seen by the user
    logger.warning('starting %s ', 'write_maze_userView', extra={'linenum': lineno(), 'method':""})
    fileName="v"+str(aMaze.n)+"e"+str(aMaze.m)+"d"+str(aMaze.dim)
    fileName+=".mazeUser"
    with open (fileName,'w')as mz:
        maze_print(aMaze)
        #mz.write(maze_print(aMaze))
        mz.close()

write_maze_file(maze1)
# must refactor the maze_print to output a string buffer !
# either that or use the following redirect of prints
# http://stefaanlippens.net/redirect_python_print
#write_maze_userView(maze1)
logger.warning('Ending File: %s ', 'mazeBuilder.py', extra={'linenum': lineno(), 'method': 'main'})
