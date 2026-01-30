/* Author: Grace Swartz (2414391, gswartz@chapman.edu) */
/* PA 6: Kruskal's */
/* Class: CPSC350-02 */
/* Date: 12/6/24 */
/* Summary: provided cpp file for weighted graph
            - includes my implementation of computeMST where a min heap is used
            - creates adjacency matrix of minimum spanning tree and the cost */

#include "WGraph.h"
#include "MinHeap.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

WGraph::WGraph(){
  m_size = 0;
  m_adj = NULL;
}

WGraph::WGraph(unsigned int sz){
  m_size = sz;
  //allocate sz * sz adj matrix
  m_adj = new double*[sz];
  m_conn = new double*[sz];
  for(int i = 0; i < m_size; ++i){
    m_adj[i] = new double[sz];
    m_conn[i] = new double[sz];
  }
  //start with edges
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_adj[i][j] = numeric_limits<double>::max();
      m_conn[i][j] = numeric_limits<double>::max();
    }
  }
}

WGraph::~WGraph(){
  //release memory
  for (size_t i = 0; i < m_size; ++i) {
    delete[] m_adj[i]; // delete each row
  }
  delete[] m_adj; // delete array of pointers
}

void WGraph::addEdge(VertexID i, VertexID j, double w){
  if(i < m_size && j < m_size){
    m_adj[i][j] = w;
    m_adj[j][i] = w;
  }
}

void WGraph::removeEdge(VertexID i, VertexID j){
  if(i < m_size && j < m_size){
    m_adj[i][j] = numeric_limits<double>::max();
    m_adj[j][i] = numeric_limits<double>::max();
  }
}

bool WGraph::areAdjacent(VertexID i, VertexID j){
  return (m_adj[i][j] < numeric_limits<double>::max());
}

void WGraph::calcFW(){
  for(int i = 0; i < m_size; ++i){
    for(int j = 0; j < m_size; ++j){
      m_conn[i][j] = m_adj[i][j]; //start with conn == adj matrix
    }
  }

  for(int im = 0; im < m_size; ++im){ //transitive closure
    for(int source = 0; source < m_size; ++source){
      for(int sink = 0; sink < m_size; ++sink){
        //every possible pair of source,sink and intermediate node
        if(source==sink){
          continue;
        }
        if(m_conn[source][im] != numeric_limits<double>::max() &&
           m_conn[im][sink] != numeric_limits<double>::max() &&
           m_conn[source][sink] > m_conn[source][im] + m_conn[im][sink]){
          m_conn[source][sink] = m_conn[source][im] + m_conn[im][sink];
        }

      }
    }
  }


}

double WGraph::cheapestCost(VertexID i, VertexID j){
  return m_conn[i][j];
}

// vector to get edges into graph
vector<pair<double, pair<VertexID, VertexID> > > WGraph::getEdges() {
    vector<pair<double, pair<VertexID, VertexID> > > edges;

    // iterating through graph
    for (size_t i = 0; i < m_size; ++i) {
        for (size_t j = i + 1; j < m_size; ++j) {
            if (m_adj[i][j] > 0.0) { // ensure each edge is positive
                edges.push_back(make_pair(m_adj[i][j], make_pair(i, j))); // adding the edges into the vector; vertices where the edge connects are a pair
            }
        }
    }

    return edges;
}

// compute the minimum spanning tree from graph
void WGraph::computeMST() {
    // get all the edges of the graph (using getEdges method)
    vector<pair<double, pair<VertexID, VertexID> > > edges = getEdges();

    /// """BEGINNING CODE FROM CHAT GPT, PROMPT ASKED; how can i create a min heap in my computeMST method to store the edges sorted by weight?"""///
    MinHeap<pair<double, pair<VertexID, VertexID> > > minHeap(edges.size()); // create a min heap to store edges ordered by weight (using MinHeap.h)
    /// """END OF CODE FROM CHAT GPT"""///

    // insert all the edges into the heap
    for (unsigned int i = 0; i < edges.size(); ++i) {
        minHeap.insert(edges[i]);
    }

    // keep track of the vertices that are already in the MST
    vector<bool> inMST(m_size, false);
    double mstCost = 0.0; // start cost at 0

    // initialize MST adjacency matrix
    double** adjMatrix = new double*[m_size];
    for (unsigned int i = 0; i < m_size; ++i) {
        adjMatrix[i] = new double[m_size];
        for (unsigned int j = 0; j < m_size; ++j) {
            adjMatrix[i][j] = 0.0; // all edges start at 0.0
        }
    }

    // process edges from the MinHeap and add them to the MST
    while (!minHeap.isEmpty()) {
        // get the minimum edge from the heap
        pair<double, pair<VertexID, VertexID> > edge = minHeap.getMin();
        minHeap.deleteMin();

        double weight = edge.first;
        VertexID u = edge.second.first;
        VertexID v = edge.second.second;

        // checking if both vertices are already in MST
        if (inMST[u] && inMST[v]) {
            continue;
        }

        // add the edge to matrix
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;
        mstCost += weight;

        // keep track of vertices that are part of the MST
        inMST[u] = true;
        inMST[v] = true;
    }

    // print the MST cost and the MST adjacency matrix
    cout << fixed << setprecision(1); // set precision to one decimal place for the MST cost
    cout << "The MST Cost is: " << mstCost << std::endl;

    cout << fixed << setprecision(1); // set precision to one decimal place for each number in MST
    for (unsigned int i = 0; i < m_size; ++i) {
        for (unsigned int j = 0; j < m_size; ++j) {
            cout << adjMatrix[i][j] << " "; 
        }
        cout << endl;
    }
}