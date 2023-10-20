#ifndef AVLTREE_H
#define AVLTREE_H
//my homework code
#include "dsexceptions.h"
#include <algorithm>
#include <iostream> 
#include "BinaryHeap.h"
#include "AvlNode.h"
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x ,y )       --> Insert prjecy Id x and array index y
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin_heapIndex( )  --> Return smallest priority's heap index
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template<typename Comparable>
class AvlTree {
public:
	void displayTree(ostream &out = cout) const {
		if (isEmpty())
			out << "Empty tree" << endl;
		else
			displayTree(root, 0, out);
	}

	void displayTree(ostream &out = cout) {
		if (isEmpty())
			out << "Empty tree" << endl;
		else
			displayTree(root, 0, out);
	}

	int contains_search_depth(const Comparable &x) {
		return contains_search_depth(x, root);

	}

	const int contains_search_depth(const Comparable &x) const {
		return contains_search_depth(x, root);

	}

	void displayLinks(ostream &out = cout) const {
		if (isEmpty())
			out << "Empty tree" << endl;
		else
			displayLinks(root, 0, out);
	}
//	    int height( ){
//	    	 return height(root);
//	    }
	int depth(Comparable &x) {
		return depth(x, root);
	}

	int depth(Comparable &x) const {
		return depth(x, root);
	}

	int height() {
		return height(root);
	}

	int height() const {
		return height(root);
	}

	AvlTree() {
		root = nullptr;
	}

	AvlTree(const AvlTree &rhs) :
			root { nullptr } {
		root = clone(rhs.root);
	}

	AvlTree(AvlTree &&rhs) :
			root { rhs.root } {
		rhs.root = nullptr;
	}

	~AvlTree() {
		makeEmpty();
	}

	/**
	 * Deep copy.
	 */
	AvlTree& operator=(const AvlTree &rhs) {
		AvlTree copy = rhs;
		std::swap(*this, copy);
		return *this;
	}

	/**
	 * Move.
	 */
	AvlTree& operator=(AvlTree &&rhs) {
		std::swap(root, rhs.root);

		return *this;
	}

	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable& findMin() const {

		return findMin(root)->prj;
	}

