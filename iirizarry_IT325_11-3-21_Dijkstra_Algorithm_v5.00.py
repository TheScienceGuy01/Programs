"""
    Program: iirizarry_IT325_10-23-21_Dijkstra_Algorithm_v5.00.py
    Author(s): Israel Irizarry
    Email: iirizarry33 at students.cumberland.edu
    Date: October 23, 2021
    Class - Computer Networking
    Professor - Dr. Nichols
    ***Honor Code***
    
    Objective: Display the steps to complete Dijkstra's algorithm in a table and in a forwarding table.
    
    Version 1.00 - Created graph and found the shortest weight for the current node.
    Version 2.00 - Created loop that finds the next node to check.
    Version 3.00 - Formatted the output and added comments.
    Version 4.00 - Formatted the forwarding table ***May not be working properly***
    Version 5.00 - Formatted the forwarding table correctly and organized comments and algorithm (Works as intended).
    
    Algorithm:
        1. From start node check all nodes that have the path to it.
        
        2. Update table so that they have the correct D() and P().
            2.1 - Update with the lowest value if a path of less weight if found.
            2.2 - Update the last node it was connected to as the P() if needed
            
        3. Make the next node the node that has the least total weight.
        
        4. Add last node and new node to list to not check.
        
        5. Repeat until all the nodes have been checked.
        
        6. Calculate the forwarding table.
            6.1 - Check if any nodes that are linked to the start node are in the shortest path to the current node.
            6.2 - If so, repeat 6.1 for the node linked to the start node. This is to find out if the linked node is the shortest
                  path or if the node's shortest path is from another node.
            6.3 - Format into a table and print for every node that is not the starting node.
            
        7. Print the final path to each node.

        
    ***Credits***
        None other than some python syntax error help.
        

    System Information:
        OS: Windows 10 Home X64
        Version: 10,0,19041 Build 19041
        CPU: Intel Celeron 1.10GHz
        RAM: 4GB
        
    Run via command line:

        python C:Users/israe/Desktop/Programming/iirizarry_IT325_10-23-21_Dijkstra_Algorithm_v4.00.py

    Output:
    
    **********************************************************************************************************************************
    *   This program calulates the shortest path from any node on the graph (given in the book p. 381)
    *   to all other nodes using Dijkstra's algorithm. It then sets the algorithm step table and the forwarding table.
    Enter a node (u, v, w, x, y, or z):u
    **********************************************************************************************************************************
    Step | Path   | D(u),P(u) | D(v),P(v) | D(x),P(x) | D(w),P(w) | D(z),P(z) | D(y),P(y) |
    0    |u       |     0 ,  *|     2 ,  u|     1 ,  u|     5 ,  u|     0 ,  *|     0 ,  *
    1    |ux      |     0 ,  *|     2 ,  u|     0 ,  *|     4 ,  x|     0 ,  *|     2 ,  x
    2    |uxy     |     0 ,  *|     2 ,  u|     0 ,  *|     3 ,  y|     4 ,  y|     0 ,  *
    3    |uxyv    |     0 ,  *|     0 ,  *|     0 ,  *|     3 ,  y|     4 ,  y|     0 ,  *
    4    |uxyvw   |     0 ,  *|     0 ,  *|     0 ,  *|     0 ,  *|     4 ,  y|     0 ,  *
    5    |uxyvwz  |     0 ,  *|     0 ,  *|     0 ,  *|     0 ,  *|     0 ,  *|     0 ,  *

    Destination |    Link
         v      | ( u ,  v )
         x      | ( u ,  x )
         w      | ( u ,  x )
         z      | ( u ,  x )
         y      | ( u ,  x )

    Final List of shortest paths from  u  to all other nodes: 
         {'u': [0, '*'], 'v': [2, 'u'], 'w': [3, 'y'], 'y': [2, 'x'], 'z': [4, 'y'], 'x': [1, 'u']}
    **********************************************************************************************************************************
"""
global forwardingTable
forwardingTable = {'u':[],'v':[],'x':[],'w':[],'z':[],'y':[]}

