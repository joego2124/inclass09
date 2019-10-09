#include <iostream>
#include <fstream>

using namespace std;

class SortableArray {
    private:
        double *arr;
        int len;
    public:
        SortableArray() {
            len = 10;
            arr = new double[10];
            zeros();
        }

        SortableArray(unsigned int n) {
            len = n;
            arr = new double[n];
            zeros();
        }

        double *getPointer() {
            return arr;
        }

        int getLength() {
            return len;
        }

        void zeros() {
            for (int i = 0; i < len; i++) {
                *(arr + i) = 0;
            }
        }

        void write(ofstream &f) {
            f << "ECE 0301 - Sorting Arrays" << endl;
            f << "Unsorted Array:" << endl;
            for (int i = 0; i < len; i++) {
                f << *(arr + i) << endl;
            }
        }
};

int main() {

    SortableArray arr = new SortableArray();

    ofstream outFile;
    outFile.open("ece_0301_unsorted_array.txt");

    arr.write(outFile);

    return 0;
}
