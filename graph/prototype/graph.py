#!/usr/bin/env python

class Successors:
    def __init__(self):
        self.d=0
        self.length=0
        self.is_sorted=0
        self.sList=[]
    def __str__(self):
        string=""
        for i in range(0,self.d):
            string+=str(self.sList[i])
        return string
        

class Graph:
    def __init__(self,n,dim):
        self.n=n  # number of vertices
        self.m=0  # number of edges
        self.dim=dim # 2nd dimension 
        self.aList=[] # adjacency list  of graph
        for i in range(0,n):
            self.aList.append(Successors())
        assert len(self.aList)==self.n
        # self.aList[1] index is vertex and contents are the list of successors 

    def __str__(self):
        string=""
        for i in range(0,self.n):
            string+=str(i)
            string+=":"
            string+=str(self.aList[i])
            string+="\n"
        return string

    def graph_vertex_count(self):
        return self.n

    def graph_edge_count(self):
        return self.m

    def graph_out_degree(self,source):
        assert source>=0
        assert source < self.n
        return self.aList[source].d

    def graph_has_edge(self,source,sink):
        assert source >= 0
        assert source < self.n
        assert sink >=0
        assert sink < self.n

        self.aList[source].sList.sort()
        if (sink in self.aList[source].sList):
            return True
        else:
            return False
    #def graphCreate(n):

    def graph_add_edge(self,u,v):
        assert u >=0
        assert u < self.n
        assert v >=0
        assert v < self.n
        self.aList[u].sList.append(v)
        self.aList[u].d+=1
        self.m+=1

    def graph_return_stats(self):
        return "vertices: %d,\n edges:%d,\n dimension:%d\n"%(self.n,self.m,self.dim)

    def graph_show_graph(self):
        print "n :",self.n
        print "len(aList) : ",len(self.aList)
        string= ""
        count=1
        string+=( "*"* self.dim)
        string+=( "\n")
        for i in range(0,self.n):
            found=False
            for j in range(1,self.n):
                if (j < self.n ) and (self.graph_has_edge(i,j)):
                    string += "@"
                    found=True
                    print "%d is a connected node"%i
                    break
            if not found:
                string += "-"
            if count %self.dim ==0:
                string +="\n"
            count+=1
        string+=( "\n")
        string+=( "*"* self.dim)
        string+=( "\n")
        return string


