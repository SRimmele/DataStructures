#ifndef ARRAY_HEAP_HPP
#define ARRAY_HEAP_HPP

#include <string>

class MaxHeap
{
    private: 
    int* array; 
    int maxSize;
    int currentSize; 
    bool isLeafNode(int pos) const; 
    int leftChild(int pos) const; 
    int rightChild(int pos) const; 
    int parent(int pos) const;  

    public: 
    MaxHeap(int maxSize_); //default
    MaxHeap(int* arr, int length, int maxSize_); 
    void heapify();
    void heapify(int array[], int pos); 
    void insert(int value);
    void removeRoot(); 
    int searchMax();     
    int searchMin();    
    int searchMin(int pos); 
}; 

MaxHeap generateMyHeap(int size, int maxSize_); 
void swap(int *x, int *y);

void runArrayHeap();

#endif 