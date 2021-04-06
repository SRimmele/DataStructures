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
    "| Insert           ", 
    "| Delete           ", 
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

        i = i + 1 % maxSize;
    }

    array[i] = Pair();
    array[i].key = key;
    array[i].value = value;
}

void HashTable::remove(std::string key)
{
    int i = hashFunction(key); 

    // Make sure key is in map
    search(key);

    // Mark pair with key as empty
    for(int num_iters = 0; num_iters < maxSize && array[i].key.length() != 0; ++num_iters) {
        if(array[i].key == key) {
            array[i].key = "";
            break;
        }

        i = i + 1 % maxSize;
    }

    int lastI = i;
    i = i + 1 % maxSize;
    for(int num_iters = 0; num_iters < maxSize; ++num_iters) {
        if(array[i].key.length() == 0) {
            break;
        }

        auto hashResult = hashFunction(array[i].key);
        if(hashFunction(array[i].key) == hashFunction(key)) {
            array[lastI].key = array[i].key;
            array[lastI].value = array[i].value;

            array[i].key = "";

            lastI = i;
            num_iters = 0;
        }
    
        i = i + 1 % maxSize;
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

        i = i + 1 % maxSize;
    }

    throw "Key not in map";
}

HashTable generateHashMap(int size, int maxSize) {
    HashTable map(maxSize);

    for(int i = 0; i < size; ++i) {
        map.insert(std::to_string(i), i);
    }
}
//  generateHash(int size, int maxSize_)
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
    HashTable map(16);
    map.insert("a", 1);  // a -> 0
    map.insert("ab", 2); // ab -> 1
    map.insert("abc", 3); // abc -> 2

    map.insert("c", 4); // c -> 3
    map.insert("c", 5);
    map.insert("d", 6);

    map.remove("a"); 
    // try {
    //     map.insert("", 10); 
    // } catch(const char *error) {
    //     std::cerr << error << std::endl;
    // }

    // std::cout << map.search("a") << std::endl; 
    // std::cout << map.search("abc") << std::endl; 
    // try {
    //     std::cout << map.search("z") << std::endl; 
    // } catch (const char* error) {
    //     std::cout << error << std::endl;
    // }

    return 0;
}

int driver_main()
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