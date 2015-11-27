// PHYS 30762 Programming in C++
// Project - Polygons
// Lets the user create, edit and plot (using matlab) pentagons.

#include"functionsAndSubroutines.h"
#include"polygonsClasses.h" //Technically not required as functionsAndSubroutines.h includes this header, and it will not be redefined
// However, it is left here for clarity.

using namespace std;


int main(){
	cout.precision(4);
	cout << "-----------------------Polygons demonstration-----------------------------------" << endl;
	cout << "This is a short programme demonstrating the capabilities of using a class" << endl;
	cout << "inheritance system to store and manipulate polygons. You will be asked to input" << endl;
	cout << "details for an arbitary number of polygons before the programme outputs" << endl;
	cout << "information and gives the user the option to store them or further manipulate" << endl;
	cout << "them." << endl;
	cout << "--------------------------------------------------------------------------------" << endl;

	//Asks the user to enter polygon details. Check functionsAndSubroutines.cpp for implementation
	vector<polygon*> storedPolygons = userInputPolygons();
	
	//Prints information for all user entered polygons
	printAll(storedPolygons);
	
	//Asks the user if they want to edit/manipulate the polygons, and allows them to pick which ones to edit.
	cout << "Do you wish to edit any of the polygons you entered?  y/n  ";
	if (giveYN() == true) { userEditPolygons(storedPolygons); }

	cout << "Do you wish to save the polygons in a matlab script to plot them?" << endl;
	cout << "(If you are running windows with matlab the script will automatically open" << endl;
	cout << "in matlab).   y/n  ";
	
	//Writes a matlab script file and then opens it in matlab if on a windows machines. If matlab is not installed then it will open
	//in a programme defined in Windows, like notepad.
	if (giveYN() == true) { plotMatlab(storedPolygons); }

	cout << "Do you wish to save the polygon vertices in a text file?  y/n  ";
	if (giveYN() == true) { writeAll(storedPolygons); }

	//Delete stored vectors so as to free memory.
	for (vector<polygon*>::const_iterator iter = storedPolygons.begin(); iter < storedPolygons.end(); ++iter){ delete *iter;	}
	storedPolygons.clear();

	system("pause"); //Pause so user can look at contents of console before it  closes.
	
	return 0;
}