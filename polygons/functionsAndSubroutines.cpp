#include"functionsAndSubroutines.h"


double giveNumber(bool const &checkNegative){
	double dNumber;
	bool bInputCorrect(false);
	do{
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Clears the entire stream.
		cin.clear(); //Resets any fail flags
		cin >> dNumber;
		if (cin.fail()){
			cout << "Input incorrect, please enter correctly." << endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
		}
		//Stops user inputting negative value if checkNegative is true.
		else if (checkNegative == true && dNumber < 0){ cout << "Please enter a positive value." << endl; }
		
		else{ bInputCorrect = true; }

	} while (bInputCorrect == false);

	return dNumber;
} 

bool giveYN(){
	char cYN;
	bool bYN, bChoiceCorrect;
	
	do{
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.clear();
		cin >> cYN; //Get first character of user input.

		if (cYN == 'y' || cYN == 'Y'){
			bYN = true;
			bChoiceCorrect = true; //user said yes
		}
		else if (cYN == 'n' || cYN == 'N') {
			bYN = false;
			bChoiceCorrect = true;
		}
		else{
			cout << "Please only enter y  or  n " << endl;
			bChoiceCorrect = false; //User didn't enter y or n so ask again.
		}
	} while (bChoiceCorrect == false);

	return bYN;
}

vector<polygon*> userInputPolygons(){
	vector<polygon*> storedPolygons;
	bool bInputCorrect(false);
	char cPolygonChoice;
	double base, side, angle, posOfCentre[2];
	
	do{
		
		do{
			cout << "Please enter which polygon you wish to create (t=Isosoles triangle, r=Rectangle" << endl;
			cout << ", p=Pentagon, h=Hexagon):   ";
			cin >> cPolygonChoice;
			
			if (cPolygonChoice == 't' || cPolygonChoice == 'r' || cPolygonChoice == 'p' || cPolygonChoice == 'h'){
				bInputCorrect = true;
			}
			else{ cout << endl << "Please enter ONE of the above lower case characters." << endl; }

		} while (bInputCorrect == false);

		//Switch block performs different things for different cases. Equivalent to many if's and else if's.
		switch (cPolygonChoice){
		case 't':
			cout << "Please enter the size of the base (unique side) of the isosoles triangle: ";
			base = giveNumber(true);

			cout << "Please enter the size of the other side(s) of the triangle: ";
			side = giveNumber(true);

			cout << "Please enter the angle in radians you wish to orientate the triangle by: ";
			angle = giveNumber(false);

			cout << "Please enter where you want the the centre of the triangle to be: x= ";
			posOfCentre[0] = giveNumber(false);
			cout << "y= ";
			posOfCentre[1] = giveNumber(false);

			//Create the triangle in storage vector using the values the user entered.
			storedPolygons.push_back(new isosolesTriangle(base, side, angle, posOfCentre));
			
			break;

		case 'r':
			cout << "Please enter the size of the base of the rectangle: ";
			base = giveNumber(true);

			cout << "Please enter the size of the side(s) of the rectangle: ";
			side = giveNumber(true);

			cout << "Please enter the angle in radians you wish to orientate the rectangle by: ";
			angle = giveNumber(false);

			cout << "Please enter where you want the the centre of the rectangle to be: x= ";
			posOfCentre[0] = giveNumber(false);
			cout << "y= ";
			posOfCentre[1] = giveNumber(false);
			cout << endl;

			storedPolygons.push_back(new rectangle(base, side, angle, posOfCentre));
			
			break;

		case 'p':
			cout << "Please enter the size of a side of the regular pentagon: ";
			side = giveNumber(true);

			cout << "Please enter the angle in radians you wish to orientate the pentagon by: ";
			angle = giveNumber(false);

			cout << "Please enter where you want the the centre of the pentagon to be: x= ";
			posOfCentre[0] = giveNumber(false);
			cout << "y= ";
			posOfCentre[1] = giveNumber(false);
			cout << endl;
			
			storedPolygons.push_back(new pentagon(side, angle, posOfCentre));
			
			break;

		case 'h':
			cout << "Please enter the size of a side of the regular hexagon: ";
			side = giveNumber(true);

			cout << "Please enter the angle in radians you wish to orientate the hexagon by: ";
			angle = giveNumber(false);

			cout << "Please enter where you want the the centre of the hexagon to be: x= ";
			posOfCentre[0] = giveNumber(false);
			cout << "y= ";
			posOfCentre[1] = giveNumber(false);
			cout << endl;
			
			storedPolygons.push_back(new hexagon(side, angle, posOfCentre));
			
			break;
		}

		cout << "Do you wish to add another polygon y/n " << endl;
	} while (giveYN()==true);

	return storedPolygons;
}

