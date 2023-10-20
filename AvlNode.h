
#ifndef AVLNODE_H_
#define AVLNODE_H_
#include <iostream>
#include <sstream>
#include <string>
#include "dsexceptions.h"
#include <vector>
using namespace std;

template <typename Comparable>
    struct AvlNode
    {

        Comparable prj; //task id
        int heapIndex; //starting from 1
        AvlNode   *left;
        AvlNode   *right;
        int       height;

//        AvlNode()
        AvlNode( const Comparable & ele, const int & ind, AvlNode *lt, AvlNode *rt, int h = 0 )
          : prj{ ele },heapIndex{ ind }, left{ lt }, right{ rt }, height{ h } { }

        AvlNode( Comparable && ele,const int & ind, AvlNode *lt, AvlNode *rt, int h = 0 )
          : prj{ std::move( ele ) }, heapIndex{ std::move( ind ) },left{ lt }, right{ rt }, height{ h } { }
    };



#endif /* AVLNODE_H_ */
