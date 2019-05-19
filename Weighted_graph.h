/*****************************************
 * UW User ID:  J4JO
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 *  the provided code.
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "ece250.h"

// include whatever classes you want
#include "Leftist_node.h"
#include "Leftist_heap.h"


class Weighted_graph {
	private:
		// your implementation here
		// you can add both private member variables and private member functions

        int edges;
        int vertices;
		static const double INF;
        
        
        double **adjacency_matrix;      // adjacency matrix that shows weight of nm and mn indices and also shows if there's an edge
        double *distance_array;         // keeps track of the smallest distance of each vertex. 
        int *degree_array;              // keeps track of degree of obj due to O(1)

	public:
		Weighted_graph( int = 50 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		double adjacent( int, int ) const;
		double distance( int, int ) const;

		void insert( int, int, double );

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

// Your implementation here

Weighted_graph::Weighted_graph( int n ){
    int num = 0;
    if (n <= 0) {
        num = 1;
    } else { 
        num = n;
    }
    
    vertices = num;
    edges = 0;
    
    // initialize everything
    distance_array = new double [vertices];
    degree_array = new int[vertices];
    adjacency_matrix = new double*[vertices];
    
    // assign the default states of each array,
    // and also make the matrix into 2D
    for (int i = 0; i < vertices; i++) {
        adjacency_matrix[i] = new double [vertices];
        distance_array[i] = INF;
        degree_array[i] = 0;
    }
    
    // initialize everything to weight of INF
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            adjacency_matrix[i][j] = INF;
        } // except for ii indices which will be 0.0
        adjacency_matrix[i][i] = 0.0;
    }        
}
    
Weighted_graph::~Weighted_graph(){
    // destructor
    for (int i = 0; i < vertices; i++) {
			delete[] adjacency_matrix[i];
    }
    // delete the matrices and indices
    // problem is that memory is not being properly deallocated.
    delete[] degree_array;
    delete[] distance_array;
    delete[] adjacency_matrix;
}


int Weighted_graph::degree(int obj) const {
    if (obj >= vertices || obj < 0) {
        throw illegal_argument();
    }
    return degree_array[obj];
}

int Weighted_graph::edge_count() const {
    return edges;
}


double Weighted_graph::adjacent(int m, int n) const {
    if (m >= vertices || n >= vertices || m < 0 || n < 0) {
        throw illegal_argument();
    }
    else if (m == n) {
        return 0;
    }
    else {
        return adjacency_matrix[m][n];
    }
}

double Weighted_graph::distance(int m, int n) const {    
// a new implementation was added to leftist node and leftist heap
// where it can now take in the weight and the vertex of the node 
// in order to be arranged in priority by weight and also keeping
// reference to what vertex
    
    
    // reset back to default settings
    for (int i = 0; i < vertices; i++) {
        distance_array[i] = INF;
    }
    
    
    Leftist_heap<double>* pq = new Leftist_heap<double>(); // instantiate the leftist heap
    
    // leftist node will now be double weight, int vertex
    // push the starting node into the priority queue
    // where priority is by weight
    pq->push(0.0, m);
    
    // indicate on the distance array that the starting point has distance 0
    distance_array[m] = 0.0;
    
    // throw  illegal argument if out of bounds
    if (m >= vertices || n >= vertices || m < 0 || n < 0) {
        throw illegal_argument();
    } // return 0.0 if same node
    else if (m == n) {
        return 0.0;
    } else {
        while (!pq->empty()) { // priority queue implementation
            int u_vertex = pq->return_vertex();  // give back vertex first
            double u_weight = pq->pop();         // then pop out the weight
            for (int i = 0; i < vertices; i++) {
                if (adjacency_matrix[u_vertex][i] != INF && adjacency_matrix[u_vertex][i] != 0.0) { // check only unvisited edges
                    if (distance_array[i] > distance_array[u_vertex] + adjacency_matrix[u_vertex][i]) { // check if the distance on the distance array is larger than this traversal
                        distance_array[i] = distance_array[u_vertex] + adjacency_matrix[u_vertex][i]; // set to new traversal if so
                        pq->push(distance_array[i], i); // push that vertex into the distance array and mark it visited
                    }
                }
            }
        }
        pq->clear();  // delete the priority queue
        delete pq;
        return distance_array[n]; // return the distance found. 
    }  
}


void Weighted_graph::insert(int m, int n, double w) {
    if (w <= 0) {
		throw illegal_argument();
    }
	if (m == n) {
		throw illegal_argument();
	}
    if (m < 0 || m >= vertices || n < 0 || n >= vertices) {
		throw illegal_argument();
    }
    if (adjacent(m,n) == INF) {
		edges++;
        degree_array[m] = degree_array[m] + 1;
        degree_array[n] = degree_array[n] + 1;
	}
        adjacency_matrix[m][n] = w;
        adjacency_matrix[n][m] = w;  
}


// You can modify this function however you want:  it will not be tested

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
