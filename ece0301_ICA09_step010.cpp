#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdlib>
#include <ctime>

#include "SortableArray.cpp"


using namespace std;



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
