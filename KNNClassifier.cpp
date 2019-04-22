/* Name: Junyi Wu, Chuhuan Huang
* email: juw132@ucsd.edu, chh172@ucsd.edu
* date:04/22/2019
* File: KNNClassifier.cpp
* Description: this file contains several readin methods and a main function to
* interact with user
* Source of help: PA1 write up, tutors
*/
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <iterator>
#include "KDT.hpp"
#include "Point.hpp"
#include "BruteForceKNN.hpp"

using namespace std;

/** Read the data from file and convert them to vector of points.
*  Each line of the file contains data in each dimension of the
*  features (and potentially label) of one data point.
*  The boolean withLabel indicates if the last value in a line
*  is a label of the data point.
*/
vector<Point> readData(const char * fileName, bool withLabel) {

  vector<Point> result;
  string line;
  int numDim = 0;
  double data = 0;

  ifstream in;
  in.open(fileName, ios::binary);

  // count number of dimensions
  getline(in, line);
  stringstream lineStream(line);
  while (lineStream >> data) numDim++;
  if (withLabel) numDim--;

  //Resets the stream to beginning of file
  in.seekg(0, ios_base::beg);

  // read the data and convert them to data points
  while (!in.eof()) {
    vector<double> features;
    int label = 0;
    for (int i = 0; i < numDim; i++) {
      in >> data;
      if (!in.fail()) {
        features.push_back(data);
      }
    }
    if (withLabel) {
      in >> label;
    }
    if (!in.fail()) {
      result.push_back(Point(features, label));
    }
  }

  in.close();
  return result;
}
/** The comparator used in sorting points based of label*/
struct CompareLabelValue {
  int label;
  CompareLabelValue(int label){
    this->label=label;
  }
  bool operator() (const Point & p1, const Point & p2) {
    return p1.label < p2.label;
  }
};
/** Find the most frequent label in the given set of points */
int mostFreqLabel(vector<Point>& points) {
  std::unordered_map<int,int> table;
  // init map
  for (unsigned int i = 0; i < points.size();i++) {
    if (table.find(points[i].label) == table.end()) {
      // if cannot find given key, insert one.
      table.insert(std::pair<int,int>(points[i].label,1));
    }
    else {
      // increment the value of found key.
      table[points[i].label]++;
    }
  }
  std::unordered_map<int,int>::iterator record = table.begin();
  // init the record iterator.
  for (auto it = table.begin(); it != table.end(); it++) {
    if ((record->second < it->second)
          ||(record->second == it->second && record->first > it->first)) {
      // update the record iterator if
      // case 1: record->second, the value or the count less than it->second
      // case 2: same count but record has greater label.
      record = it;
    }
  }
  return record->first;
  // return that label
}

/** Check if a given data file is valid. Note that his does not
* check if the data file is in correct format
*/
bool fileValid(const char * fileName) {

  ifstream in;
  in.open(fileName, ios::binary);

  // Check if input file was actually opened
  if(!in.is_open()) {
    cout<< "Invalid input file. No file was opened. Please try again.\n";
    in.close();
    return false;
  }

  // Check for empty file
  in.seekg(0, ios_base::end);
  int len = (int) in.tellg();
  if(len == 0) {
    cout << "The file is empty. \n";
    in.close();
    return false;
  }

  in.close();
  return true;
}
/** the main function */
int main(int argc, const char * argv[]) {

  KDT kdTree = KDT();
  // init tree.
  vector<Point> input;
  // init vector input
  int mismatch = 0;
  // init mismatch record
  string param4(argv[4]);
  // construct string
 //check if the file is valid and build kdt
  if((fileValid(argv[2]))&&(fileValid(argv[3]))){
    vector<Point> read = readData(argv[2],true);
    // construct a reference
    kdTree.build(read);
  }
  //check if have 4 parameters
  if(argc!=5){
    return -1;
  }
  //create output
  ofstream output;
  output.open("result.txt",ios::out | ios::app);

  //compare the input string

  if(param4.compare("validation") == 0){
    input = readData(argv[3],true);
    // init iput with readin file
    int convertedK = std::stoi(argv[1],nullptr);
    // convert the string to int
    for(unsigned int i = 0; i < input.size(); i++){
      vector<Point> findKNN = kdTree.findKNearestNeighbors(input[i],convertedK);
      // construct reference for KNN
      if(mostFreqLabel(findKNN)!=input[i].label){
        mismatch++;
        // record the mismatch
      }
    }

    double error = (double)mismatch/(double)input.size();
    // calc validation error
    output<<"K:"<<argv[1]<<",Validation Error:"<<error<<endl;
    // print
  }
  if(param4.compare("test") == 0){
    input = readData(argv[3],false);
    // init iput with readin file
    for(unsigned int i = 0;i < input.size(); i++){
      int convertedK2 = std::stoi(argv[1],nullptr);
      // convert the string to int
      vector<Point> fdKNN2 = kdTree.findKNearestNeighbors(input[i],convertedK2);
      // construct reference for KNN
      output<<mostFreqLabel(fdKNN2)<<endl;
      // print
    }
  }

  output.close();
  // close the file and return
  return 0;
}
