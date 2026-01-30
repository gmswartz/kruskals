/* Author: Grace Swartz (2414391, gswartz@chapman.edu) */
/* PA 6: Kruskal's */
/* Class: CPSC350-02 */
/* Date: 12/6/24 */
/* Summary: runs program */

#include "WGraph.h"
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char* argv[]) {
    // error handling
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    
    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    unsigned int size;
    file >> size;

    WGraph graph(size);

    // read adjacency matrix
    for (unsigned int i = 0; i < size; ++i) {
        for (unsigned int j = 0; j < size; ++j) {
            double weight;
            file >> weight;
            if (weight < numeric_limits<double>::max()) {
                graph.addEdge(i, j, weight);
            }
        }
    }

    // close file and compute MST
    string endMarker;
    file >> endMarker;
    // error handling
    if (endMarker != "END") {
        cerr << "Error: Final file line should be 'END'" << std::endl;
        return 1;
    }

    // make the MST
    graph.computeMST();

    return 0;
}

