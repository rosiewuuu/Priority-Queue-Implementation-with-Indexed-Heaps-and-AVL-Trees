/*
 * BinaryHeap_twoArg_2.h
 *
 *  Created on: Nov 11, 2022
 *      Author: rosem
 */

#ifndef BINARYHEAP_H_
#define BINARYHEAP_H_

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "dsexceptions.h"
#include "AvlTree.h"
#include <vector>
using namespace std;

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x ,y )       --> Insert priority x and ptr2AVL y
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest the smallest priority's AVL pointer
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void update_priority(const int & old_prioirity, int new_priority)
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinaryHeap
{
  public:
    struct HeapNode{
        	int priority;
        	Comparable ptr2AVL; //pointer to AVL tree
        };
    explicit BinaryHeap( int capacity = 100 )
      : array( capacity + 1 ), currentSize{ 0 }
    {
    }

    explicit BinaryHeap( const vector<HeapNode> & items )
      : array( items.size( ) + 10 ), currentSize{ items.size( ) }
    {
        for( int i = 0; i < items.size( ); ++i ){
        	array[ i + 1 ] = items[ i ];

        }
        buildHeap( );
    }

    int get_currentSize() const {
    	return currentSize;
    }

    int get_index(int x) const{
    	//assuming priority exisit.
    	// x is priority
    	if (!isEmpty()){
    		for (int i = 1 ; i<=currentSize ; i++){
    			if (array[i].priority == x){
    				return i;
    			}
    		}
    	}
    	return 0;
    }

    Comparable get_ptr2AVL(int ind) const{
    	//assuming priority exisit.
    	// x is priority
    	if (ind<0 && ind > currentSize){
    		cout<<"array index out of bound."<<endl;
    	}
    	return array[ind].ptr2AVL;
    }

    void  set_ptr_by_priority(const int prio, const Comparable new_ptr )
        {
            if( isEmpty( ) ){
            	cout<<"From set_ptr_by_priority( )"<<endl;
                throw UnderflowException{ };
            }
            for(int i = 1 ; i <= currentSize ; i++){
            	if (array[i].priority == prio){
            		array[i].ptr2AVL = new_ptr;

            	}
            }
        }

    void  set_ptr_by_ind(const int ind, const Comparable new_ptr )
        {
            if( isEmpty( ) ){
            	cout<<"From set_ptr_by_ind( )"<<endl;
                throw UnderflowException{ };
            }
            if ( ind <= currentSize)
            array[ind].ptr2AVL = new_ptr;


        }
//     const int get_currentSize() const {
//    	return currentSize;
//    }


    bool isEmpty( ) const
      { return currentSize == 0; }

    bool priorityRepeated(int p){
    	for (int j=1 ; j<= currentSize; j++){
    		if ( p == array[j].priority ){
    			return true;
    		}
    	}
    	return false;
    }
    /**
     * Find the smallest item in the priority queue.
     * Return the smallest item, or throw Underflow if empty.
     */

//    const Comparable & findMin( ) const
//    {
//        if( isEmpty( ) )
//            throw UnderflowException{ };
//        return array[ 1 ];
//    }

    void update_priority(const int & arr_index, int new_prio){
    	if (priorityRepeated(new_prio)){
    		cout<<"New priority number is not unique.\n";
    		return;
    	}

    	array[arr_index].priority = new_prio;
    	buildHeap();
    }

    //return pointer to AVL node
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) ){
        	cout<<"From findMin"<<endl;
            throw UnderflowException{ };
        }
        return array[ 1 ].ptr2AVL;


    }


    /**
     * Insert item x, allowing duplicates.
     */
//    void insert( const int & x,const Comparable & y )
//    {
//        if( currentSize == array.size( ) - 1 )
//            array.resize( array.size( ) * 2 );
//
//            // Percolate up
//        int hole = ++currentSize;
//        HeapNode copy;
//        copy.priority = x;
//        copy.ptr2AVL = y;
//
//        array[ 0 ]= std::move( copy );
//        for( ; x < array[ hole / 2 ].priority; hole /= 2 )
//            array[ hole ] = std::move( array[ hole / 2 ]);
//        array[ hole ] = std::move( array[ 0 ]);
//
//
//    }

