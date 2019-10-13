#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdlib>
#include <ctime>

#include "SortableArray.h"

using namespace std;

//merge two sub arrays from one array to another
void SortableArray::merge(double *donorPtr, double *receiverPtr, unsigned int secondStartIndex, unsigned int start, unsigned int end) {

    //ini pointers
    double *blackPtr = donorPtr + start;
    double *greenPtr = receiverPtr + start;
    double *redPtr = donorPtr + secondStartIndex;
    double *greyPtr = redPtr;
    double *bluePtr = donorPtr + end; //length is necessary to get the end of the first array

    //first comparison loop in ascending order
    while (blackPtr < redPtr && greyPtr < bluePtr) {
        cout << *blackPtr << ", " << *greyPtr << endl;
        if (*blackPtr < *greyPtr) {
            *greenPtr = *blackPtr;
            blackPtr++;
        } else {
            *greenPtr = *greyPtr;
            greyPtr++;
        }
        greenPtr++;
    }

    //second loop for adding in non empty sub array items
    while (blackPtr < redPtr || greyPtr < bluePtr) {
        if (blackPtr < redPtr) {
            *greenPtr = *blackPtr;
            greenPtr++;
            blackPtr++;
        }
        if (greyPtr < bluePtr) {
            *greenPtr = *greyPtr;
            greenPtr++;
            greyPtr++;
        }
    }
}

//recursively splits and merges array
void SortableArray::split(double *prePtr, double *postPtr, unsigned int startIndex, unsigned int endIndex) {

    cout << startIndex << ", " << endIndex << endl;

    if (endIndex - startIndex == 1) {
        return;
    } else {
        int midIndex = (startIndex + endIndex) / 2;

        split(postPtr, prePtr, startIndex, midIndex);
        split(postPtr, prePtr, midIndex, endIndex);

        merge(prePtr, postPtr, midIndex, startIndex, endIndex);
    }
}

//default constructor
SortableArray::SortableArray() {
    len = 10;
    arr = new double[10];
    zeros();
}

//constructor with size
SortableArray::SortableArray(unsigned int n) {
    len = n;
    arr = new double[n];
    zeros();
}

//returns pointer for array's first element
double* SortableArray::getPointer() {
    return arr;
}

//returns length of array
int SortableArray::getLength() {
    return len;
}

//initialize array to be all zeros
void SortableArray::zeros() {
    for (int i = 0; i < len; i++) {
        *(arr + i) = 0;
    }
}

//generate random double for each value in array between max and min
void SortableArray::random(double min, double max) {
    srand(static_cast<long int>(time(NULL)));
    for (int i = 0; i < len; i++) {
        double r = 2 * (static_cast<double>(rand()) / RAND_MAX) - 1;
        *(arr + i) = r * max;
    }
}

//writes out array to a file
void SortableArray::write(ofstream &f, bool sorted) {
    f << (sorted ? "Sorted Array:" : "Unsorted Array:") << endl;
    for (int i = 0; i < len; i++) {
        f << *(arr + i) << endl;
    }
}

//full implementation of merge sort
void SortableArray::mergeSort() {
    double *callingPtr = getPointer();
    SortableArray workingArr(getLength());
    double *workingArrPtr = workingArr.getPointer();

    for (int i = 0; i < getLength(); i++) {
        *(workingArrPtr + i) = *(callingPtr + i);
    }

    split(workingArrPtr, callingPtr, 0, getLength());
}
