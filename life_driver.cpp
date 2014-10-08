/****************************************************
Name: Rudy Gonzalez 
Date: 01/16/13
Problem Number:
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

// This is driver's code


#ifdef linux 
#define LINUX true
#define WINDOWS false
#endif

#ifdef __WIN32__ 
#define LINUX false 
#define WINDOWS true
#endif


#include <iostream>
#include <fstream>
#include "life.h"

const char FILE_NAME[] = "glider_gun_fight.txt";

using namespace std;

const int NUM_GENERATIONS = 9; //set to a smaller number for debugging

int main() 
{
    populateWorld(FILE_NAME);
       
    showWorld();

   for (int iteration = 0; iteration < NUM_GENERATIONS; iteration++) 
      {
        if (WINDOWS)
           system("cls"); //Windows only
       else
           system("clear"); //Linux only
    
        iterateGeneration();
    
        showWorld();
    } 

    if (WINDOWS)
        system("PAUSE");

    return 0;
}
