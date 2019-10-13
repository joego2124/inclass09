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
        void merge(double *donorPtr, double *receiverPtr, unsigned int secondStartIndex, unsigned int start, unsigned int end) {

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
        void split(double *prePtr, double *postPtr, unsigned int startIndex, unsigned int endIndex) {

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

    public:
        //default constructor
        SortableArray() {
            len = 10;
            arr = new double[10];
            zeros();
        }

        //constructor with size
        SortableArray(unsigned int n) {
            len = n;
            arr = new double[n];
            zeros();
        }

        //returns pointer for array's first element
        double *getPointer() {
            return arr;
        }

        //returns length of array
        int getLength() {
            return len;
        }

        //initialize array to be all zeros
        void zeros() {
            for (int i = 0; i < len; i++) {
                *(arr + i) = 0;
            }
        }

        //generate random double for each value in array between max and min
        void random(double min, double max) {
            srand(static_cast<long int>(time(NULL)));
            for (int i = 0; i < len; i++) {
                double r = 2 * (static_cast<double>(rand()) / RAND_MAX) - 1;
                *(arr + i) = r * max;
            }
        }

        //writes out array to a file
        void write(ofstream &f, bool sorted) {
            f << (sorted ? "Sorted Array:" : "Unsorted Array:") << endl;
            for (int i = 0; i < len; i++) {
                f << *(arr + i) << endl;
            }
        }

        //full implementation of merge sort
        void mergeSort() {
            double *callingPtr = getPointer();
            SortableArray workingArr(getLength());
            double *workingArrPtr = workingArr.getPointer();

            for (int i = 0; i < getLength(); i++) {
                *(workingArrPtr + i) = *(callingPtr + i);
            }

            split(workingArrPtr, callingPtr, 0, getLength());
        }
};

SortableArray readArray(ifstream&);

int main() {

    SortableArray arr(256); //create first array
    arr.random(-1, 1);

    //create output file
    ofstream outFile;
    outFile.open("ece0301_merge_sort_results.txt");

    //write out first header
    outFile << "ECE 0301 - Sorting Arrays" << endl;
    arr.write(outFile, false);

    //call merge with proper parameters
    arr.mergeSort();
    arr.write(outFile, true);

    //close files
    outFile.close();

    return 0;
}


//read array data from a file and returns as a SortableArray Object
SortableArray readArray(ifstream &f) {

    string temp;
    unsigned int n;
    getline(f, temp);

    //error checking for file header
    if (temp.substr(0, 9).compare("LENGTH = ") != 0) {
        cout << "ERROR! Invalid input file header." << endl;
        exit(EXIT_FAILURE);
    }

    //get length of array and loop through file for data
    n = (unsigned int) stoi(temp.substr(9, temp.length() - 9));
    SortableArray arr(n);
    arr.zeros();
    for (int i = 0; i < n; i++) {
        double num;
        f >> num;
        *(arr.getPointer() + i) = num;
    }

    return arr;
}
