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
   Files: STLStack.cpp
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

 The purpose of this program is to record the test times of the push(k), pop(), and search() functions of a stack whose 
 entries are copied from a randomly generated vector.
 */

#include <iostream>
#include <stack>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>

#include "Complexity_Timer.hpp"
#include "STLStack.hpp"

const int operations = 3;

std::stack<int, std::vector<int>> generateSTL_Stack(int size) 
{

    std::vector<int> values;

    for (int i = 0; i < size; ++i)
    {
        values.push_back(i); 
    }

    std::random_shuffle(values.begin(), values.end());
    std::stack<int, std::vector<int>> s(values);  
    return s;
}

int search(int element, std::stack<int, std::vector<int>> s)
{
    std::stack<int> temp; 
    int i = 0; 
    int ogsize = s.size(); 

    for( ; i <= ogsize; ++i){
        if( i == ogsize){   //indicates that the stack is empty "Underflow"
            i = -1; 
            break;
        }

        if(s.top() == element){
            break;
        }

        temp.push(s.top()); 
        s.pop(); 
    }

    int ogtemp = temp.size(); 

    for(int j = 0; j < ogtemp; ++j){
        s.push(temp.top());
        temp.pop(); 
    }

    return i; 
}

const char* headings2[operations] = 
{
    "| Push           ", 
    "| Pop            ", 
    "| Search    "
};

void runnerSTL()
{
    timer time;

    // How many times to perform each task to get the average
    const int repetitions = 7;

    // How many times to repeat the operation per task
    // (adding constant to our big-oh runtime)
    const int factor = 10000;

    std::cout << "STL Stack: \n"; 
    std::cout << "____";
    for (int i = 0; i < operations; ++i)
      std::cout << headings2[i];
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
                auto s = generateSTL_Stack(size);

                time.restart();
                s.push(5);
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
                auto s = generateSTL_Stack(size);

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
                auto s = generateSTL_Stack(size);

                time.restart();
                search(4, s); 
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