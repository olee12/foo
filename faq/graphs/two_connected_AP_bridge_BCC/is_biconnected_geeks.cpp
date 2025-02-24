/* An undirected graph is called "Biconnected" if there are two vertex-disjoint 
 * paths between any two vertices. In a Biconnected Graph, there is a simple 
 * cycle through any two vertices.
 * By convention, two nodes connected by an edge form a biconnected graph, 
 * but this does not verify the above properties. For a graph with more than 
 * two vertices, the above properties must be there for it to be Biconnected.
 * 
 * Given an input graph G, how to tell whether it is biconnected?
 * 
 * dhu: Note that a biconnected graph may not be 2V-connected (graph is still 
 * connected after removing any edge, see description of Problem 16.4). 
 * As a matter of fact, the following graph:
 *
 *                   0---1
 *                    \ /
 *                     2
 *                    / \
 *                   3---4
 *
 * is 2V-connected, but is NOT biconnected, because there is only one 
 * vertex-disjoint path in (0, 3), (0, 4), (1, 3) and (1, 4). Vertex #2 
 * is actually an articulation point.
 * 
 * The following approach is copied from:
 *
 * http://www.geeksforgeeks.org/biconnectivity-in-a-graph/
 * 
 * "How to find if a given graph is Biconnected or not?
 * A connected graph is Biconnected if it is connected and doesn't have any 
 * Articulation Point (AP). We mainly need to check two things in a graph.
 *   1) The graph is connected.
 *   2) There is no articulation point in graph."
 *
 * 
 */

#include<iostream>
#include <list>

#define NIL -1

using namespace std;
 
// A class that represents an undirected graph
class Graph {
  int V;    // No. of vertices
  list<int> *adj;    // A dynamic array of adjacency lists
  bool isBC_util(int v, bool visited[], int disc[], int low[],int parent[]);
public:
  Graph(int V);   // Constructor
  void addEdge(int v, int w);   // function to add an edge to graph
  bool isBC();    // returns true if graph is Biconnected, else returns false
};
 
Graph::Graph(int V) {
  this->V = V;
  adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w) {
  adj[v].push_back(w);
  adj[w].push_back(v);  // Note: the graph is undirected
}
 
// A recursive function that returns true if there is an articulation
// point in given graph, otherwise returns false.
// This function is almost same as isAPUtil() here ( http://goo.gl/Me9Fw )
// u --> The vertex to be visited next
// visited[] --> keeps tract of visited vertices
// disc[] --> Stores discovery times of visited vertices
// parent[] --> Stores parent vertices in DFS tree
bool Graph::isBC_util(int u, bool visited[], int disc[],int low[],int parent[]) {
  // A static variable is used for simplicity, we can avoid use of static
  // variable by passing a pointer.
  static int time = 0;
 
  // Count of children in DFS Tree
  int children = 0;
 
  // Mark the current node as visited
  visited[u] = true;
 
  // Initialize discovery time and low value
  disc[u] = low[u] = ++time;
 
  // Go through all vertices aadjacent to this
  list<int>::iterator i;
  for (i = adj[u].begin(); i != adj[u].end(); ++i) {
    int v = *i;  // v is current adjacent of u
    
    // If v is not visited yet, then make it a child of u
    // in DFS tree and recur for it
    if (!visited[v]) {
      children++;
      parent[v] = u;
      
      // check if subgraph rooted with v has an articulation point
      if (isBC_util(v, visited, disc, low, parent))
	return true;
 
      // Check if the subtree rooted with v has a connection to
      // one of the ancestors of u
      low[u]  = min(low[u], low[v]);
      
      // u is an articulation point in following cases
      // (1) u is root of DFS tree and has two or more chilren.
      if (parent[u] == NIL && children > 1)
	return true;
 
      // (2) If u is not root and low value of one of its child is
      // more than discovery value of u.
      if (parent[u] != NIL && low[v] >= disc[u])
	return true;
    }
 
    // Update low value of u for parent function calls.
    else if (v != parent[u])
      low[u]  = min(low[u], disc[v]);
  }

  return false;
}
 
// The main function that returns true if graph is Biconnected, otherwise false.
// It uses recursive function isBCUtil()
bool Graph::isBC() {
  // Mark all the vertices as not visited
  bool *visited = new bool[V];
  int *disc = new int[V];
  int *low = new int[V];
  int *parent = new int[V];
 
  // Initialize parent and visited, and ap(articulation point) arrays
  for (int i = 0; i < V; i++) {
    parent[i] = NIL;
    visited[i] = false;
  }
 
  // Call the recursive helper function to find if there is an articulation 
  // point in given graph. We do DFS traversal starring from vertex 0
  if (isBC_util(0, visited, disc, low, parent) == true)
    return false;
 
  // Now check whether the given graph is connected or not. An undirected
  // graph is connected if all vertices are reachable from any starting 
  // point (we have taken 0 as starting point)
  for (int i = 0; i < V; i++) {
    if (visited[i] == false)
      return false;
  }

  return true;
}
 
// Driver program to test above function
int main() {
  // Create graphs given in above diagrams
  /*
  Graph g1(2);
  g1.addEdge(0, 1);
  g1.isBC()? cout << "Yes\n" : cout << "No\n";
 
  Graph g2(5);
  g2.addEdge(1, 0);
  g2.addEdge(0, 2);
  g2.addEdge(2, 1);
  g2.addEdge(0, 3);
  g2.addEdge(3, 4);
  g2.addEdge(2, 4);
  g2.isBC()? cout << "Yes\n" : cout << "No\n";
 
  Graph g3(3);
  g3.addEdge(0, 1);
  g3.addEdge(1, 2);
  g3.isBC()? cout << "Yes\n" : cout << "No\n";
 
  Graph g4(5);
  g4.addEdge(1, 0);
  g4.addEdge(0, 2);
  g4.addEdge(2, 1);
  g4.addEdge(0, 3);
  g4.addEdge(3, 4);
  g4.isBC()? cout << "Yes\n" : cout << "No\n";
 
  Graph g5(3);
  g5.addEdge(0, 1);
  g5.addEdge(1, 2);
  g5.addEdge(2, 0);
  g5.isBC()? cout << "Yes\n" : cout << "No\n";
  */
 
  // dhu test case:
  //                 0---1
  //                  \ /
  //                   2
  //                  /	\
  //                 3---4
  // which is NOT biconnected, but is 2V-connected.
  Graph g_dhu(5);
  g_dhu.addEdge(0, 1);
  g_dhu.addEdge(0, 2);
  g_dhu.addEdge(1, 2);
  g_dhu.addEdge(2, 3);
  g_dhu.addEdge(2, 4);
  g_dhu.addEdge(3, 4);

  g_dhu.isBC()? cout << "Yes\n" : cout << "No\n";

  return 0;
}
