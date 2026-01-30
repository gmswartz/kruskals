/* Author: Grace Swartz (2414391, gswartz@chapman.edu) */
/* PA 6: Kruskal's */
/* Class: CPSC350-02 */
/* Date: 12/6/24 */
/* Summary: provided header file for weighted graph */

#ifndef WGRAPH_H
#define WGRAPH_H

#include <cstdlib>
#include <deque>
#include <set>
#include <stack>
#include <iostream>
#include <limits>
#include <vector>
using namespace std;

//an unweighted, undirected WGraph implemented with adjacency matrix
//fixed size

typedef unsigned int VertexID;

class WGraph{
public:
  WGraph();
  WGraph(unsigned int sz);
  ~WGraph();
  void addEdge(VertexID i, VertexID j, double w);
  void removeEdge(VertexID i, VertexID j);
  bool areAdjacent(VertexID i, VertexID j);
  double cheapestCost(VertexID i, VertexID j);
  void calcFW();
  void computeMST(); // compute the minimum spanning tree from graph

private:
  double** m_adj; // adjacency matrix
  double** m_conn; // connectivity matrix
  unsigned int m_size; //nodes in WGraph (fixed)

  vector<pair<double, pair<VertexID, VertexID> > > getEdges(); // vector to get the edges from graph 

};

#endif
