/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  j4jo @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef LEFTIST_NODE_H
#define LEFTIST_NODE_H

#include <algorithm>
// You may use std::swap and std::min

#ifndef nullptr
#define nullptr 0
#endif

template <typename Type>
class Leftist_node {
	private:
		Type element;
        Type vertex;
		Leftist_node *left_tree;
		Leftist_node *right_tree;
		int heap_null_path_length;

	public:
		Leftist_node( Type const &obj , int const &vertname ); // takes in two parameters, the weight (obj) and the vertex (vertname)
                                                               

		Type retrieve() const;
        int vert() const;
		bool empty() const;
		Leftist_node *left() const;
		Leftist_node *right() const;
        
        int count_keeper( Type const & , int ) const;
		int count( Type const & ) const;
		int null_path_length() const;

		void push( Leftist_node *, Leftist_node *& );
		void clear();
};

template <typename Type>
Leftist_node<Type>::Leftist_node( Type const &obj , int const &vertname):
element( obj ),
vertex( vertname ),
left_tree( nullptr ),
right_tree( nullptr ),
heap_null_path_length( 0 ) {
	// does nothing
}

// You may need this

template <typename Type>
bool Leftist_node<Type>::empty() const {
	return ( this == nullptr );
}

template <typename Type>
Type Leftist_node<Type>::retrieve() const {
	return element;
}

template <typename Type>
int Leftist_node<Type>::vert() const { 
	return vertex;
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::left() const {
	return left_tree;  
}

template <typename Type>
Leftist_node<Type>* Leftist_node<Type>::right() const {
	return right_tree;
}


template <typename Type>
int Leftist_node<Type>::null_path_length() const {
	if (this->empty()) { return -1; }
    else {
        return heap_null_path_length;
    }
}


template <typename Type>
int Leftist_node<Type>::count( const Type &obj ) const {
	int count = 0;
    count = this->count_keeper(obj, count);
    return count;
}


template <typename Type>
int Leftist_node<Type>::count_keeper( Type const &obj, int count) const {
    if ( empty() ) {
        return count;
    }
    if (element == obj) {
        count = count + 1;
    }
    count = left_tree->count_keeper(obj, count);
    count = right_tree->count_keeper(obj, count);
    return count;
}


template <typename Type>
void Leftist_node<Type>::push( Leftist_node *new_heap, Leftist_node *&ptr_to_this) {
    if (new_heap->empty()) { 
        return;     
    }
    else if (ptr_to_this->empty()) {
        ptr_to_this = new_heap;
        return;
    } else { 
        if ( ptr_to_this->retrieve() <= new_heap->retrieve() ) {
            ptr_to_this->right_tree->push(new_heap, ptr_to_this->right_tree );
            ptr_to_this->heap_null_path_length = ptr_to_this->right()->null_path_length() + 1;
            if ( ptr_to_this->left()->null_path_length() < ptr_to_this->right()->null_path_length() ) {
                    std::swap(  left_tree, right_tree  );
                    ptr_to_this->heap_null_path_length = ptr_to_this->right()->null_path_length() + 1;
            }
        }        
        else {
            Leftist_node<Type>* temp = ptr_to_this;
            ptr_to_this = new_heap;
            new_heap = temp;
            ptr_to_this->push(new_heap, ptr_to_this);
        }
    }
}


template <typename Type>
void Leftist_node<Type>::clear() {
	if ( this == nullptr )
        return;
    else {
        left_tree->clear();
        right_tree->clear();
        delete(this);
    }
}


// You must implement everything

#endif
