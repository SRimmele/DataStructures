/**
 * # Test cases
 * Measure time for insert using Linear Probing
 * Measure time for delete using Linear Probing
 * Measure time for find using Linear Probing
 * 
 * # Comparison
 * Test cases should be completed for:
 * 1. Own Linear Probing
 * 2. Experimenter (1, 10, 19, 28) Hopscotch Hashing
 * 3. Experimenter 1, 10, 19, 28) Hopscotch Hashing
 * 
 * # Notes
 * - Do not have to use sample code
 */


#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>

#include "Complexity_Timer.hpp"
#include "LinearProbe.hpp"

const int operations = 3;

const char* headings[operations] = 
{
    "| Insert           ", 
    "| Delete           ", 
    "| Search    "
};

HashTable::HashTable()
{
    for(int i = 0; i < size; i++)
}

//  generate(int size, int maxSize_)
// {
//     std::vector<int> values;
//     for (int i = 0; i < size; ++i)
//     {
//         values.push_back(i);
//     }

//     std::random_shuffle(values.begin(), values.end());
//     int *array = new int [maxSize_];
//     std::copy(values.begin(), values.end(), array);  
    
//     return MaxHeap(array, values.size(), maxSize_);
// }

int main()
{
    timer time;

    // How many times to perform each task to get the average
    const int repetitions = 7;

    // How many times to repeat the operation per task
    // (adding constant to our big-oh runtime)
    const int factor = 10000;

    std::cout << "My Max Binary Heap: \n"; 
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
                 //auto s = generateMyHeap(size);

                // time.restart();
                // s.push(0);
                // time.stop();

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
                // auto s = generateMyStack(size);

                // time.restart();
                // s.pop();
                // time.stop();

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
                // auto s = generateMyStack(size);

                // time.restart();
                // s.search(0);
                // time.stop();

                totalSearchTime += time.time();
            }
        }

        // Use the average runtime as our output
        // double averagePushTime = (double)totalPushTime / repetitions;
        // double averagePopTime = (double)totalPopTime / repetitions;
        // double averageSearchTime = (double)totalSearchTime / repetitions;
    //     std::cout << std::fixed
    //         << std::setw(4) << size << "|" << std::setprecision(10)
    //         << std::setw(16) << averagePushTime << "|"
    //         << std::setw(16) << averagePopTime << "|"
    //         << std::setw(16) << averageSearchTime << "|"
    //         << std::endl;
     }
    
}