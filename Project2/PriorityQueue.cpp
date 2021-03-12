#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <queue>

#include "Complexity_Timer.hpp"
#include "PriorityQueue.hpp"

const int operations = 4;

const char* priorityQueueHeadings[operations] = 
{
    "|     Insert     ", 
    "|     Delete     ", 
    "|  Max Search    ",
    "|  Min Search    "
};

std::priority_queue<int> generatePQueue(int size)
{
    std::vector<int> values;
    for (int i = 0; i < size; ++i)
    {
        values.push_back(i);
    }

    std::random_shuffle(values.begin(), values.end());
    
    return std::priority_queue<int>(values.begin(), values.end()); 
}

int searchMinSTL(std::priority_queue<int> pq)
{
    int lastValue; 

    while(!pq.empty()){
        lastValue = pq.top(); 
        pq.pop(); 
    }

    return lastValue; 
}

void runPriorityQueue()
{
    timer time;

    // How many times to perform each task to get the average
    const int repetitions = 7;

    // How many times to repeat the operation per task
    // (adding constant to our big-oh runtime)
    const int factor = 5000;

    std::cout << "My Priority Queue: \n"; 
    std::cout << "____";
    for (int i = 0; i < operations; ++i)
      std::cout << priorityQueueHeadings[i];
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
                auto h = generatePQueue(size);

                time.restart();
                h.push(10); 
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
                auto h = generatePQueue(size);

                time.restart();
                h.pop();
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
                auto h = generatePQueue(size); 

                time.restart();
                h.top();
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
                auto h = generatePQueue(size);

                time.restart();
                searchMinSTL(h);
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