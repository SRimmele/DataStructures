/*
   ACADEMIC INTEGRITY PLEDGE

   - I have not used source code obtained from another
     student nor any other unauthorized source, either
     modified or unmodified. Any source code used for
     testing that is another student's has been
     appropriately documented

   - All source code and documentation used in my program
     is either my original work or was derived by me from
     the source code published in the textbook for this
     course or presented in class. Other sources are acknowledged
     without transcribing code verbatim

   - I have not discussed coding details about this project
     with anyone other than my instructor, TA, and my immediate
     project team. I understand that I may discuss the concepts
     of this program with other students and that another student
     may help me debug my program so long as neither of us writes
     anything during the discussion or modifies any computer file
     during the discussion.

   - I have violated neither the spirit nor letter of these
     restrictions.

   Signed: Savannah Rimmele Date: 03/014/2021


   COPYRIGHT (C) 2021 student name. All Rights Reserved.
   Project #: 2
   author Savannah Rimmele, smr165
   version 1.01 2021-03-011
   Files: ArrayHeap.cpp
          ArrayHeap.hpp
          Complexity_Timer.hpp

   COPYRIGHT (C) 2018 Will Crissey, Jr. All rights reserved.
   DS316 Sample Project example.
   Author.  Will Crissey, Jr.
   Version. 1.02 06.03.2018.
   Files: DS316_Project_Standard_Code_Example.cpp
          Complexity_Timer.hpp
          Complexity_Recorder.hpp


This program uses some of the supplied code in the DS316_Project_Standard_Code_Example to create the clock to record the
test times for each implementation as the inset, remove, and search functions are implemented. 
 
 The purpose of this program is to record the run times of the insert(k), removeRoot(), searchMax(), and searchMin() functions of a
 maximum binary heap without the use of the STL. 
 */


#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>

#include "Complexity_Timer.hpp"
#include "ArrayHeap.hpp"

const int operations = 4;

const char* arrayHeapHeadings[operations] = 
{
    "|     Insert     ", 
    "|     Delete     ", 
    "|  Max Search    ",
    "|  Min Search    "
};

bool MaxHeap::isLeafNode(int pos) const
{
//    return (pos >= currentSize/2) && (pos < currentSize);
    return leftChild(pos) >= currentSize && rightChild(pos) >= currentSize;
}

int MaxHeap::leftChild(int pos) const
{
    return (2 * pos + 1); 
}

int MaxHeap::rightChild(int pos) const
{
    return (2 * pos + 2);
}

int MaxHeap::parent(int pos) const
{
    return (pos - 1)/2; 
}

MaxHeap::MaxHeap(int maxSize_)
{
    currentSize = 0; 
    maxSize = maxSize_; 
    array = new int[maxSize]; 
}

MaxHeap::MaxHeap(int* arr, int length, int maxSize_)
{
    currentSize = length; 
    maxSize = maxSize_; 
    array = new int[maxSize]; 

    for(int i = 0; i < length; ++i){
        array[i] = arr[i]; 
    }

    heapify(); 
}

void MaxHeap::heapify()
{
    for(int current = parent(currentSize - 1); current >= 0; --current) {
        heapify(array, current);
    }
}

//Move the value at the position in an array 
//into the correct position. 
void MaxHeap::heapify(int array[], int pos)
{
    if(isLeafNode(pos)){    //If a leaf node then break
        return;
    } 
        
    int left = leftChild(pos); 
    int right = rightChild(pos);

    if (left < currentSize && (array[left] > array[pos])){
        swap(&array[pos], &array[left]);    //swap the current node with the left node
    }

    if (right < currentSize && (array[right] > array[pos])){
        swap(&array[pos], &array[right]);   //swap the current node with the right node
    }

    if(left < currentSize){
        heapify(array, left);
    }

    if(right < currentSize){
        heapify(array, right); 
    }
}

void MaxHeap::insert(int value)
{ 
    if(currentSize >= maxSize){
        std::cout << "The Heap is Full! \n";
        return;  
    }
    
    currentSize++; 
    array[currentSize - 1] = value; 
    int pos = currentSize - 1; 

    while(pos != 0 && array[pos] > array[parent(pos)]){
        swap(&array[pos], &array[parent(pos)]); 
        pos = parent(pos); 
    }
}