//this one
//    void insert(  const int & x,const Comparable & y  )
//    {
//        if( currentSize == array.size( ) - 1 )
//            array.resize( array.size( ) * 2 );
//        HeapNode copy;
//        copy.priority = x;
//        copy.ptr2AVL = y;
//            // Percolate up
//        int hole = ++currentSize;
//        for( ; hole > 1 && x < array[ hole / 2 ].priority; hole /= 2 ){
//        	 array[ hole ] = std::move( array[ hole / 2 ] );
//        }
//        array[ hole ] = std::move( copy );
//
//
//
//
//    }

    void insert( const int & x,const Comparable &y )
    {
        if( currentSize == array.size( ) - 1 )
            array.resize( array.size( ) * 2 );

            // Percolate up
        int hole = ++currentSize;
        //Comparable copy = x;

	HeapNode copy;
        copy.priority = x;
        copy.ptr2AVL = y;

        array[ 0 ] = std::move( copy );
        for( ; x < array[ hole / 2 ].priority; hole /= 2 )
            array[ hole ] = std::move( array[ hole / 2 ] );
        array[ hole ] = std::move( array[ 0 ] );
    }




    void insert( int && x, const Comparable && y )
       {
           if( currentSize == array.size( ) - 1 )
               array.resize( array.size( ) * 2 );
   	HeapNode copy;
           copy.priority = x;
           copy.ptr2AVL = y;
               // Percolate up
           int hole = ++currentSize;
           for( ; hole > 1 && x < array[ hole / 2 ].priority; hole /= 2 )
               array[ hole ] = std::move( array[ hole / 2 ] );
           array[ hole ] = std::move( copy );
       }
    /**
     * Remove the minimum item.
     * Throws UnderflowException if empty.
     */
    void deleteMin( )
    {


        if( isEmpty( ) ){
        	cout<<"From deleteMin"<<endl;
            throw UnderflowException{ };
        }

        array[ 1 ] = std::move( array[ currentSize-- ] );
        percolateDown( 1 );
    }

    /**
     * Remove the minimum item and place it in minItem.
     * Throws Underflow if empty.
     */
    void deleteMin( Comparable & min_ptr )
    {
        if( isEmpty( ) ){
        	cout<<"From void delete Min()compaprable"<<endl;
            throw UnderflowException{ };
        }

        int minPriority = std::move( array[ 1 ].priority );
        min_ptr = std::move( array[ 1 ].ptr2AVL );


        array[ 1 ] = std::move( array[ currentSize-- ] );
        percolateDown( 1 );
    }

    void makeEmpty( )
      { currentSize = 0; }


    void displayArray(){
    	if(!isEmpty()){
    		cout<<setw(18)<< "Heap array index: "<<setw(20)<<"Priority: "<<setw(30)<<"AVLnode ptr points to: "<<endl;
    		for (int i = 1; i<= currentSize;i++){
    		cout<< setw(18)<< i <<setw(20)<< array[ i ].priority<<setw(30)<< array[ i ].ptr2AVL << endl;

    		}
    	}else{
    		cout<<"No display of heap b/c is empty.\n";
    	}

    }
  private:

    vector <HeapNode> array;
    int currentSize;  // Number of elements in heap
    //vector<Comparable> array;        // The heap array




    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; --i )
            percolateDown( i );
    }

    /**
     * Internal method to percolate down in the heap.
     * hole is the index at which the percolate begins.
     */
    void percolateDown( int hole )
    {
        int child; //index of child

        int tmp = std::move( array[ hole ].priority );
        Comparable tmpptr = std::move( array[ hole ].ptr2AVL );
        //comparing int type priority

        for( ; hole * 2 <= currentSize; hole = child )
        {
            child = hole * 2;
            if( child != currentSize && array[ child + 1 ].priority < array[ child ].priority )
                ++child;
            if( array[ child ].priority < tmp ){
                array[ hole ].priority = std::move( array[ child ].priority );
            	array[ hole ].ptr2AVL = std::move( array[ child ].ptr2AVL );
            }
            else
                break;
        }
        array[ hole ].priority = std::move( tmp );
        array[ hole ].ptr2AVL = std::move( tmpptr );
    }
};


#endif /* BINARYHEAP_TWOARG_2_H_ */
