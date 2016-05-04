#! /usr/bin/env python

class Vertex:
    def __init__(self,row,col):
        self.y=row
        self.x=col
        self.tup=(row,col)
        self.color=None
        self.successors=[] # integer list of successors
        self.neighbors=[]
        self.connections=[]
    def __str__(self):
        return "(%d,%d)-color=%s" % (self.y,self.x,self.color)

    def getNeighbors(self):
        return self.neighbors

    def getConnections(self):
        return self.connections

    def printNeighbors(self):
        for n in self.neighbors:
            print "neighbors: ", n.tup
# maze is a 2d array
# adj matrix for maze = (h x w)^2 boolean matrix
# or (h x w)^2 vertex lists for the adjList

# build the maze one cell at a time
# start at random position
# red chooses a cell for a path
# black chooses a cell for a wall
# if start = (0,0) frontier = [(0,1),(1,0)]
# each vertex gets a color (red or black)
# frontier =includes all immediately avaialble vertices
# openList = all uncolored vertices
def createOpenList(  rows, cols,oList=[]):
    for i in range(0,rows):
        for j in range(0,cols):
            oList.append( Vertex(i,j))
    return oList

# all vertices in maze (x,y) become vertices with a color
# and lists of neighbors and connections
openList=createOpenList(width,height)
#print openList
print len(openList)
# graph = V(verticies) & E(edges)
# graph = { (0,0):[(0,1),(1,0)]
def getVertexByTuple(vList,tup):
    for v in vList:
        if v.tup == tup:
            return v
    return None
def mazeInit(vList):
    neighborDict = {}

    for e in openList:
        #  row wise extremes
        upper = e.tup[0] -1
        lower = e.tup[0] +1
        left  = e.tup[1] -1
        right = e.tup[1] +1
        # this has to be changed to append only references to the Vertex already in the list
        if (upper >= 0 ):
            e.neighbors.append(getVertexByTuple(vList,(upper,e.tup[1])))
        if (lower < height):
            e.neighbors.append(getVertexByTuple(vList,(lower,e.tup[1])))
        if (left >= 0):
            e.neighbors.append(getVertexByTuple(vList,(e.tup[0],left)))
        if (right < width):
            e.neighbors.append(getVertexByTuple(vList,(e.tup[0],right)))
        neighborDict[e.tup]=e.neighbors
        #print e, e.neighbors
    #print e,":", neighbors
    return neighborDict

def printMaze(vList):
    for v in vList:
        print v, v.connections #,v.neighbors

def addRedVertex(vertex):
    vertex.color="red"

def addBlackVertex(vertex):
    vertex.color="black"

# functions for maze builder
# getNextFrontierVertex(frontierList)
# addVertexToFrontier
# addListToFrontier
# connectVertices(v1,v2)
# 

def addVertexToFrontier(frontierList,vertex):
    print "stop"
    

def buildMaze(openVertexList,mazeBuildDict):
    counter=1
    start = openVertexList[0]
    start.color="red"
    current=start
    # the final vertex list with connections and neighbors
    mazeList=[]
    blackList=[]
    # frontier of available vertices to be chosen from
    # initially will be neighbors of starting vertex
    # frontier=[]
    current.printNeighbors()
    frontier = start.neighbors
    # as the frontier changes the list of openVertices should also change
    pick=-1
    counter = len(openVertexList)
    while (len(frontier) > 0):
        print "Length of frontier: ",len(frontier)
        print "frontier: ",frontier
        pick=random.randrange(0,len(frontier))
        print "pick: ", pick
        v = frontier[pick]
        print "v: ", v
        #mazeList.append(openVertexList.remove(v))
        # black case
        if counter %2 == 0:
            v.color="black"
            blackList.append(openVertexList.remove(v))
        else:
            current.connections.append(v)
            v.color="red"
            for neighbor in v.neighbors:
                if v not in frontier:
                    frontier.append(neighbor)
            v.connections.append(current)
            if v in openVertexList:
                print "index of v in openVertexList: ",openVertexList.index(v)
                mazeList.append(openVertexList.remove(v))
            else:
                raise Exception 
            #v.connections.append(v.neighbors.pop())
        counter-=1
        print "counter: ",counter
        frontier.remove(v)
        print "vertex:",v
        
        #
    return mazeList


#mazeDict = mazeInit(openList)
pp = pprint.PrettyPrinter(indent=4)
#pp.pprint(mazeDict)
#printMaze(openList)

#builtMaze=buildMaze(openList,mazeDict)
#printMaze(builtMaze)
