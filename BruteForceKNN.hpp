/* Name: Junyi Wu, Chuhuan Huang
* email: juw132@ucsd.edu, chh172@ucsd.edu
* date:04/22/2019
* File: BruteForceKNN.hpp
* Description: this file contains several readin methods and a main function to
* interact with user
* Source of help: PA1 write up, tutors
*/
#ifndef BruteForceKNN_hpp
#define BruteForceKNN_hpp

#include <algorithm> // sort, max, min
#include <math.h>    // pow, abs
#include <vector>    // vector<typename>
#include <limits>    // numeric_limits<type>::max()
#include "Point.hpp"

/** A brute force approach to find K nearest neighbors */
class BruteForceKNN {

protected:

    vector<Point> trainingPoints;
    int k;
    double threshold;

    struct Priority {
      bool operator() (const Point & p1, const Point & p2) {
        return p1.squareDistToQuery > p2.squareDistToQuery;
      }
    };
    // define a data structure to store current K nearest neighbors
    priority_queue<Point,vector<Point>,Priority> v;

public:


    /** Default constructor */
    BruteForceKNN() {

      threshold=INFINITY;




    }

    /** Initialize the training data points */
    void build(vector<Point>& points) {
          if (points.empty()) {return;}
          trainingPoints=points;
    }

    /** Find k nearest neighbors of the given query point */
    vector<Point> findKNearestNeighbors(Point & queryPoint, unsigned int k) {
      this->k=k;
      while (!v.empty()) {
        v.pop();
      }
      for(unsigned int i=0; i<this->trainingPoints.size();i++){
        trainingPoints[i].setSquareDistToQuery(queryPoint);
        updateKNN(trainingPoints[i]);
      }
      vector<Point> ret {};
      for (unsigned int i = 0; i < v.size(); i++) {
        ret.insert(ret.begin()+i,v.top());
        v.pop();
      }
      threshold = INFINITY;
      return ret;
    }

    /** Helper method to update your data structure storing KNN using
     * the given point. */
    void updateKNN(Point & point) {
      int size = v.size();
      if (size < k) {
        v.push(point);
        //
        if (size == k) {
          threshold = v.top().squareDistToQuery;
        }
      }
      else {

        //update threshold
        if(point.squareDistToQuery < threshold) {
          v.pop();// how to define that priority queue view point with largest squareD as top priority?
          v.push(point);

          threshold = v.top().squareDistToQuery;//update threshold
        }
      }
    }



};

#endif /* BruteForceKNN_hpp */
