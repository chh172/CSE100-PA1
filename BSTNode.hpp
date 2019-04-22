/* Name: Junyi Wu, Chuhuan Huang
 * email: juw132@ucsd.edu, chh172@ucsd.edu
 * date:04/15/2019
 * File: BSTNode.hpp
 * Description: This file includes the constructor of a BSTnode and also includes
 * the method to return the successor of the current node
 * Source of help: PA1 write up
 */


#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iostream>
#include <iomanip>
using namespace std;

template<typename Data>
class BSTNode {

	public:

		BSTNode<Data>* left;
		BSTNode<Data>* right;
		BSTNode<Data>* parent;
		Data const data;   // the const Data in this node.

		/** Constructor.  Initialize a BSTNode with the given Data item,
		 *  no parent, and no children.
		 *  
		 */
		BSTNode(const Data & d) 
			:data(d) { left = right = parent = nullptr; 
		}
		/** Return the successor of this BSTNode in a BST, or 0 if none.
		 *  PRECONDITION: this BSTNode is a node in a BST.
		 *  POSTCONDITION:  the BST is unchanged.
		 *  RETURNS: the BSTNode that is the successor of this BSTNode,
		 *  or 0 if there is none. 
		 */
		BSTNode<Data>* successor() {
			if (this->right != nullptr) { // if has right subtree
				// all the way right until end 
				BSTNode<Data>* traverse = this->right;
				while (traverse->left != nullptr) {
					traverse = traverse->left;
				}
				return traverse;
			}
			else {
			// find the first left child in his ancestors and
			// the parent of that ancestor is the successor node
				BSTNode<Data>* traverse = this->parent;
				BSTNode<Data>* n = this;
				while (traverse != nullptr 
					&& n ==  traverse->right) {
					n = traverse;
					traverse = traverse->parent;
				} 
				return traverse;
			}
		}

}; 

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
ostream & operator<<(ostream& stm, const BSTNode<Data> & n) {
	stm << '[';
	stm << setw(10) << &n;                 // address of the BSTNode
	stm << "; p:" << setw(10) << n.parent; // address of its parent
	stm << "; l:" << setw(10) << n.left;   // address of its left child
	stm << "; r:" << setw(10) << n.right;  // address of its right child
	stm << "; d:" << n.data;               // its data field
	stm << ']';
	return stm;
}

#endif // BSTNODE_HPP