	const int& findMin_heapIndex() const {

		return findMin(root)->heapIndex;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable& findMax() const {

		return findMax(root)->prj;
	}

	/**
	 * Returns true if x is found in the tree.
	 */
	bool contains(const Comparable &x) const {
		return contains(x, root);
	}

	void set_index(const Comparable &x, const int &new_index) const {
		set_index(x, new_index, root);
	}
	AvlNode<Comparable>* get_avlNodePtr_from_prj(const Comparable &x) const {
		return get_avlNodePtr_from_prj(x, root);
	}
	AvlNode<Comparable>* get_avlNodePtr_from_ind(const int &ind) const {
		return get_avlNodePtr_from_ind(ind, root);
	}

	int& get_heapIndex_from_prj(const Comparable &prj_num) const {
		return get_heapIndex_from_prj(prj_num, root);
	}

	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 */
	bool isEmpty() const {
		return root == nullptr;
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	void printTree() const {
		if (isEmpty())
			cout << "Empty tree" << endl;
		else
			printTree(root);
	}

	/**
	 * Make the tree logically empty.
	 */
	void makeEmpty() {
		makeEmpty(root);
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert(const Comparable &x, const int &y) //edited
			{
		insert(x, y, root);
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert(Comparable &&x, int &&y) //edited
			{
		insert(std::move(x), std::move(y), root);
	}

	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 */
	void remove(const Comparable &x) {
		remove(x, root);
	}

private:

	AvlNode<Comparable> *root;

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */

	void displayTree(AvlNode<Comparable> *t, int depth, ostream &out) {
		const int SHIFT = 4;
		if (t != nullptr) {
			for (int i = 0; i < SHIFT * depth; i++) {
				out << " ";
			}
			out << t->prj << "/" << t->heapIndex << endl;
			displayTree(t->left, depth + 1, out);
			displayTree(t->right, depth + 1, out);
		}
	}

	int contains_search_depth(const Comparable &x, AvlNode<Comparable> *t) {
		if (contains(x)) {
			return depth(x, t);
		}
		AvlNode<Comparable> *temp;
		while (t != nullptr) {
			if (x < t->prj) {
				temp = t;
				t = t->left;
			} else if (t->prj < x) {
				temp = t;
				t = t->right;
			}
		}

		return depth(temp->prj);

	}

	const int contains_search_depth(const Comparable &x,
			AvlNode<Comparable> *t) const {
		if (contains(x)) {
			return depth(x, root);
		}
		AvlNode<Comparable> *temp;
		while (t != nullptr) {
			if (x < t->prj) {
				temp = t;
				t = t->left;
			} else if (t->prj < x) {
				temp = t;
				t = t->right;
			}
		}

		return depth(temp->prj);

	}

	void insert(const Comparable &x, const int &y, AvlNode<Comparable> *&t) //edited
			{
		if (t == nullptr)
			t = new AvlNode<Comparable> { x, y, nullptr, nullptr };
		else if (x < t->prj)
			insert(x, y, t->left);
		else if (t->prj < x)
			insert(x, y, t->right);

		balance(t);
	}

	/**
	 * Internal method to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */
	void insert(Comparable &&x, int &&y, AvlNode<Comparable> *&t) {
		if (t == nullptr)
			t = new AvlNode<Comparable> { std::move(x), std::move(y), nullptr,
					nullptr };
		else if (x < t->prj)
			insert(std::move(x), std::move(y), t->left);
		else if (t->prj < x)
			insert(std::move(x), std::move(y), t->right);

		balance(t);
	}

	/**
	 * Internal method to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Set the new root of the subtree.
	 */

	void remove(const Comparable &x, AvlNode<Comparable> *&t) {
		if (t == nullptr)
			return;   // Item not found; do nothing

		if (x < t->prj)
			remove(x, t->left);
		else if (t->prj < x)
			remove(x, t->right);
		else if (t->left != nullptr && t->right != nullptr) // Two children
				{
			t->prj = findMin(t->right)->prj;
			t->heapIndex = findMin(t->right)->heapIndex;
			remove(t->prj, t->right);
		} else {
			AvlNode<Comparable> *oldNode = t;
			t = (t->left != nullptr) ? t->left : t->right;
			delete oldNode;
		}

		balance(t);
	}
	static const int ALLOWED_IMBALANCE = 1;

	// Assume t is balanced or within one of being balanced
	void balance(AvlNode<Comparable> *&t) {
		if (t == nullptr)
			return;

		if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
			if (height(t->left->left) >= height(t->left->right))
				rotateWithLeftChild(t);
			else
				doubleWithLeftChild(t);
		else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
			if (height(t->right->right) >= height(t->right->left)) {
				rotateWithRightChild(t);
			} else
				doubleWithRightChild(t);
		}

		t->height = max(height(t->left), height(t->right)) + 1;
	}

	/**
	 * Internal method to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	AvlNode<Comparable>* findMin(AvlNode<Comparable> *t) const {
		if (t == nullptr)
			return nullptr;
		if (t->left == nullptr)
			return t;
		return findMin(t->left);
	}

	/**
	 * Internal method to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	AvlNode<Comparable>* findMax(AvlNode<Comparable> *t) const {
		if (t != nullptr)
			while (t->right != nullptr)
				t = t->right;
		return t;
	}

	/**
	 * Internal method to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the tree.
	 */
	bool contains(const Comparable &x, AvlNode<Comparable> *t) const {
		if (t == nullptr)
			return false;
		else if (x < t->prj)
			return contains(x, t->left);
		else if (t->prj < x)
			return contains(x, t->right);
		else
			return true;    // Match
	}
	int& get_heapIndex_from_prj(const Comparable &prj_num,
			AvlNode<Comparable> *t) const {
		if (!contains(prj_num)) {
			throw UnderflowException { };
		}
		if (prj_num < t->prj)
			return get_heapIndex_from_prj(prj_num, t->left);
		else if (t->prj < prj_num)
			return get_heapIndex_from_prj(prj_num, t->right);
		else
			return t->heapIndex;    // Match
	}

	AvlNode<Comparable>* get_avlNodePtr_from_prj(const Comparable &x,
			AvlNode<Comparable> *t) const {
		if (t == nullptr)
			return nullptr;
		else if (x < t->prj)
			return get_avlNodePtr_from_prj(x, t->left);
		else if (t->prj < x)
			return get_avlNodePtr_from_prj(x, t->right);
		else
			return t;    // Match
	}

	AvlNode<Comparable>* get_avlNodePtr_from_ind(const int &ind,
			AvlNode<Comparable> *t) const {
		if (t == nullptr) {
			return nullptr;
		}
		if (t->heapIndex == ind) {
			return t;
		}

		if (get_avlNodePtr_from_ind(ind, t->left) != nullptr) {
			return get_avlNodePtr_from_ind(ind, t->left);
		}
		if (get_avlNodePtr_from_ind(ind, t->right) != nullptr) {
			return get_avlNodePtr_from_ind(ind, t->right);
		}
		return nullptr;

	}

	//update project x's array index to y
	//assume proj x is in the tree
	void set_index(const Comparable &x, const int &new_index,
			AvlNode<Comparable> *t) const {
		if (t == nullptr)
			return;
		else if (x < t->prj) {
			set_index(x, new_index, t->left);
			return;
		} else if (t->prj < x) {
			set_index(x, new_index, t->right);
			return;
		} else {
			t->heapIndex = new_index;
			return;
		}
		// Match
	}

	/****** NONRECURSIVE VERSION*************************
	 bool contains( const Comparable & x, AvlNode<Comparable> *t ) const
	 {
	 while( t != nullptr )
	 if( x < t->prj )
	 t = t->left;
	 else if( t->prj < x )
	 t = t->right;
	 else
	 return true;    // Match

	 return false;   // No match
	 }
	 *****************************************************/

	/**
	 * Internal method to make subtree empty.
	 */
	void makeEmpty(AvlNode<Comparable> *&t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = nullptr;
	}

	/**
	 * Internal method to print a subtree rooted at t in sorted order.
	 */
	void printTree(AvlNode<Comparable> *t) const {
		if (t != nullptr) {
			printTree(t->left);
			cout << t->prj << endl;
			printTree(t->right);
		}
	}

	/**
	 * Internal method to clone subtree.
	 */
	AvlNode<Comparable>* clone(AvlNode<Comparable> *t) const {
		if (t == nullptr)
			return nullptr;
		else
			return new AvlNode<Comparable> { t->prj, clone(t->left), clone(
					t->right), t->height };
	}
	// Avl manipulations
	/**
	 * Return the height of node t or -1 if nullptr.
	 */
	int height(AvlNode<Comparable> *t) const {
		return t == nullptr ? -1 : t->height;
	}

	int height(AvlNode<Comparable> *t) {
		return t == nullptr ? -1 : t->height;
	}

	int max(int lhs, int rhs) const {
		return lhs > rhs ? lhs : rhs;
	}

	/**
	 * Rotate binary tree node with left child.
	 * For AVL trees, this is a single rotation for case 1.
	 * Update heights, then set new root.
	 */
	void rotateWithLeftChild(AvlNode<Comparable> *&k2) {
		AvlNode<Comparable> *k1 = k2->left;
		k2->left = k1->right;
		k1->right = k2;
		k2->height = max(height(k2->left), height(k2->right)) + 1;
		k1->height = max(height(k1->left), k2->height) + 1;
		k2 = k1;
	}

	/**
	 * Rotate binary tree node with right child.
	 * For AVL trees, this is a single rotation for case 4.
	 * Update heights, then set new root.
	 */
	void rotateWithRightChild(AvlNode<Comparable> *&k1) {
		AvlNode<Comparable> *k2 = k1->right;
		k1->right = k2->left;
		k2->left = k1;
		k1->height = max(height(k1->left), height(k1->right)) + 1;
		k2->height = max(height(k2->right), k1->height) + 1;
		k1 = k2;
	}

	/**
	 * Double rotate binary tree node: first left child.
	 * with its right child; then node k3 with new left child.
	 * For AVL trees, this is a double rotation for case 2.
	 * Update heights, then set new root.
	 */

	void doubleWithLeftChild(AvlNode<Comparable> *&k3) {
		rotateWithRightChild(k3->left);
		rotateWithLeftChild(k3);
	}

	/**
	 * Double rotate binary tree node: first right child.
	 * with its left child; then node k1 with new right child.
	 * For AVL trees, this is a double rotation for case 3.
	 * Update heights, then set new root.
	 */
	void doubleWithRightChild(AvlNode<Comparable> *&k1) {
		rotateWithLeftChild(k1->right);
		rotateWithRightChild(k1);
	}
	void displayLinks(AvlNode<Comparable> *t, int depth, ostream &out) const {
		const int SHIFT = 4;
		if (t != nullptr) {
			for (int i = 0; i < SHIFT * depth; i++) {
				out << " ";
			}

			out << t->prj << "/" << t->heapIndex << ") @:" << t << endl;
			;
			displayLinks(t->left, depth + 1, out);
			displayLinks(t->right, depth + 1, out);
		}
	}
//origianl display links
//    void displayLinks( AvlNode<Comparable> *t, int depth, ostream & out )const
//        {
//            const int SHIFT = 4 ;
//            if( t != nullptr )
//            {
//                for( int i = 0 ; i < SHIFT*depth ; i++ ){ out << " " ; }
//                //out << t->prj << endl;
//                out << t->prj <<") @:" << t << "  L:"<< t->left<< " R:" << t->right <<endl;;
//                displayLinks( t->left, depth+1, out );
//                displayLinks( t->right, depth+1, out );
//            }
//        }

//        int height(AvlNode<Comparable>* nodeA){
//        	if (isLeaf(nodeA)){
//        		return 1;
//        	}else if (hasOneLeftChild(nodeA)){
//
//        		return 1+height(nodeA->left);
//        	}else if (hasOneRightChild(nodeA)){
//
//        		return 1+height(nodeA->right);
//        	}else{
//
//        		return 1+max(height(nodeA->left),height(nodeA->right));
//
//        }
//        }
	bool hasTwoChild(AvlNode<Comparable> *node1) {
		return (node1->left != nullptr && node1->right != nullptr);
	}

	bool isLeaf(AvlNode<Comparable> *node1) {
		return (node1->left == nullptr && node1->right == nullptr);
	}

	bool hasOneLeftChild(AvlNode<Comparable> *node1) {
		return (node1->left != nullptr && node1->right == nullptr);
	}

	bool hasOneRightChild(AvlNode<Comparable> *node1) {
		return (node1->left == nullptr && node1->right != nullptr);
	}

	int depth(const Comparable &x, AvlNode<Comparable> *t) { //assume x is in the tree
		while (t->prj != x) {
			if (x > t->prj) {
				return 1 + depth(x, t->right);
			}
			if (x < t->prj) {
				return 1 + depth(x, t->left);
			}
		}
		return 0;
	}
};

#endif
