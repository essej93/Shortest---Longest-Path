#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "library.h"

using namespace std;

// variables to hold start/goal vertices
int start, goal;

// stores number of edges and vertices
int nEdges, nVertices;

// arrays to hold edges and vertices
Vertex vertices[100];
Edge edges[100];

const int INFINITE = 99999;

// for shortest path
double shortestPathLength = 0;
int shortestPathStackCount = 0;
int shortestPathStack[20];

//variables to store info for longest path
int longestPath[20];
double longestPathLength = 0;
double currentPathLength = 0;
double weightMatrix[20][20];

// variables re-used for both shortest/longest path algorithms
double dist[20];
bool visited[20];
int parentNode[20];
double euclideanDistance;


// main function
int main() {

    readFile();
    calculateEuclideanDistance(start, goal);
    findShortestPath();
    findLongestPath();
    print();

}

// findLongestPath function initialises arrays then runs the longestPathDFS function
void findLongestPath(){

    cout<<"Brute forcing longest path. Please wait... as it might take a minute"<<endl;

    // initialises dist, parentnode and visited arrays
    for(int i = 0; i < nVertices; i++){
        parentNode[i] = 0;
        visited[i] = false;
    }

    for(int i = 0; i < nVertices; i++){
        for(int j = 0; j < nVertices; j++){
            weightMatrix[i][j] = findAdjNodeDistance(i,j);
        }
    }

    int index = 0;

    // runs longestPathDFS
    longestPathDFS(start-1, goal-1, index);


    cout<<"Brute force completed!"<<endl;


}

// longestPathDFS uses brute force DFS recursion method to find every path from the start to the goal vertex
void longestPathDFS(int s, int g, int& index){

    // when visiting a node we set it as visited so we don't visit it again
    visited[s] = true;
    parentNode[index] = s; // array keeps track of the current path from start to finish
    index++; // due to using recursion we increment the index each time we run the function

    // checks if the current visiting node is the goal node
    if(s == g){
        // if the current node = goal node then we check if
        // the current longest path is greater than the longest path length
        // if so we then store the path into the longest path array
        // then we have the longest path equal the current longest path
        if(currentPathLength > longestPathLength){
            // for loop to store the current longest path nodes from start to finish
            for(int i = 0; i < index; i++){
                longestPath[i] = parentNode[i];
            }
            longestPathLength = currentPathLength; // stores longest path length
            
        }
    }

    // for loop to find the next node to visit from the current node
    for(int i = 0; i < nVertices; i++){
        //int check = findAdjNodeDistance(s, i); // gets the distance between current node and adj node
        int check = weightMatrix[s][i];
        // checks if the adj node can be visited
        if(check!=INFINITE){
            if(!visited[i]){
                // we add the checklength to the current longest path length when we visit
                currentPathLength += check; 

                // recursion step to then find the next node to visit
                longestPathDFS(i, g, index); 

                // we then remove the checklength when we move back a node
                currentPathLength -= check;
            }
            
        }
    }

    // reduces index and sets visited to false for when
    // recursive functions start popping off the stack
    index--;
    visited[s] = false;

}


// function to push node onto stack
void pushShortStack(int node){
    shortestPathStack[shortestPathStackCount++] = node;
}

//function to pop node from stack
int popShortStack(){
    return shortestPathStack[--shortestPathStackCount];
}


// function to find shortest path in the graph
void findShortestPath(){

    cout<<"Finding shortest path..."<<endl;

    // initialises dist, parentnode and visited arrays
    for(int i = 0; i < nVertices; i++){
        dist[i] = findAdjNodeDistance((start-1), i);
        parentNode[i] = 1;
        visited[i] = false;
    }

    // sets distance from start node to 0
    dist[start-1] = 0;

    // for loop iterates through n amount of times (the amount of vertices)
    // uses findMinNode to find the closest node that hasn't been visited
    // markes that node to visited
    for(int i = 0; i < nVertices; i++){
        int v = findMinNode();
        visited[v] = true;

        // inner for loop finds the closest node to the one we've just visited 
        // by finding a node that hasn't been visited, it then checks the shorter distance between
        // the v node and node j which we are checking
        // if the distance is larger (even if infinite) it will get the minimum distance of
        // the node we are checking (j) and the sum of the current distance of node v and
        // the distance between node v and j. If any of the sums is infinite then it means the node's are not connected
        for(int j = 0; j < nVertices; j++){
            if(!visited[j]){
                if(dist[j] > (findAdjNodeDistance(v, j) + dist[v])){
                    dist[j] = getMin(dist[j], dist[v] + findAdjNodeDistance(v, j));
                    parentNode[j] = v;
                }
            }
        }
    }

    // the following pushes the path nodes to stack from end to start
    // so we can pop them off the stack and print them from start to end
    // we first push the goal node onto the stack, the while loop will then add
    // the nodes between the goal and start onto the stack
    // we then add the start node to the top of the stack
    int pNode = parentNode[goal-1];
    pushShortStack(goal-1);
    while(pNode != (start-1)){
        pushShortStack(pNode);
        pNode = parentNode[pNode];
    }
    pushShortStack(start-1);

    // assigns the distance from start to goal node to print later
    shortestPathLength = dist[goal-1];


    cout<<"Shortest path found!"<<endl;

}

