/* Name: Junyi Wu, Chuhuan Huang
* email: juw132@ucsd.edu, chh172@ucsd.edu
* date:04/15/2019
* File: BST.hpp
* Description: This file will construct a binary search tree with functions
* to insert item, and search item inserted into the tree. Also includes
* other basic method which will return basic informations about the tree.
* Source of help: PA1 write up, tutors
*/

#ifndef BST_HPP
#define BST_HPP
#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include <iostream>
using namespace std;

template<typename Data>
class BST {

protected:

  /** Pointer to the root of this BST, or 0 if the BST is empty */
  BSTNode<Data>* root;

  /** Number of Data items stored in this BST. */
  unsigned int isize;

  /** Height of this BST. */
  unsigned int iheight;

public:

  /** define iterator as an aliased typename for BSTIterator<Data>. */
  typedef BSTIterator<Data> iterator;

  /** Default constructor.
  * Initialize an empty BST.
  */
  BST() : root(0), isize(0), iheight(0) {  }


  /** Default destructor.
  * Delete every node in this BST.
  */
  virtual ~BST() {
    deleteAll(root);
  }

  /** Given a reference to a Data item, insert a copy of it in this BST.
  *  Return  true if the item was added to this BST
  *  as a result of this call to insert,
  *  false if an item equal to this one was already in this BST.
  *  Note: This function should use only the '<' operator when comparing
  *  Data items. (should not use ==, >, <=, >=)  For the reasoning
  *  behind this, see the assignment writeup.
  *
  */
  virtual bool insert(const Data& item) {
    //if the tree is empty, insert the data to root and increment the size
    if (empty()) {
      root = new BSTNode<Data>(item);
      isize++;
      return true;
    }

    //if the item is in the list, return false
    if (find(item) != end()) {
      return false;
    }
    BSTNode<Data>* traverse = root;
    BSTNode<Data>* record = root;

    //sort the tree again to have the right order of items
    while (traverse != nullptr) {

      //if item has a larger data than traverse, shift to the right
      if (traverse->data < item) {
        record = traverse;
        traverse = traverse->right;
      }
      else {
        record = traverse;
        traverse = traverse->left;
      }
    }
    //if item has a larger data than the root, place it on th right
    if (record->data < item) {
      record->right = new BSTNode<Data>(item);// can I do this???
      record->right->parent = record;
      isize++;
      return true;
    }

    //if item is smaller, place item on the left
    else {
      record->left = new BSTNode<Data>(item);
      record->left->parent = record;
      isize++;
      return true;
    }
  }


  /** Find a Data item in the BST.
  *  Return an iterator pointing to the item, or pointing past
  *  the last node in the BST if not found.
  *  Note: This function should use only the '<' operator when comparing
  *  Data items. (should not use ==, >, <=, >=).  For the reasoning
  *  behind this, see the assignment writeup.
  *
  */
  virtual iterator find(const Data& item) const {
    // how to specifically call constructor, the format
    // if the list is empty, return the end node
    if (empty())
    return end();

    BSTNode<Data>* traverse = root;

    //if traverse is not null
    while (traverse != nullptr) {
      //check its right if item is larger than data in traverse
      if (traverse->data < item)
      traverse = traverse->right;

      //check left if item is smaller than data in traverse
      else if (item < traverse->data)
      traverse = traverse->left;

      //if data in traverse equal to item, return the iterator
      //at traverse
      else
      return BST::iterator(traverse);
    }
    //if no data in the list equals to item, return the end of the list
    return end();
  }


  /** Return the number of items currently in the BST.
  *
  */
  unsigned int size() const {
    return isize;
  }

  /** Return the height of the BST.
  * The height of an empty tree is -1 and the height of a tree
  * with only one node is 0.
  *
  */

  //helper method to find the height
  unsigned int findHeightFrom(BSTNode<Data>* n) const{
    unsigned int leftResult = 0;
    unsigned int rightResult = 0;

    //height with one node is 0
    if (n->left == nullptr && n->right == nullptr)
    return 0;

    //find height of the left part
    if (n->left != nullptr)
    leftResult = findHeightFrom(n->left);

    //find height of the right part
    if (n->right != nullptr)
    rightResult = findHeightFrom(n->right);

    return 1 + max(leftResult,rightResult);
  }
  unsigned int height() const {

    //if the tree is empty, height is -1
    if (isize==0)
    return -1;

    return findHeightFrom(root);
  }


  /** Return true if the BST is empty, else false.
  */
  bool empty() const {
    return isize == 0;
  }

  /** Return an iterator pointing to the first item in the BST (not the root).
  */
  iterator begin() const {
    return BST::iterator(first(root));
  }

  /** Return an iterator pointing past the last item in the BST.
  */
  iterator end() const {
    return typename BST<Data>::iterator(0);
  }


  /** Inorder traverse BST, print out the data of each node in ascending order.
  * Implementing inorder and deleteAll base on the pseudo code is an easy way to get started.
  * Pseudo Code:
  * if current node is null: return;
  * recursively traverse left sub-tree
  * print current node data
  * recursively traverse right sub-tree
  *
  */

  void inorder() const {
    inorderTraverse(root);
  }
  /** inorder traverse helper method*/
  void inOrderTraverse(BSTNode<Data>* n) const {
    //if current node is null, return
    if (n == nullptr) {return;}
    //traverse left subtree
    if (n->left != nullptr) {inOrderTraverse(n->left);}
    // print current node data
    cout << n->data;
    //traverse right subtree
    if (n->right != nullptr) {inOrderTraverse(n->right);}
  }

private:

  /** Find the first element of the BST
  *
  */
  static BSTNode<Data>* first(BSTNode<Data>* root) {
    if (root->left == nullptr) {return root;}
    else {return first(root->left);}
  }

  /** do a postorder traversal, deleting nodes
  *
  */
  static void deleteAll(BSTNode<Data>* n) {
    /* Pseudo Code:
    if current node is null: return;
    recursively delete left sub-tree
    recursively delete right sub-tree
    delete current node
    */

    //if current node is null, return
    if (n == nullptr) {return;}

    //recursively delete left subtree
    deleteAll(n->left);

    //recursively delete right subtree
    deleteAll(n->right);

    //delete current node
    delete n;
    return;
  }


};


#endif //BST_HPP
