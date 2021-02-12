#ifndef STL_STACK_HPP
#define STL_STACK_HPP

#include <stack> 
#include <vector> 

std::stack<int, std::vector<int>> generateSTL_Stack(int size);
int search(int element, std::stack<int, std::vector<int>> s); 

void runnerSTL();  

#endif  //STL Stack HPP