// function to return smaller/min value out of 2 values
double getMin(double n1, double n2){
    if(n1 < n2) return n1;
    else return n2;
}


// function to find the closest node to the start node that hasn't been visited
int findMinNode(){
    
    double min = INFINITE;
    int minNode = 0;

    for(int i = 0; i < nVertices; i++){

        if(!visited[i] && dist[i] < min){
            min = dist[i];
            minNode = i;
        }

    } 

    return minNode;
}

// function used to find the distance of an edge between 2 nodes
double findAdjNodeDistance(int src, int adjNode){

    if(src == adjNode) return 0;

    double distance = INFINITE;

    for(Edge edge : edges){
        if(edge.v1 == src && edge.v2 == adjNode) return edge.weight;
    }

    return distance;
}

// function which takes the start and goal node id's to then calculate
// the euclidean distance between both vertices.
void calculateEuclideanDistance(int s, int g){

    Vertex v1 = findVertex(s);
    Vertex v2 = findVertex(g);

    double xpower = pow((v1.x - v2.x), 2);
    double ypower = pow((v1.y - v2.y), 2);

    double sqrtResult = sqrt((xpower + ypower));

    euclideanDistance = sqrtResult;
}

// function to find a vertex from the vertices array using a node id/label
Vertex findVertex(int nodeId){

    for(int i = 0; i < nVertices; i++){
        if(vertices[i].label == nodeId) return vertices[i];
    }

    return Vertex();
}


// PRINT function to print out all the collected information
void print() {

    cout<<"----------------=============== Graph Statistics ===============----------------"<<endl;
    // prints out graph statistics
    cout<<"Number of Vertices in the Graph: "<<nVertices<<endl;
    cout<<"Number of Edges in the Graph: "<<nEdges<<endl;
    cout<<"The start vertex: "<<start<<endl;
    cout<<"The goal vertex: "<<goal<<endl;
    cout<<"Euclidean distance between Start and Goal: "<<euclideanDistance<<endl;
    cout<<endl;

    // prints out stored shortest path
    cout<<"Shortest path from start to finish: ";
    int pathLength = shortestPathStackCount;
    for(int i = 0; i < pathLength; i++){
        int node = popShortStack();

        cout<<node+1<<" ";
    } 
    cout<<endl;

    // prints out shortest path length
    cout<<"The length of the shortest path: "<<shortestPathLength<<endl;
    cout<<endl;

    // prints out stored longest path
    cout<<"The longest path from start to finish: ";
    for(int i = 0; i < nVertices; i++){
        cout<<longestPath[i]+1<<" ";
    }
    cout<<endl;

    // prints out longest path length
    cout<<"The length of the longest path: "<<longestPathLength<<endl;
}

// Vertex constructor
Vertex::Vertex(int id, double xpos, double ypos) {
    label = id;
    x = xpos;
    y = ypos;
}

// Vertex default constructor
// I remove 1 off the labels to make them easier to store and reference, i then re-add the 1 when printing out the data
Vertex::Vertex() {
    label = -1;
    x = 0;
    y = 0;
}

// Edge constructor
// I remove 1 off the labels to make them easier to store and reference, i then re-add the 1 when printing out the data
Edge::Edge(int vertex1, int vertex2, double w) {
    v1 = vertex1 - 1;
    v2 = vertex2 - 1;
    weight = w;
}

// Edge default constructor
Edge::Edge() {
    v1 = -1;
    v2 = -1;
    weight = 0;
}

// function to read data in from the file
void readFile() {


    char filename[20];
    ifstream filein;

    cout << "Please input the file name: ";
    cin >> filename;

    filein.open(filename);

    // if statement checks if file opened
    if (!filein) {
        cerr << "Error opening file: " << filename << endl;
        exit(1);
    }


    // gets the number of vertices and edges from file
    filein >> nVertices >> nEdges;

    // variables to hold vertex info from file before loading
    // into vertices array
    int id;
    double xpos, ypos;


    // for loop to load in the vertices to the vertices array
    for (int i = 0; i < nVertices; i++) {
        filein >> id >> xpos >> ypos;
        Vertex newVertex(id, xpos, ypos);
        vertices[i] = newVertex;
    }

    // variables to hold edge info from file before loading
    // into edges array
    int v1, v2;
    double weight;

    // for loop to load in the edges to the edges array
    for (int i = 0; i < nEdges; i++) {
        filein >> v1 >> v2 >> weight;
        Edge newEdge(v1, v2, weight);
        edges[i] = newEdge;

    }

    filein >> start >> goal;


    filein.close();


}
