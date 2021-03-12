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
   Files: MyStack.cpp
          Complexity_Timer.hpp

   COPYRIGHT (C) 2018 Will Crissey, Jr. All rights reserved.
   DS316 Sample Project example.
   Author.  Will Crissey, Jr.
   Version. 1.02 06.03.2018.
   Files: DS316_Project_Standard_Code_Example.cpp
          Complexity_Timer.hpp
          Complexity_Recorder.hpp


This program uses some of the supplied code in the DS316_Project_Standard_Code_Example to create the clock to record the
test times for each stack as the push(), pop(), and search() functions are implemented
 
 The purpose of this program is to record the run times of the push(k), pop(), and search(n) functions of a linked list
 stack without the use of the STL. 

 */

#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>

#include "Complexity_Timer.hpp"
#include "MyStack.hpp"

const int operations = 3;

//Simple stack using a Linked List.
MyStack::MyStack(const int array[], int size) {
    Node* prevNode = nullptr; 
    for(int i = 0; i < size; ++i){
        Node* node = new Node(); 
        node -> element = array[i]; 
        node -> next = nullptr; 

        if(i == 0){
            top = node; 
        }

        if(prevNode != nullptr){
            prevNode -> next = node; 
        }

        prevNode = node;
    }
}

MyStack::MyStack()
{
    top = nullptr; 
}

void MyStack::push(int element)
{
    struct Node* temp = new Node(); 

    if(!temp){
        std::cout << "The stack is full. \n"; 
    }

    temp -> element = element; 
    temp->next = top; 
    top = temp; 
}

void MyStack::pop()
{
    struct Node* temp; 
    if(top == nullptr){
        std::cout << "The stack is empty \n"; 
    }

    temp = top; 
    top = top -> next; 
    temp -> next = nullptr; 
    delete(temp);
}

int MyStack::search(int element)
{
    struct Node* temp = top; 
    int pos = 0; 

    while(temp != nullptr){
        pos = pos + 1; 
        if(temp -> element == element){
            return pos; 
        }
        else
        {
            temp = temp -> next; 
        }
    }

    return -1;
}

MyStack generateMyStack(int size)
{
    std::vector<int> values;
    for (int i = 0; i < size; ++i)
    {
        values.push_back(i);
    }

    std::random_shuffle(values.begin(), values.end());
    int *array = new int [values.size()];
    std::copy(values.begin(), values.end(), array); 

    return MyStack(array, values.size());
}

const char* headings[operations] = 
{
    "| Push           ", 
    "| Pop            ", 
    "| Search    "
};

void runner()
{
    timer time;

    // How many times to perform each task to get the average
    const int repetitions = 7;

    // How many times to repeat the operation per task
    // (adding constant to our big-oh runtime)
    const int factor = 10000;

    std::cout << "My Stack: \n"; 
    std::cout << "____";
    for (int i = 0; i < operations; ++i)
      std::cout << headings[i];
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
                auto s = generateMyStack(size);

                time.restart();
                s.push(0);
                time.stop();

                totalPushTime += time.time();
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
                auto s = generateMyStack(size);

                time.restart();
                s.pop();
                time.stop();

                totalPopTime += time.time();
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
                auto s = generateMyStack(size);

                time.restart();
                s.search(0);
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
