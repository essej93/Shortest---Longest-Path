struct Vertex {
    int label;
    double x, y;
    Vertex();
    Vertex(int, double, double);

};

struct Edge {
    int v1, v2;
    double weight;
    Edge();
    Edge(int, int, double);
};

// Declaring main functions
void readFile();
double getMin(double, double);
void pushShortStack(int);
int popShortStack();
void print();


// GRAPH FUNCTIONS:

// shortest path functions
void findShortestPath();
double findAdjNodeDistance(int, int);
int findMinNode();

// euclidean distance functions
void calculateEuclideanDistance(int, int);
Vertex findVertex(int);

// find longest path length
void findLongestPath();
void longestPathDFS(int, int, int&);