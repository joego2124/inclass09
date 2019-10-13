#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdlib>
#include <ctime>

using namespace std;

//declare SortableArray class
class SortableArray {
    private:
        double *arr;
        int len;

        //merge two sub arrays from one array to another
        void merge(double *donorPtr, double *receiverPtr, unsigned int secondStartIndex, unsigned int start, unsigned int end);

        //recursively splits and merges array
        void split(double *prePtr, double *postPtr, unsigned int startIndex, unsigned int endIndex);

    public:
        //default constructor
        SortableArray();

        //constructor with size
        SortableArray(unsigned int n);

        //returns pointer for array's first element
        double *getPointer();

        //returns length of array
        int getLength();

        //initialize array to be all zeros
        void zeros();

        //generate random double for each value in array between max and min
        void random(double min, double max);

        //writes out array to a file
        void write(ofstream &f, bool sorted);

        //full implementation of merge sort
        void mergeSort();
};
