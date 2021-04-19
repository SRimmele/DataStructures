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
 * 3. Experimenter (1, 10, 19, 28) Hopscotch Hashing OR STL
 * 
 * # Notes
 * - Do not have to use sample code
 */


#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <string>

#include "Complexity_Timer.hpp"
#include "LinearProbe.hpp"

const int operations = 3;

const char* headings[operations] = 
{
    "| Insert         ", 
    "| Delete         ", 
    "| Search    "
};

HashTable::HashTable(int maxSize_)
{
    currentSize = 0; 
    maxSize = maxSize_; 
    array = new Pair[maxSize]; 
}

HashTable::~HashTable()
{
    delete [] array; 
}

int HashTable::hashFunction(std::string key)
{
    return (key.length() - 1) % maxSize; 
}

void HashTable::insert(std::string key, int value)
{
    int i = hashFunction(key);

    // Fail if map is full
    if(currentSize == maxSize){
        throw "Map is full";
    }

    // Fail if key is empty string
    if(key == ""){
        throw "Empty key not allowed";
    }
    
    // Check for collisions
    while(array[i].key.length() != 0) {
        // Fail if duplicate key
        if(array[i].key == key) {
            array[i].value = value;
            return;
        }

        i = (i + 1) % maxSize;
    }

    array[i].key = key;
    array[i].value = value;
}

void HashTable::remove(std::string key)
{
    int i = hashFunction(key);
    const auto hashedKey = hashFunction(key); 

    // Make sure key is in map
    search(key);

    // Mark pair with key as empty
    for(int num_iters = 0; num_iters < maxSize && array[i].key.length() != 0; ++num_iters) {
        if(array[i].key == key) {
            array[i].key = "";
            break;
        }
    }

    int lastI = i;
    i = (i + 1) % maxSize;
    for(int num_iters = 0; num_iters < maxSize; ++num_iters) {
        if(array[i].key.length() == 0) {
            break;
        }

        // Break after all keys that hash to removed key's hash have been moved.
        // Prevent infinite loop
        if(hashFunction(key) == i){
            break; 
        }

        auto hashResult = hashFunction(array[i].key);
        if(hashFunction(array[i].key) == hashedKey) {
            array[lastI].key = array[i].key;
            array[lastI].value = array[i].value;

            array[i].key = "";

            lastI = i;
            num_iters = 0;
        }
    
        i = (i + 1) % maxSize;
    }
}

int HashTable::search(std::string key)
{
    int i = hashFunction(key); 

    // Search for key if collision
    for(int num_iters = 0; num_iters < maxSize && array[i].key.length() != 0; ++num_iters) {
        if(array[i].key == key) {
            return array[i].value;
        }

        i = (i + 1) % maxSize;
    }

    throw "Key not in map";
}

void HashTable::print() {
    for(int i = 0; i < maxSize; ++i){
        std::cout << std::right << std::setw(3) << i << " | ";
        if(array[i].key != ""){
            std::cout << '"' << array[i].key << '"' << ": "
                       << array[i].value; 
        }
        std::cout << std::endl;
    }
    
}

HashTable generateHashMap(int size, int maxSize) {
    HashTable map(maxSize);

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
        
        map.insert(key, randNum);
    }
    
    return map; 
}

void runLinearProbing()
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
                    auto s = generateHashMap(size, size + 1); 

                    time.restart();
                    try {
                        s.insert("sav", 9);
                    } catch(const char* error) {
                        std::cerr << "Error inserting key 'sav': " << error << std::endl;
                        return;
                    }
                    time.stop();
                    totalInsertTime += time.time();
                    time.restart();
                    try {
                        s.search("sav");
                    } catch(const char* error) {
                        std::cerr << "Error searching key 'sav': " << error << std::endl;
                        return;
                    }
                    time.stop();
                    totalSearchTime += time.time();

                    time.restart();
                    try {
                        s.remove("sav");
                    } catch(const char* error) {
                        std::cerr << "Error removing key 'sav': " << error << std::endl;
                        return;
                    }
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