void MaxHeap::removeRoot()
{
    if(currentSize == 0){
        std::cout << "The Heap is Empty! \n"; 
        return; //Heap is empty
    }

    int rootIndex = 0; 

    swap(&array[currentSize - 1], &array[rootIndex]); 
    currentSize -=1;

    heapify();  
}

int MaxHeap::searchMax()
{
    return array[0]; 
}

int MaxHeap::searchMin() {
    return searchMin(0);
}

int MaxHeap::searchMin(int pos)
{
    if(isLeafNode(pos)){
        return array[pos]; 
    }

    if(rightChild(pos) >= currentSize) {
        return searchMin(leftChild(pos));
    }
    
    int leftMin = searchMin(leftChild(pos));
    int rightMin = searchMin(rightChild(pos));

    if(leftMin < rightMin) {
        return leftMin;
    }

    return rightMin;
}

MaxHeap generateMyHeap(int size, int maxSize_)
{
    std::vector<int> values;
    for (int i = 0; i < size; ++i)
    {
        values.push_back(i);
    }

    std::random_shuffle(values.begin(), values.end());
    int *array = new int [maxSize_];
    std::copy(values.begin(), values.end(), array);  
    
    return MaxHeap(array, values.size(), maxSize_);
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void runArrayHeap()
{
    timer time;

    // How many times to perform each task to get the average
    const int repetitions = 7;

    // How many times to repeat the operation per task
    // (adding constant to our big-oh runtime)
    const int factor = 5000;

    std::cout << "My Max Binary Heap: \n"; 
    std::cout << "____";
    for (int i = 0; i < operations; ++i)
      std::cout << arrayHeapHeadings[i];
    std::cout << std::endl;

    std::cout << "Size";
    for (int i = 0; i < operations; ++i)
      std::cout << "|      Time      ";
    std::cout << std::endl;

    // Insert into stack size 1
    for(int size = 1; size < 1000; size *= 2){
        double totalInsertTime = 0;
        double totalRemoveTime = 0;
        double totalSearchMaxTime = 0;
        double totalSearchMinTime = 0;

        // Run multiple repetitions because the execution time
        // can vary between runs
        for (int i = 0; i < repetitions; ++i)
        {
            // Repeat the same operation multiple times because the
            // computer is too fast
            for (int j = 0; j < factor; ++j)
            {
                auto h = generateMyHeap(size, std::max(size * 2, 16));

                time.restart();
                h.insert(10); 
                time.stop();

                totalInsertTime += time.time();
            }
        }

        // Run multiple repetitions because the execution time
        // can vary between runs
        for (int i = 0; i < repetitions; ++i)
        {
            // Repeat the same operation multiple times because the
            // computer is too fast
            for (int j = 0; j < factor; ++j)
            {
                auto h = generateMyHeap(size, size * 2);

                time.restart();
                h.removeRoot();
                time.stop();

                totalRemoveTime += time.time();
            }
        }

        // Run multiple repetitions because the execution time
        // can vary between runs
        for (int i = 0; i < repetitions; ++i)
        {
            // Repeat the same operation multiple times because the
            // computer is too fast
            for (int j = 0; j < factor; ++j)
            {
                auto h = generateMyHeap(size, size * 2);

                time.restart();
                h.searchMax();
                time.stop();

                totalSearchMaxTime += time.time();
            }
        }

        
        // Run multiple repetitions because the execution time
        // can vary between runs
        for (int i = 0; i < repetitions; ++i)
        {
            // Repeat the same operation multiple times because the
            // computer is too fast
            for (int j = 0; j < factor; ++j)
            {
                auto h = generateMyHeap(size, size * 2);

                time.restart();
                h.searchMin();
                time.stop();

                totalSearchMinTime += time.time();
            }
        }

        // Use the average runtime as our output
         double averageInsertTime = (double)totalInsertTime / repetitions;
         double averageRemoveTime = (double)totalRemoveTime / repetitions;
         double averageSearchMaxTime = (double)totalSearchMaxTime / repetitions;
         double averageSearchMinTime = (double)totalSearchMinTime / repetitions;
         std::cout << std::fixed
             << std::setw(4) << size << "|" << std::setprecision(10)
             << std::setw(16) << averageInsertTime << "|"
             << std::setw(16) << averageRemoveTime << "|"
             << std::setw(16) << averageSearchMaxTime << "|" 
             << std::setw(16) << averageSearchMinTime << "|"
             << std::endl;
     }
}