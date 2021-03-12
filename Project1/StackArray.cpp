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

   Signed: student name Date: 02/07/2021


   COPYRIGHT (C) 2021 student name. All Rights Reserved.
   Project #: 1
   author student name, uanetid
   version 1.01 2021-02-05
   Files: StackArray.cpp
          Complexity_Timer.hpp

   COPYRIGHT (C) 2018 Will Crissey, Jr. All rights reserved.
   DS316 Sample Project example.
   Author.  Will Crissey, Jr.
   Version. 1.02 06.03.2018.
   Files: DS316_Project_Standard_Code_Example.cpp
          Complexity_Timer.hpp
          Complexity_Recorder.hpp


This program uses some of the supplied code in the DS316_Project_Standard_Code_Example to create the clock to record the
test times for each stack as the push(), pop(), and search() functions are implemented. 

This dynamic array-based stack has operations from https://dev.to/yuvraajsj18/stack-implemented-with-arrays-kja, where code
was supplied to start the implementation of the stack, while a search function was created to traverse this type of stack.
 
 The purpose of this program is to record the test times of the push(k), pop(), and search() functions of a randomly
 generated array-based stack. 
  */

#include <iostream>
#include <stack>
#include <array>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>

#include "Complexity_Timer.hpp"
#include "StackArray.hpp"

#define STACK_BUFFER 1024

const int operations = 3;

//constructor
template<typename T, int size> 
StackArray<T, size>::StackArray()
{
    stack = new T[size]; 
    top = -1; 
}

template<typename T, int size>
StackArray<T,size>::StackArray(T* array, int length)
{
    stack = new T[size];
    top = -1; 

    for(int i = 0; i < length; ++i){
        push(array[i]);
    }
}

//destructor
template<typename T, int size> 
StackArray<T, size>::~StackArray()
{
    delete[] stack;
}

template<typename T, int size> 
bool StackArray<T, size>::isEmpty()
{
    return top == -1; 
}

template<typename T, int size> 
void StackArray<T, size>::push(T element)
{
    if(top == size -1){
        std::cout << "The Stack is Full!"; 
    }

    //insert onto the next position
    stack[++top] = element; 
}

template<typename T, int size> 
void StackArray<T, size>::pop()
{
    if(isEmpty()){
        std::cout<<"The stack is empty \n"; 
    }
    T elementPopped = stack[top--]; 
}

template<typename T, int size>
int StackArray<T,size>::search(T element)
{
    for(int i = 0; i < top + 1; ++i){
        if(stack[i] == element){
            return i; 
        }
    }
    return -1; 
}

StackArray<int, STACK_BUFFER> generateStack(int size)
{

    std::vector<int> values;

    for (int i = 0; i < size; ++i)
    {
        values.push_back(i); 
    }

    std::random_shuffle(values.begin(), values.end());
    StackArray<int, STACK_BUFFER> s(values.data(), values.size());

    return s;
}

const char* headings1[operations] = 
{
    "| Push           ", 
    "| Pop            ", 
    "| Search    "
};

void runnerArray()
{
    timer time;

    // How many times to perform each task to get the average
    const int repetitions = 7;

    // How many times to repeat the operation per task
    // (adding constant to our big-oh runtime)
    const int factor = 10000;

    std::cout << "Array Based Stack: \n"; 
    std::cout << "____";
    for (int i = 0; i < operations; ++i)
      std::cout << headings1[i];
    std::cout << std::endl;

    std::cout << "Size";
    for (int i = 0; i < operations; ++i)
      std::cout << "|      Time      ";
    std::cout << std::endl;

    // Insert into stack size 1
    for(int size = 1; size < 1000; size *= 2){
        double totalPushTime = 0;
        double totalPopTime = 0;
        double totalSearchTime = 0;

        // Run multiple repetitions because the execution time
        // can vary between runs
        for (int i = 0; i < repetitions; ++i)
        {
            // Repeat the same operation multiple times because the
            // computer is too fast
            for (int j = 0; j < factor; ++j)
            {
                auto s = generateStack(size);

                time.restart();
                s.push(5); 
                //s.pop();
                //auto result = s.search(4); 
                time.stop();

                totalPushTime += time.time();
            }
        }

                for (int i = 0; i < repetitions; ++i)
        {
            // Repeat the same operation multiple times because the
            // computer is too fast
            for (int j = 0; j < factor; ++j)
            {
                auto s = generateStack(size);

                time.restart();
                s.pop(); 
                time.stop();

                totalPopTime += time.time();
            }
        }

        for (int i = 0; i < repetitions; ++i)
        {
            // Repeat the same operation multiple times because the
            // computer is too fast
            for (int j = 0; j < factor; ++j)
            {
                auto s = generateStack(size);

                time.restart();
                auto result = s.search(4); 
                time.stop();

                totalSearchTime += time.time();
            }
        }

        // Use the average runtime as our output
        double averagePushTime = (double)totalPushTime / repetitions;
        double averagePopTime = (double)totalPopTime / repetitions;
        double averageSearchTime = (double)totalSearchTime / repetitions;
        std::cout << std::fixed
            << std::setw(4) << size << "|" << std::setprecision(10)
            << std::setw(16) << averagePushTime << "|"
            << std::setw(16) << averagePopTime << "|"
            << std::setw(16) << averageSearchTime << "|"
            << std::endl;
    }
}