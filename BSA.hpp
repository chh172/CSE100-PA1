/* Name: Junyi Wu, Chuhuan Huang
* email: juw132@ucsd.edu, chh172@ucsd.edu
* date:04/15/2019
* File: BSA.hpp
* Description: This file will construct a binary search array with function *
* to insert item, and search item inserted into the array. One helper
* method is called binarySearch, which will search for the item in
* the array binarily
* Source of help: PA1 write up, tutors
*/

#ifndef BSA_HPP
#define BSA_HPP

#include <vector>
using namespace std;

template<typename Data>

/** This class implements a binary search array */
class BSA {

private:
  vector<Data> v;
  /** Helper method used to either find an element if it exists
  * or else find where it should be inserted.
  */
  virtual size_t binarySearch(const Data& item) const {

    //if the list is empty, return 0
    if (v.size() == 0 )
    return 0;

    int ret = -1;
    int mid;
    int start = 0;
    int end = v.size()-1;

    //while loop to keep using binary search when start !>= end
    while (start <= end) {

      //find the midpoint
      mid  = start + (end - start) / 2;

      //if value at midpoint is smaller than item, go to the
      //right half
      if (v[mid] < item)
      start = mid + 1;

      //if vale at midpoint is bigger than item, move to left half
      else if (item < v[mid])
      end = mid - 1;

      //if they have same value, update ret and exit the loop
      else {
        ret = mid;
        break;
      }
    }

    //if ret equals to mid, return ret
    if (ret == mid)
    return ret;

    //if no value is found, return the index to be inserted
    else if (start < v.size()-1)
    return (v[start] < item) ? start+1 : start;

    //return the new index if item is bigger than all data in array
    else
    return start;
  }

public:
  /** Return the position of item, otherwise v.cend() */
  virtual typename vector<Data>::const_iterator find(const Data& item) const {
    int search = binarySearch(item);
    //return v.cend if array is empty
    if (v.size() == 0)
      return v.cend();

    //if the index is larger than the current size,not found
    //return v.cend
    else if (search > v.size() - 1)
      return v.cend();

    //if the data at index returned does not equal to item
    //return v.cend
    else if (v[search] < item || item < v[search])
      return v.cend();

    //otherwise return the index
    else
      return v.begin() + search;

  }

  /** Insert item into sorted position */
  virtual bool insert(const Data& item) {

    //if the array is empty, insert to the array
    if (v.size() == 0) {
      v.insert(v.begin(),item);
        return true;
    }

    //if the item is not in the array, insert into correct index
    if (find(item) == v.cend()) {
      v.insert(v.begin() + binarySearch(item),item);
        return true;
    }

    //else do not insert and return false
    return false;
  }

  typename vector<Data>::iterator begin() const {
    return v.begin();
  }

  typename vector<Data>::iterator end() const {
    return v.end();
  }
};

#endif
