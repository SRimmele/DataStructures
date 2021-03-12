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
   Files: StackArray.cpp
          Complexity_Timer.hpp

   COPYRIGHT (C) 2018 Will Crissey, Jr. All rights reserved.
   DS316 Sample Project example.
   Author.  Will Crissey, Jr.
   Version. 1.02 06.03.2018.
   Files: DS316_Project_Standard_Code_Example.cpp
          Complexity_Timer.hpp
          Complexity_Recorder.hpp

    The purpose of this program is to record the times of the push(k), pop(), and search(n) functions of 
    each of the stack tests cases, focusing on the time and space complexity of STL and array-based 
    stack against my own linked list stack. 
*/

#include "MyStack.hpp"
#include "STLStack.hpp"
#include "StackArray.hpp"

int main() {
    runner();
    runnerSTL(); 
    runnerArray(); 

    return 0;
}