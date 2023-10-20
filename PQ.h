
#ifndef PQ_H
#define PQ_H

#include <iostream>
#include <sstream>
#include <string>
#include "AvlTree.h"
#include "AvlNode.h"
#include "BinaryHeap.h"
#include "dsexceptions.h"
#include <vector>
using namespace std;
// PQ classs
//
// Template parameter: ID
// Constructors:
// PQ --> constructs a new empty queue
// PQ( tasks, priorities ) --> constructs a new queue with a given set of task IDs and priorities
// ******************PUBLIC OPERATIONS*********************
// void insert( x, p )       --> Insert task ID x with priority p
// ID findMin( )  --> Return a task ID with smallest priority, without removing it
// ID deleteMin( )   --> Remove and return a task ID with smallest priority
// void updatePriority( x, p )   --> Changes priority of ID x to p (if x not in PQ, inserts x);
// bool isEmpty( )   --> Return true if empty; else false
// int size() --> return the number of task IDs in the queue
// void makeEmpty( )  --> Remove all task IDs (and their priorities)
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename ID>
// ID is the type of task IDs to be used; the type must be Comparable (i.e., have < defined), so IDs can be AVL Tree keys.
class PQ
{

  public:

    // Constructor
    // Initializes a new empty PQ
    PQ(){

    }
    // Constructor
    // Initializes a new PQ with a given set of tasks IDs and priorities
    //      priority[i] is the priority for ID task[i]
    PQ( const std::vector<ID> & tasks, const std::vector<int> & priorities ) {
    	int nums = tasks.size();
    	//insert the whole priorities to heap to get index
    	for(int i = 0 ; i<nums ; i++){
    		priorityList.insert(priorities[i],nullptr);
    	}
    	//insert avltree with its insert function that takes 2 arguments
    	//get the avlnode pointer then assigned it to heapnode
    	for(int i = 0 ; i< nums ; i++){
    		int array_index = priorityList.get_index(priorities[i]);
    		taskTree.insert( tasks[i], array_index );

    		//match the pointers
    		AvlNode<ID>* nodePtr = taskTree.get_avlNodePtr_from_prj(tasks[i]);
    		priorityList.set_ptr_by_priority(priorities[i],nodePtr);
    		//priorityList.set_ptr_by_priority_by_priority(priority,new_avlnodeptr);
    	}


    }

    // Emptiness check
    bool isEmpty( ) const{

    	return size()==0;

    }

    // Deletes and Returns a task ID with minimum priority
    //    Throws exception if queue is empty
    const ID & deleteMin(){
    	if (size()==0){
    		cout<<"Nothing to be deleted."<<endl;
    		return 0;
    	}
    	ID todo = findMin();
    	taskTree.remove(todo);


    	//rewrite ptr2AVL in hap array
    	//i is the index of heap array
    	//obtain avl ptr using function get_avlNodePtr_from_ind(i)
    	//then set ptr2AVL in the heap
    	for(int i = 2 ; i<=size() ; i++){

    	    		AvlNode<ID>* nodePtr = taskTree.get_avlNodePtr_from_ind(i);
    	    		priorityList.set_ptr_by_ind(i,nodePtr);

    	    	}
    	priorityList.deleteMin( );

    	for(int i = 1 ; i<=size() ; i++){
    	    		priorityList.get_ptr2AVL(i)->heapIndex = i ;
    	    	}


    	return todo;

    }

    // Returns an ID with minimum priority without removing it
    //     Throws exception if queue is empty
    const ID & findMin() const{

    	AvlNode<ID>* min_prio_ptr = priorityList.findMin();
    	return min_prio_ptr->prj;


    }

    // Insert ID x with priority p.
    void insert( const ID & x, int p ){
    	if (priorityList.priorityRepeated(p) && taskTree.contains(x) ){
    		cout<<"priority: "<<x<<" or"<<"project number: "<<p<<" is repeated."<<endl;
    		return;
    	}
    	//cout<<"Inserting prj "<<x<<" priority : "<<p<<endl;
    	taskTree.insert(x,0);//set index=0 first, edit later
    	//cout<<"Inside insert(), irght after insert(x,0)"<<endl;
    	//taskTree.displayLinks();

    	for(int i = 1 ; i<=priorityList.get_currentSize() ; i++){ 		//heap array index 1 to currentSize
    											//after insertion, avl's array index are right
    											//But heap's ptr are not matched
    		AvlNode<ID>* AVLnodePtr = taskTree.get_avlNodePtr_from_ind(i);
    		//cout<<"in for lopp setting "<<AVLnodePtr<<" to index "<<i<<endl;
    		priorityList.set_ptr_by_ind(i,AVLnodePtr);
    	 }

    	priorityList.insert(p,taskTree.get_avlNodePtr_from_prj(x));
    	//cout<<"TESTing: the ptr that was inserted to heap is: "<<taskTree.get_avlNodePtr_from_prj(x)<<" "<<endl;
    	//taskTree.set_index(x,priorityList.get_index(p));
    	for (int i = 1 ; i<=priorityList.get_currentSize() ; i++){
    		taskTree.set_index(priorityList.get_ptr2AVL(i)->prj,i);
    	}

    }

    // Update the priority of ID x to p
    //    Inserts x with p if s not already in the queue
    void updatePriority( const ID & x, int p ) {
    	int old_ind = taskTree.get_heapIndex_from_prj(x);
    	priorityList.update_priority(old_ind, p);
    	//rewrite the array index in AVL tree
    	for(int i = 1 ; i<=size() ; i++){
    		AvlNode<ID>* temp = priorityList.get_ptr2AVL(i);
    		temp->heapIndex = i ;
    	}

    }

    // Return the number of task IDs in the queue
    int size() const {
    	return priorityList.get_currentSize();
    }

    // Delete all IDs from the PQ
    void makeEmpty( ){
    	priorityList.makeEmpty();
    	taskTree.makeEmpty();
    }

    void display(){
    	if (isEmpty()){
    		cout<<"Empty PQ: Nothing to be displayed.\n";
    		return;
    	}
     	cout<<"Displaying priority heap array: \n";
    	priorityList.displayArray();
     	cout<<"Displaying AVL tree (prj/index): \n";
    	taskTree.displayLinks();
    	cout<<endl;
    }

  private:
    AvlTree<ID> taskTree; //project iD of type int
    BinaryHeap<AvlNode<ID>*> priorityList;

};
#endif
