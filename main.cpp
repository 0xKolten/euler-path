#include <iostream> 
#include <fstream> 
using namespace std; 
#include "matrix.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Needs to arguments..." << endl; 
    }

    int vertices, max_edges;
    ifstream inFile;
    string filename(argv[1]); 

    // cout << "Enter filename: ";
    // cin >> filename;
    inFile.open(filename);
    if (!inFile.is_open()) {
        cout << "File failed to open..." << endl; 
    }
    inFile >> vertices; 
    inFile >> max_edges; 
    matrix m(vertices);

    int v1, v2; 
    while (inFile >> v1 >> v2) {
        m.add_edge(v1, v2); 
    }
    
    cout << "Adjacency list for " << filename << ": " << endl; 
    m.print_adj(); 
    //cout << endl; 

    if(m.one_stroke()) {
        cout << "Can be drawn in one stroke." << endl; 
    } 
    else {
        cout << "Can not be drawn in one stroke." << endl;
        return 0; 
    }

    cout << endl; 
    
    cout << "Path to draw graph in one stroke: " << endl; 
    int b = m.get_start(); 
    m.find_path(b); 
    m.print_path(); 

    cout << endl; 

    return 0;
}