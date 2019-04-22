/* Name: Junyi Wu, Chuhuan Huang
* email: juw132@ucsd.edu, chh172@ucsd.edu
* date:04/22/2019
* File: KDT.hpp
* Description: this file contains the KDTree class and a KDNode inner class.
* a build method and a KNN method.
* Source of help: PA1 write up, tutors
*/
#ifndef KDT_HPP
#define KDT_HPP

#include <algorithm> // sort, max, min
#include <math.h>    // pow, abs
#include <vector>    // vector<typename>
#include "Point.hpp"
#include <queue>
#include <iostream>
using namespace std;

/** A KD tree that can output K nearest neighbors of given query point */
class KDT {

protected:

  /** Inner class that diefines a KDNode with certain data point
  *  and pointers to its children and parent
  */
  class KDNode {

  public:

    KDNode * left;
    KDNode * right;
    KDNode * parent;
    Point point;
    bool otherBranchChecked;
    KDNode() {}

    KDNode(Point point) : point(point) {
      left = right = parent = nullptr;
    }
  };


  KDNode * root; // root of KD tree
  unsigned int numDim; // number of dimension of data points
  unsigned int k; // number of nearest neighbors to find
  double threshold; // largest distance to query point in current KNN
  unsigned int isize;
  unsigned int iheight;
  struct Priority {
    bool operator() (const Point & p1, const Point & p2) {
      return p1.squareDistToQuery <  p2.squareDistToQuery;
      // questions!!!
      // if return true, will the PQ place p2 on top of p1?
    }
  };
  // define a data structure to store current K nearest neighbors
  priority_queue<Point,vector<Point>,Priority> v;
public:

  /** : Default constructor of KD tree */
  KDT() {
    root = nullptr;
    numDim = k = isize = iheight = 0;
    threshold = INFINITY;
  }
  /** destructor of kdTree*/
  ~KDT() {
    deleteAll(root);
  }
  /** Build the KD tree from the given vector of Point references */
  void build(vector<Point>& points) {
    if (points.empty()) {return;}
    // edge case
    this->numDim = points[0].numDim;
    // init numDim
    isize = points.size();
    // init isize
    root = buildSubtree(points,0,points.size(),0,0);
    // init root
  }

  /** Find k nearest neighbors of the given query point */
  vector<Point> findKNearestNeighbors(Point queryPoint, unsigned int k) {
    // make sure v starts with empty
    while (!v.empty()) {
      v.pop();
    }
    this->k = k;
    // init k
    findKNNHelper(root,queryPoint,0);
    // find knn from root
    vector<Point> ret {};
    // declare the return vector
    // copy from PQ
    while (!v.empty()) {
      ret.push_back(move(v.top()));// questions!!
      v.pop();
    }
    // re init the threshold for next time use
    threshold = INFINITY;
    return ret;
  }

  /** Return the size of the KD tree */
  unsigned int size() {
    return isize;
  }

  /** Return the height of the KD tree */
  unsigned int height() {
    return iheight;
  }
  void deleteAll(KDNode* n) {
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
private:

  /** Helper method to recursively build the subtree of KD tree. */
  KDNode * buildSubtree(vector<Point>& points, unsigned int start,
    unsigned int end, unsigned int d, unsigned int height) {
      // base case
      if (start >= end ) {
        return nullptr;
      }
      // update iheight
      if (height > iheight) {
        iheight = height;
      }
      // sort the vector and choose the median node
      sort(points.begin() + start, points.begin() + end, CompareValueAt(d));
      // construct a new KDNode
      KDNode * median = new KDNode(points[start + (end - start)/2]);
      // recursively build
      median->left = buildSubtree(points,start,start + (end - start)/2
      ,(d+1)%numDim,height + 1);
      if (median->left != nullptr) {
        median->left->parent = median;
        // connect with parent node if applicable
      }
      // recursively build
      median->right = buildSubtree(points,start + (end - start)/2 + 1,end
      ,(d+1)%numDim,height + 1);
      if (median->right != nullptr) {
        median->right->parent = median;
        // connect with parent node if applicable
      }
      return median;
    }

    /** Helper method to recursively find the K nearest neighbors */
    void findKNNHelper(KDNode *node, const Point & queryPoint, unsigned int d){
      // base case
      if (node == nullptr) {
        return;
      }
      // calc the squared distance in Dimension d
      double temp = getSqDistInD(node->point, queryPoint, d%numDim);
      if ( goToLeft(node->point,queryPoint,d)) {
        // if go to left subtree, recursively call findKNNHelper
        findKNNHelper(node->left,queryPoint,(d+1)% numDim);
        if(threshold >= temp) {
          // if criterion holds, it is necessay to check other branch.
          findKNNHelper(node->right,queryPoint,(d+1)% numDim);
        }
      }
      else {
        // if go to right subtree, recursively call findKNNHelper
        findKNNHelper(node->right,queryPoint,(d+1)% numDim);
        if (threshold >= temp) {
          // if criterion holds, it is necessay to check other branch.
          findKNNHelper(node->left,queryPoint,(d+1)% numDim);
        }
      }
      // set up the squareDistToQuery
      node->point.setSquareDistToQuery(queryPoint);
      // UPDATE THE PQ
      updateKNN(node->point);
    }

    /** Helper method to update your data structure storing KNN using
    *  the given point.
    */
    void updateKNN(Point & point) {
      // if PQ not full, insert the node
      if (v.size() < k) {
        v.push(point);
        // set up the threshold instantly after it is full
        if (v.size() == k) {
          threshold = getThreshold(v);
        }
      }
      else  {
        // compare the point with threshold
        // if within,take it and pop out the one with greatest squareDistToQuery
        if(point.squareDistToQuery < threshold) {
          v.pop();
          v.push(point);
          threshold = getThreshold(v);//update threshold
        }
      }
    }

    /** helper function to get the threshold*/
    double getThreshold(priority_queue<Point,vector<Point>,Priority> & v) {
      if (v.empty()) {
        return INFINITY;
      }
      return v.top().squareDistToQuery;
    }

    /** helper function to calc the squared distance in dimension d*/
    double getSqDistInD(const Point & p1, const Point & p2, unsigned int d) {
      return pow(p1.features[d] - p2.features[d],2.0);
    }

    /** helpe  funciton to decide if go to left subtree*/
    bool goToLeft(const Point & p1, const Point & p2, unsigned int d) {
      return p1.features[d] > p2.features[d];
    }

  };// I love atom, Greatest IDE of all time.
  #endif // KDT_HPP
