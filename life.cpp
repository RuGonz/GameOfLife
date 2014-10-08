/****************************************************
Name:Rudy Gonzalez	
Date: 01/16/13
Problem Number:
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

//This file provides the implementation of the life.h header file.


#include <iostream>
#include <fstream>

#include "life.h"

using namespace std;

//GLOBAL VARIABLES
int ROWS = 2,//2
	xRows,         //stores the number of rows in the grid
    COLUMNS = 2,//2
	xColumns;      //stores the number of rows in the grid
const int NUM_GENERATIONS = 1; //set to a smaller number for debugging
const char FILE_NAME[] = "glider_gun_fight.txt";
char ** ptr; //// changed from int to char
int ** ptrCount;
char ** ptrTemp;
//char ** ptrCopy;

//This function reads input file for subsequent prosessing (add high level 
//description of your implementation logic) 
void populateWorld (const char * file)
{
ifstream fin(file);
	//file validation
	if(!fin)
		cout << "Cannot open input file.\n";

	//counts columns
	while(fin.peek() == '0' || fin.peek()=='1' )// fin.peek() != '\r')
	{
         COLUMNS++;
         fin.get();
    }

	//while(fin.get()!='\r') || fin.get()!= '\n')
	//	COLUMNS++;


	fin.clear();
	fin.seekg(0, ios::beg);

	//counts rows
	char array[COLUMNS];

	while(fin >> array)
		ROWS++;

	fin.clear();
	fin.seekg(0, ios::beg);


	ptr = new char *[ROWS];

	for(int i = 0; i < ROWS; i++)
		ptr[i] = new char [COLUMNS];

	for(int j = 0; j < ROWS; j++)
			for(int k = 0; k < COLUMNS; k++)
				ptr[j][k]= '.';

	for(int j = 1; j < ROWS-1; j++)// j=1  ROWS-1
	{
		fin >> array;
		for(int k = 1; k < COLUMNS-1; k++)//  k=1 COLUMNS-1
		{
			if (array[k-1] == '1')//k-1
				ptr[j][k] = 'O';
			else if(array[k-1] == '0')//k-1
				ptr[j][k] = 'x';
		}
	}
	fin.close();

}

//This function outputs the grid for current generation (add high level 
//description of your implementation logic) 
void showWorld ()
{
	for(int j = 1; j < ROWS-1; j++)
	{
		for(int k = 1; k < COLUMNS-1; k++)
			cout << ptr[j][k];
		cout << endl;
	}

}

//This function creats new geneneration grid from the old generation grid
//(add high level description of your implementation logic)
void iterateGeneration ()
{
     	//neighbors to cell
	int neighbors = 0;
	xColumns = COLUMNS;
	xRows = ROWS;

	//create new d array with 2 extra rows
	ptrCount = new int *[xRows];
	//create new dynamic array with 2 extra columns
	for(int i = 0; i < xRows; i++)
		ptrCount[i] = new int [xColumns];

	//set all cells to dead
	for(int j = 0; j < xRows; j++)
	{
		for(int k = 0; k < xColumns; k++)
			ptrCount[j][k] = 0;
	}
	for(int j = 1; j < ROWS-1; j++)//j=1 ROWS-1
	{
		for(int k = 1; k < COLUMNS-1; k++)// k=1 COLUMNS-1
		{
			//calculate # of neighbors
			if(ptr[j-1][k-1] == 'O')// top left corner
				neighbors++;
			if(ptr[j-1][k] == 'O')// top
				neighbors++;
			if(ptr[j-1][k+1] == 'O') // top right corner
				neighbors++;
			if(ptr[j][k-1] == 'O') // left
				neighbors++;
			if(ptr[j][k+1] == 'O') // right
				neighbors++;
			if(ptr[j+1][k-1] == 'O') //bottom left corner
				neighbors++;
			if(ptr[j+1][k] == 'O') //bottom
				neighbors++;
			if(ptr[j+1][k+1] == 'O') //bottom right corner
				neighbors++;
			//record # of neighbors around cell
			ptrCount[j][k] = neighbors;
			neighbors = 0;
		}
	}
    	for(int j = 1; j < ROWS-1; j++)// j=1 ROWS-1
	{
		for(int k = 1; k < COLUMNS-1; k++)// k=1 COLUMNS-1
		{
			if(ptrCount[j][k] == 3) // born into Big Love
				ptr[j][k] = 'O';
			else if(ptrCount[j][k] >= 4) //dies
				ptr[j][k] = 'x';
			else if(ptrCount[j][k] <= 1) // dies of sad lonely life
				ptr[j][k] = 'x';
			else if(ptrCount[j][k] == 2 && ptr[j][k] == 'O')// lives on if accompanied by 2 friends
				ptr[j][k] = 'O';
			else
				ptr[j][k] = 'x';
		}
	}
}
