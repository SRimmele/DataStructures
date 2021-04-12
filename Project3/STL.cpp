#include <iostream> 
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <unordered_map>
#include <string> 

#include "Complexity_Timer.hpp"
#include "LinearProbe.hpp"

const int operations = 3;

const char* headings[operations] = 
{
    "| Insert         ", 
    "| Delete           ", 
    "| Search    "
};

std::unordered_map<std::string, int> generateSTLHashMap(int size, int maxSize) {
    std::unordered_map<std::string, int> hashMap; 

    srand(time(NULL)); 

    // Run every time for each key
    for(int i = 0; i < size; ++i) {
        int randNum = rand() % 32; 

        // Run every time for each character in key
        std::string key = "";
        for(int j = 0; j < randNum + 1; ++j) { 
            char randLetter = 'a' + rand() % 26;
            key += randLetter; 
        }
        
        hashMap.insert({key, randNum});
    }
    
    return hashMap; 
}

int runSTL()
{
    timer time;

    // How many times to perform each task to get the average
    const int repetitions = 7;

    // How many times to repeat the operation per task
    // (adding constant to our big-oh runtime)
    const int factor = 5000;

    std::cout << "My Linear Probing Hash Table: \n"; 
    std::cout << "____";
    for (int i = 0; i < operations; ++i)
      std::cout << headings[i];
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
                    auto s = generateSTLHashMap(size, size + 1); 

                    time.restart();
                    try {
                        s.insert({"sav", 9});
                    } catch(const char* error) {
                        std::cerr << "Error inserting key 'sav': " << error << std::endl;
                        return 1;
                    }
                    time.stop();
                    totalInsertTime += time.time();
                    time.restart();
                    try {
                        s.find("sav");
                    } catch(const char* error) {
                        std::cerr << "Error searching key 'sav': " << error << std::endl;
                        return 1;
                    }
                    time.stop();
                    totalSearchTime += time.time();

                    time.restart();
                    try {
                        s.erase("sav");
                    } catch(const char* error) {
                        std::cerr << "Error removing key 'sav': " << error << std::endl;
                        return 1;
                    }
                    time.stop();
                    totalRemoveTime += time.time();
                } catch(const char * error) {
                    std::cerr << "Error generating hash map: " << error << std::endl;
                    return 1;
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