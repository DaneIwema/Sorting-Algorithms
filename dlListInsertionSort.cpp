// simple C++ program to build a doubly linked list from a file of longs,
// sort the list using insertion sort, and then write the sorted data
// to a file
// By Mary Elaine Califf and Dane Iwema

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

//The Node struct is set up so you physically cannot change the data value after creating the object.
//Do not change this. You must only modify the pointer values when moving nodes.
struct Node
{
    private:
        long dataVal;
    public:
        Node* next;
        Node* prev;

        Node(long data = 0, Node* nextPtr = nullptr, Node* prevPtr = nullptr)
            : dataVal(data), next(nextPtr), prev(prevPtr) {}
        
        //Getter for public access of the dataVal
        long getDataVal() const { return dataVal; }
};

// read the file into the linked list
void readFile(Node*& head, char* fileName);

// write the linked list to the file
void writeFile(Node* head, char* fileName);

// sort the linked list using an insertion sort following the standard algorithm
// for an array adapted to a doubly linked list
void insertionSort(Node*& head);

// add any function prototypes for any additional functions here

void insert(Node*& head, long val);

// do not modify the main function -- you must complete the empty methods below
int main(int argc, char** argv) {

    if (argc < 3) {
        cout << "Usage: " << argv[0] << " infile outfile\n";
        exit(1);
    }
    char* inFileName = argv[1];
    char* outFileName = argv[2];
    Node* head = nullptr;

    readFile(head, inFileName);

    insertionSort(head);

    writeFile(head, outFileName);

    // clear out the list memory
    Node* temp = head;
    while (head)
    {
        head = head->next;
        delete temp;
        temp = head;
    }

    return 0;
}

void readFile(Node*& head, char* fileName)
{
    ifstream infile(fileName);
    if (infile.fail()) {
        cerr << "Could not open " << fileName << " for input" << endl;
        exit(1);
    }

    long num;
    while (infile >> num) {
        insert(head, num);
    }
    infile.close();
}

void writeFile(Node* head, char* fileName)
{
    ofstream outfile(fileName);
    Node* current = head;
    while (current) {
        outfile << current->getDataVal() << endl;
        current = current->next;
    }
    outfile.close();
}

void insertionSort(Node*& head)
{
    Node* current = head->next;
    while (current) {
        Node* keyNode = current;
        Node* prevNode = keyNode->prev;

        while (keyNode->prev && keyNode->prev->getDataVal() > keyNode->getDataVal()) {
            prevNode->next = keyNode->next;
            if (keyNode->next)
                keyNode->next->prev = prevNode;
            keyNode->prev = prevNode->prev;
            if (prevNode->prev)
                prevNode->prev->next = keyNode;
            else
                head = keyNode;
            keyNode->next = prevNode;
            prevNode->prev = keyNode;
            prevNode = keyNode->prev;
        }

        current = current->next;
    }
}

// implementation code for any additional functions here

void insert(Node*& head, long val) {
    Node* newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
    } else {
        head->prev = newNode;
        newNode->next = head;
        head = newNode;
    }
}