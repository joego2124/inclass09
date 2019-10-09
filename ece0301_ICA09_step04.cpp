#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//declare SortableArray class
class SortableArray {
    private:
        double *arr;
        int len;
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

        //writes out array to a file
        void write(ofstream &f, bool sorted) {
            f << (sorted ? "Sorted Array:" : "Unsorted Array:") << endl;
            for (int i = 0; i < len; i++) {
                f << *(arr + i) << endl;
            }
        }

        //merge two sub arrays from one array to another
        void merge(double *donorPtr, double *receiverPtr, unsigned int secondStartIndex, unsigned int length) {
            //ini pointers
            double *blackPtr = donorPtr;
            double *greenPtr = receiverPtr;
            double *redPtr = blackPtr + secondStartIndex;
            double *greyPtr = redPtr;
            double *bluePtr = donorPtr + length; //length is necessary to get the end of the first array

            //first comparison loop in ascending order
            while (blackPtr < redPtr && greyPtr < bluePtr) {
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
};

SortableArray readArray(ifstream&);

int main() {

    SortableArray arr; //create first array

    //create input and output files
    ofstream outFile;
    outFile.open("ece0301_merge_sort_results.txt");

    ifstream inFile;
    inFile.open("ece_0301_unsorted_array.txt");

    //write out first header
    outFile << "ECE 0301 - Sorting Arrays" << endl;

    //read subarray data to first array
    arr = readArray(inFile);
    arr.write(outFile, false);

    //ini second array that gets copied to
    SortableArray arr2(arr.getLength());
    arr2.zeros();

    //call merge with proper parameters
    arr.merge(arr.getPointer(), arr2.getPointer(), arr.getLength() / 2, arr.getLength());

    //write out merged array to file
    arr2.write(outFile, true);

    //close files
    outFile.close();
    inFile.close();

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
