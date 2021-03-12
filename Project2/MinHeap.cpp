#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>

#include "Complexity_Timer.hpp"
#include "MinHeap.hpp"

const int operations = 4;

const char* minHeapHeadings[operations] = 
{
    "|     Insert     ", 
    "|     Delete     ", 
    "|  Max Search    ",
    "|  Min Search    "
};

MinHeap<int> generateMinHeap(int size, int _maxSize)
{
    std::vector<int> values;
    for (int i = 0; i < size; ++i)
    {
        values.push_back(i);
    }

    std::random_shuffle(values.begin(), values.end());
    int *array = new int [_maxSize];
    std::copy(values.begin(), values.end(), array);  
    
    return MinHeap<int>(array, values.size(), _maxSize);
}

void runMinHeap()
{
    timer time;

    // How many times to perform each task to get the average
    const int repetitions = 7;

    // How many times to repeat the operation per task
    // (adding constant to our big-oh runtime)
    const int factor = 5000;

    std::cout << "Dimitry's Min Heap: \n"; 
    std::cout << "____";
    for (int i = 0; i < operations; ++i)
      std::cout << minHeapHeadings[i];
    std::cout << std::endl;

    std::cout << "Size";
    for (int i = 0; i < operations; ++i)
      std::cout << "|      Time      ";
    std::cout << std::endl;

    // Insert into stack size 1
    //Can't time with heap size of 1 because Min Heap Seg Faults at size of 0. 
    for(int size = 2; size < 1000; size *= 2){
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
                auto h = generateMinHeap(size, std::max(size * 2, 16));

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
                auto h = generateMinHeap(size, size * 2);

                time.restart();
                h.remove(h.getMinIndex());
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
                auto h = generateMinHeap(size, size * 2);

                time.restart();
                h.getMaxIndex();
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
                auto h = generateMinHeap(size, size * 2);

                time.restart();
                h.getMinIndex();
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