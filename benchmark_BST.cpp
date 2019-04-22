/* Name: Junyi Wu, Chuhuan Huang
 * email: juw132@ucsd.edu, chh172@ucsd.edu
 * date:04/15/2019
 * File: benchmark_BST.cpp
 * Description: This file will call insert and find in both BSA and BST, and
 * calculate the runtime of different trials with same amount of data and
 * print out the average runtime of the two functions of BSA and BST
 * Source of help: PA1 write up, tutors
 */

#include <iostream>
#include "BSA.hpp"
#include "BST.hpp"
#include "Timer.hpp"

using namespace std;

/** Returns a vector of random double values with range [min, max]
 *  Note that rand() returns bad random numbers, but for simplicity,
 *  we use it to serve our purpose here.
 */
vector<double> randNums(unsigned int size, int min, int max) {
    vector<double> result;
    for (unsigned int i = 0; i < size; i++) {
        result.push_back((max - min) * ( (double)rand() /
                                        (double)RAND_MAX ) + min);
    }
    return result;
}

int main () {
    // value to change to do benchmarking
    const int MIN = 0; // min value of random data
    const int MAX = 100; // max value of random data
    const int NUM_INSERT = 60000; // number of random data to insert
    const int NUM_FIND = 60000; // number of random data to find
    const int NUM_RUN = 10;
    
    vector<double> insertData = randNums(NUM_INSERT, MIN, MAX);
    vector<double> findData = randNums(NUM_FIND, MIN, MAX);
    
    BSA<double> bsa;
    BST<double> bst;
    
    cout << "Insert benchmarking for BSA and BST: " << endl;
    cout << "Number of data to insert: " << NUM_INSERT << endl;
    
    Timer t;
    long long sumTime = 0;
    long long averageTime = 0;
    
    //calculate runtime for 10 times
    for(int j=0;j<NUM_RUN;j++){ 
        t.begin_timer();
    	for(int i =0;i<NUM_INSERT;i++){
		bsa.insert(insertData[i]);
    	}
	long long time=t.end_timer();
	sumTime=sumTime+time;
    //reintialize the bsa
	bsa=BSA<double>();
    }
    //calculate average time for the 10 trials
    averageTime=sumTime/NUM_RUN;
   
    
    cout << "Average time taken to insert for BSA: " << averageTime
    << " milliseconds" << endl;
    
    sumTime = 0;
    averageTime = 0;
    //calculate runtime using timer for 10 times
    for(int j=0;j<NUM_RUN;j++){ 
	t.begin_timer();
    	for(int i =0;i<NUM_INSERT;i++){
		bst.insert(insertData[i]);
    	}
	long long time=t.end_timer();
	sumTime=sumTime+time;
	//reinitialize bst
	bst=BST<double>();
    }
    //calculate the average time
    averageTime=sumTime/NUM_RUN;
    

    
    cout << "Average time taken to insert for BST: " << averageTime
    << " milliseconds" << endl;
    
    cout << endl; // new line
    
    cout << "Find benchmarking for BSA and BST: " << endl;
    cout << "Number of data in BSA/BST: " << NUM_INSERT << endl;
    cout << "Number of data to find: " << NUM_FIND << endl;

    //First insert the doubles to bst and bsa
    for(int i=0; i<NUM_INSERT;i++){
	bst.insert(insertData[i]);
	bsa.insert(insertData[i]);
    }

    sumTime = 0;
    averageTime = 0;
    //calculate runtime of finding 30000 doubles
    for(int j=0;j<NUM_RUN;j++){ 
	t.begin_timer();
    	for(int i =0;i<NUM_FIND;i++){
		bsa.find(findData[i]);
    	}
	long long time=t.end_timer();
	sumTime=sumTime+time;
	//reinitialize the bsa
	bsa=BSA<double>();
    }
    //calculate the average time 
    averageTime=sumTime/NUM_RUN;
    


    
    cout << "Average time taken to find for BSA: " << averageTime
    << " milliseconds" << endl;
    
    sumTime = 0;
    averageTime = 0;
    //calculate the runtime
    for(int j=0;j<NUM_RUN;j++){ 
	t.begin_timer();
    	for(int i =0;i<NUM_FIND;i++){
		bst.find(findData[i]);
    	}
	long long time=t.end_timer();
	sumTime=sumTime+time;
	//reinitialize the bst
	bst=BST<double>();
    }
    //calculate average time
    averageTime=sumTime/NUM_RUN;
    


    
    cout << "Average time taken to find for BST: " << averageTime
    << " milliseconds" << endl;
    
}
