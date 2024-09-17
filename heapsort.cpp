// simple C++ program to read in an array of longs, sort
// the array using heapsort, and then write the sorted data
// to a file
// By Mary Elaine Califf and Dane Iwema

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// read the file into the vector (starting at index 1)
void readFile(vector<long>& arr, char* fileName);

// write the vector to the file (starting at index 1)
void writeFile(const vector<long>& arr, char* fileName);

// sort the vector using heapsort (data starts at index 1)
void heapsort(vector<long>& arr);

// add any function prototypes for any additional functions here

void heapify(vector<long>& arr, int n, int i);

// do not modify the main function -- you must complete the empty methods below
int main(int argc, char** argv) {

  if (argc < 3) {
    cout << "Usage: " << argv[0] << " infile outfile\n";
    exit(1);
  }
  char* inFileName = argv[1];
  char* outFileName = argv[2];
  vector<long> theArray;
  
  readFile(theArray, inFileName);

  heapsort(theArray);
  
  writeFile(theArray, outFileName);

  return 0;
}

void readFile(vector<long>& arr, char* fileName)
{
  ifstream infile(fileName);
  if (infile.fail()) {
    cerr << "Could not open " << fileName << " for input" << endl;
    exit(1);
  }

  long num;
  while (infile >> num) {
    arr.push_back(num);
  }
  infile.close();
}

void writeFile(const vector<long>& arr, char* fileName)
{
  ofstream outfile(fileName);
  for (long num : arr) {
    outfile << num << endl;
  }
  outfile.close();
}

void heapsort(vector<long>& arr)
{
  for (int i = arr.size() / 2 - 1; i >= 0; i--)
    heapify(arr, arr.size(), i);
  for (int i = arr.size() - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    heapify(arr, i, 0);
  }
}

// implementation code for any additional functions here
  
void heapify(vector<long>& arr, int n, int i) {
  int largest = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;

  if (l < n && arr[l] > arr[largest])
    largest = l;

  if (r < n && arr[r] > arr[largest])
    largest = r;

  if (largest != i) {
    swap(arr[i], arr[largest]);

    heapify(arr, n, largest);
  }
}