def main():
    #Global variables declared.
    global nodes
    global shortestPath
    global searchedNodes

    #Global Variabels initialized.
    searchedNodes = []
    nodes = ['u', 'v', 'x', 'w', 'z', 'y']
    shortestPath = {'u':[0, '*'], 'v':[0, '*'],'w':[0, '*'], 'y':[0, '*'],'z':[0, '*'], 'x':[0, '*']}
    savedShortPath = {'u':[0, '*'], 'v':[0, '*'],'w':[0, '*'], 'y':[0, '*'],'z':[0, '*'], 'x':[0, '*']}

    #Gragh represented in problem.
    graphNodes = {'u':[['v', 'x', 'w'], [2, 1, 5]], 'v':[['u', 'x', 'w'], [2, 2, 3]], 'w':[['v', 'x', 'y', 'z', 'u'], [3, 3, 1, 5, 5]],
             'x':[['u', 'v', 'w', 'y'],[1, 2, 3, 1]], 'y':[['x', 'z', 'w'],[1, 2, 1]], 'z':[['y', 'w'],[2, 5]]}

    #Declared and initialized variables.
    spaces = 9
    currentSmallest = 1000
    isSearched = 0

    #User Input and starting setup for table.
    print("**********************************************************************************************************************************")
    print("*   This program calulates the shortest path from any node on the graph (given in the book p. 381)")
    print("*   to all other nodes using Dijkstra's algorithm. It then sets the algorithm step table and the forwarding table.")
    currentNode = input("Enter a node (u, v, w, x, y, or z):")
    startNode = currentNode
    currentNodeTemp = currentNode
    print("**********************************************************************************************************************************")
    print("Step |",'{:>3}'.format('Path   |'),'{:>5}'.format("D(u),P(u) |"),'{:>5}'.format("D(v),P(v) |"),'{:>5}'.format("D(x),P(x) |"),'{:>5}'.format("D(w),P(w) |"),'{:>5}'.format("D(z),P(z) |"),'{:>5}'.format("D(y),P(y) |"))

    '''
        This covers steps 1-5 in the algorithm.
    '''
    for i in nodes:
        #Finds the lowest weights connected to the current node and assigns them to the shortest path array is they are lower than the ones before.
        searchedNodes.append(currentNode)
        
        for j in range(0, len(graphNodes[currentNode][0])):
            
            #Checks if the node connected has been searched or not.
            for q in searchedNodes:
                if q == graphNodes[currentNode][0][j]:
                    isSearched = 1

            #Changes the shortest weight if the weight is lower than the previous weight.
            if isSearched == 0 and((graphNodes[currentNode][1][j]+shortestPath[currentNode][0] < shortestPath[graphNodes[currentNode][0][j]][0]) or shortestPath[graphNodes[currentNode][0][j]][0] ==0):
                shortestPath[graphNodes[currentNode][0][j]][0] = graphNodes[currentNode][1][j]+shortestPath[currentNode][0]
                shortestPath[graphNodes[currentNode][0][j]][1] = currentNode
                savedShortPath[graphNodes[currentNode][0][j]][0] = graphNodes[currentNode][1][j]+shortestPath[currentNode][0]
                savedShortPath[graphNodes[currentNode][0][j]][1] = currentNode

            #Resets the variable that checks if the node is already searched.
            isSearched = 0
        
        #Finding next node
        for q in shortestPath:
            
            #Checks to see if the current node has not been searched.
            for w in searchedNodes:
                
                if w == q:
                    isSearched = 1

                    #Gets rid of multiples
                    shortestPath[q] = [0,'*']

            #Changes the current node to the node with the lowest total weight so far.
            if (shortestPath[q][0] != 0 and shortestPath[q][0] <= currentSmallest) and isSearched == 0:
                currentSmallest = shortestPath[q][0]
                currentNodeTemp = q

            #Resers the variable that checks if the node is already searched.
            isSearched = 0

        #Resets some variables and prints the next line of the table to the screen.
        spaces -= 1
        _TableFormation_(spaces)
        currentNode = currentNodeTemp
        currentSmallest = 100

    smallestStartEdge = 100

    '''
        Covers step 6 and its substeps in the algorithm.
    '''
    
    #Formats forwarding table.
    print("\nDestination |    Link")

    #Finds the values for the forwarding table.
    for i in forwardingTable:

        #Checks that the node is not the starting node.
        if (i != startNode):
            
            for j in forwardingTable[i]:

                #Checks if the node is connected to a node connected to the start node and adds it to table.
                for w in graphNodes[startNode][0]:
                    
                    if (j == w):
                        forwardingTable[i][0] = w
                        
                    if (j == startNode):
                        forwardingTable[i][0] = i

    #Checks that each node next to the start node is the node where the lowest path is from.
    for i in forwardingTable:

        #Changes the link if the current link is not attached to the lowest cost route.
        if forwardingTable[i] != startNode:
            
            for k in forwardingTable[i]:
                
                if (k != '*'):
                    forwardingTable[i][0] = forwardingTable[k][0]

        #Formats and prints the forwarding table.
        if (forwardingTable[i][0] == '*' and i != startNode):
            forwardingTable[i][0] = i
            
        if (i != startNode):
            print("    ",i, "     | (", startNode, ", ", forwardingTable[i][0], ")")

    '''
        This covers step 7 in the algotithm.
    '''

    #Prints the final paths.
    print("\nFinal List of shortest paths from ", startNode, " to all other nodes: ")
    print("    ", savedShortPath)
    print("**********************************************************************************************************************************")
   
        
def _TableFormation_(x):
    '''
        This function formats the output of the table so it can be read easily.
        It also covers step 2 in the algorithm.
    '''

    #Helps format some of the spacing.
    x = x-1

    #Formats each line of the table.
    print(len(searchedNodes)-1,"   |", end="")
    
    for i in searchedNodes:
        print(i,end="")
        
    for i in range(0, x):
        print(" ", end="")
        
    for i in nodes:
        print("|    ", shortestPath[i][0],", ",shortestPath[i][1],end="")
        forwardingTable[i].append(shortestPath[i][1])
        
    print("")
    

#Calls main
main()