void printAll(const vector<polygon*>  &storedPolygons){
	cout << "The stored polygons are: " << endl;
	for (vector<polygon*>::const_iterator iter = storedPolygons.begin(); iter < storedPolygons.end(); ++iter){
		(*iter)->info();//iter is a pointer to a pointer, thus needs to get dereferenced twice.
		cout << endl;
	}
}

vector<polygon*> userEditPolygons(vector<polygon*> &storedPolygons){
	double dMove[2], dScaleFactor, angle;
	
	for (vector<polygon*>::iterator iter = storedPolygons.begin(); iter < storedPolygons.end(); ++iter){
		cout << "Do you wish to edit this polygon?  y/n  " << endl;
		(*iter)->info();

		if (giveYN() == true){
			cout << "Enter the angle (radians) that you wish to rotate the polygon by: ";
			angle = giveNumber(false);
			(*iter)->rotateShape(angle);

			cout << "Enter how much you wish to translate the shape by in the x direction: ";
			dMove[0] = giveNumber(false);
			cout << "Enter how much you wish to translate the shape by in the y direction: ";
			dMove[1] = giveNumber(false);
			(*iter)->translateShape(dMove[0], dMove[1]);

			cout << "Enter the factor you wish to scale the shape by: ";
			dScaleFactor = giveNumber(true);
			(*iter)->scale(dScaleFactor);
		}
	}
	return storedPolygons;
}

void plotMatlab(const vector<polygon*>  &storedPolygons){
	ofstream myfile;
	myfile.open("polygonsplot.m"); //Open file for writing inside the polygons solution folder.

	//Write a matlab script by directly inputting strings to the file.
	myfile << "%This is a procedurally generated script by polygons.exe\nhold on \n";

	for (vector<polygon*>::const_iterator iter = storedPolygons.begin(); iter < storedPolygons.end(); ++iter){
		myfile << "polygon = " << (*iter)->stringVertices() << "; \n";
		myfile << "patch(polygon(:, 1), polygon(:, 2), 'r', 'FaceColor',[rand() rand() rand()]); \n"; //Plot the polygon with random face colour.
	}

	myfile << "axis equal\n";//Make x and y axis have same scale so regular polygons look regular!
	
	myfile.close();

#if defined (_WIN32)
	ShellExecute(0, 0, L"polygonsplot.m", 0, 0, SW_SHOW); //Opens the file with the default programme defined by windows.
#else
	cout<<"A matlab .m file has been saved to this directory."<<endl; //In case of non windows machine
#endif

	cout << "Matlab script created. You will have to run it yourself though!" << endl;
}

void writeAll(const vector<polygon*>  &storedPolygons){
	ofstream myfile;
	myfile.open("polygonVertices.txt"); 

	for (vector<polygon*>::const_iterator iter = storedPolygons.begin(); iter < storedPolygons.end(); ++iter){
		myfile << (*iter)->stringVertices() << "\n";
	}

	myfile.close();

	cout << "polygonVertices.txt succesfully written to programme directory." << endl;
	cout << "Vertices delimeted by semicolon, x and y of a vertex delimted by white space." << endl;
}