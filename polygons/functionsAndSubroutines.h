//Header guard
#ifndef FUNCTIONSANDSUBROUTINES_H
#define FUNCTIONSANDSUBROUTINES_H 

#include<vector>
#include<iostream>
#include"polygonsClasses.h"
#include<fstream> 
#include<limits> //Required to set clear the entire stream without using 'magic' numbers

//Check if running on windows machine and include windows.h if it is.
//windows.h is required for ShellExecute function.
#if defined (_WIN32)
#define NOMINMAX //So that max defined in Windows is not conflicting with max using in limits.
#include<Windows.h>
#endif

using namespace std;

//Define functions used in functionsAndSubroutines.cpp and polygonsMain.cpp

double giveNumber(bool const &checkNegative); //Gets a user to enter a number and checks the input is valid

bool giveYN(); //Gets a user to answer a yes/no question and checks the answer is valid

vector<polygon*> userInputPolygons(); //Subroutine that allows the user to create polygons

vector<polygon*> userEditPolygons(vector<polygon*> &storedPolygons); //Subroutine that allows the user to edit polygons

void printAll(const vector<polygon*>  &storedPolygons); //Prints stored polygons to the console

void plotMatlab(const vector<polygon*>  &storedPolygons); //Writes a matlab script and attempts to open it in Windows,

void writeAll(const vector<polygon*>  &storedPolygons); //Writes the stored polygons to a text file

#endif 