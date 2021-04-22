#include <iostream> 
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <string> 

#include "Complexity_Timer.hpp"
#include "HopscotchHashTable.hpp"

const int operations = 3;

const char* Hop_headings[operations] = 
{
    "| Insert         ", 
    "| Delete         ", 
    "| Search    "
};

HopscotchHashTable generateHopHashMap(int size) {
  HopscotchHashTable hashMap; 

    srand(time(NULL)); 

    // Run every time for each key
    for(int i = 0; i < size; ++i) {
        int randNum = rand() % 1000000; 

        hashMap.addValue(randNum);
    }
    
    return hashMap; 
}

void runHopscotch()
{
    timer time;

    // How many times to perform each task to get the average
    const int repetitions = 7;

    // How many times to repeat the operation per task
    // (adding constant to our big-oh runtime)
    const int factor = 5000;

    std::cout << "Hopscotch Hash Table: \n"; 
    std::cout << "____";
    for (int i = 0; i < operations; ++i)
      std::cout << Hop_headings[i];
    std::cout << std::endl;

    std::cout << "Size";
    for (int i = 0; i < operations; ++i)
      std::cout << "|      Time      ";
    std::cout << std::endl;

    // Insert into hash table of size 1
    for(int size = 1; size < 1000; size *= 2){
        double totalInsertTime = 0;
        double totalRemoveTime = 0;
        double totalSearchTime = 0;

        // Run multiple repetitions because the execution time
        // can vary between runs
        for (int i = 0; i < repetitions; ++i)
        {
            // Repeat the same operation multiple times because the
            // computer is too fast
            for (int j = 0; j < factor; ++j)
            {
                try {
                    auto s = generateHopHashMap(size); 

                    time.restart();
                    s.addValue(9);
                    time.stop();

                    totalInsertTime += time.time();

                    time.restart();
                    s.searchValue(9);
                    time.stop();

                    totalSearchTime += time.time();

                    time.restart();
                    s.removeValue(9);
                    time.stop();

                    totalRemoveTime += time.time();

                } catch(const char * error) {
                    std::cerr << "Error generating hash map: " << error << std::endl;
                    return;
                }
            }
        }

        // Use the average runtime as our output
        double averageInsertTime = (double)totalInsertTime / repetitions;
        double averageRemoveTime = (double)totalRemoveTime / repetitions;
        double averageSearchTime = (double)totalSearchTime / repetitions;
        std::cout << std::fixed
            << std::setw(4) << size << "|" << std::setprecision(10)
            << std::setw(16) << averageInsertTime << "|"
            << std::setw(16) << averageRemoveTime << "|"
            << std::setw(16) << averageSearchTime << "|"
            << std::endl;
     }  
}