# Shortest & Longest Path
## Description
This was created to understand big-O as well as graph traversal. It uses a directed weight graph and finds the shortest and longest path. The shortest path uses the standard Djikstra's algorithm to traverse the nodes and find the shortest path. The longest path algorithm uses a recursive depth first search which brute forces the search by calculating every possible path. This was originally a lengthy process however after changing the way some of the data was being accessed it processes within 1-10 seconds depending on your PC.

The program reads in a .txt file where the first line has the <vertices> <edges> then the next 20 lines represents each node <vertexID> <x-coord> <y-coord> and the next 100 lines represents each edge <StartVertex> <EndVertex> <Weight>, the last line then represents the start and goal nodes <Start> <End>. (A sample file has been provided)


### Strategy
To find the shortest path, The program uses the findShortestPath() function which initialises 3 
arrays, dist[], parentNode[], and visited[]. The dist[] array uses the findAdjNodeDistance(a,b) to store 
all the distances of nodes adjacent to the starting node, if a node is not adjacent it will store an 
INFINITE value so the program knows the node is not adjacent to the starting node.
The parentNode[] array elements are all defaulted to 1 and the visited[] array elements are all 
defaulted to false.

The function then uses Dijkstra’s algorithm to run through each of the vertices visiting them one at a 
time. It first starts by running the findMinNode() function that returns the closest node that hasn’t 
been visited. Once it returns the node, we mark that node as visited and we iterate through the 
vertices again now checking the unvisited nodes adjacent to the one we have just visited and 
calculating the distance from the visited node to the adjacent nodes adding the sum to the dist[] 
array which is holding the distances from the start node. In this loop we are also recording the 
parent nodes in the parentNode[] array so we know which nodes we have travelled from to get back 
to the start.

After calculating all the distances from the starting point and recording all the parent nodes, I then 
push the nodes from end to start onto a stack to be popped off and printed later in order from start 
to end.


To find the longest path, I’ve opted to a Brute Force method by getting all possible paths and only 
storing the data for the longest path however, to speed up the process I first create a weight matrix 
which is covered below:
The program first calls the findLongestPath() function which initialises the parentNode[] and visited[] 
arrays to their default values it then creates a weight matrix by using nested for loops and getting 
the individual edges using the findAdjNodeDistance() function, this speeds up the process of getting 
individual edge weights later. The findLongestPath() function then calls the longestPathDFS(). The 
longestPathDFS() function is a recursive function that uses DFS to find all the paths. You first call the 
function with the start and goal nodes, we then mark the starting node as visited and add the node 
to the parentNode[] array to start storing the path. The function then checks if the current node is 
the goal node (checks if we’ve reached our goal i.e. the end of the path): 


- if the current node is the goal node we then check if the currentPathLength is greater than 
the longestPathLength (this is where we decide whether this path is the longest that we’ve 
found so far), if it is the longest path found so far we then store the path nodes to the 
longestPath[] array and store the length to the longestPathLength then continue with the 
process.

- If the current node is not the goal node it will continue with the process.
The function then uses a for loop to find the next unvisited node by first using the weightMatrix 
(weightMatrix[currentNode][nextNode]) to check the node weight, if the node weight is INFINITE 
then we cannot travel to the node, if it is another value then we can travel to the node, we then 
check the visited[] array to see if this node as already been visited. After an unvisited node is found it 
adds the length to the currrentPathLength then calls the longestPathDFS() function with the node 
we found using findAdjNodeDistance().

Once we’ve hit our goal, the recursive functions will start ending/popping off the stack and will go 
back a node and search for the next adjacent node. This will continue to happen until all paths have 
been taken.