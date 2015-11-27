#include"polygonsClasses.h"

using namespace std;

//Global variable
const double pi = 4 * atan(1);

//General functons used in implementation of all classes.
void rotatePoint(double point[2], const double &angle, const double(&about)[2]){
	// Translate the point to the origin so we can then rotate about the origin (much simpler!)
	point[0] = point[0] - about[0]; point[1] = point[1] - about[1];

	// Rotate new point about the origin using explicit form of matrix multiplication:
	// (x') - (cos(theta)  -sin(theta) ) (x)
	// (y') - (sin(theta)   cos(theta) ) (y)
	double rx = point[0] * cos(angle) - point[1] * sin(angle);
	double ry = point[0] * sin(angle) + point[1] * cos(angle);

	// Move the point back by the same amount.
	point[0] = rx + about[0];
	point[1] = ry + about[1];
}
void translatePoint(double point[2], const double &deltaX, const double &deltaY){
	point[0] = point[0] + deltaX;
	point[1] = point[1] + deltaY;
}

//The only base class function that is not overridden.
void polygon::rotateShape(const double &angle){
	rotateShape(angle, polygonCentre); //Call the derived class rotate function, and rotate about the centre of shape.
}


//Functions for isosolesTriangle Class------------------------------------------------------------------------------------------------
isosolesTriangle::isosolesTriangle(){ A[0] = A[1] = B[0] = B[1] = C[0] = C[1] = polygonCentre[0] = polygonCentre[1] = 0; }
isosolesTriangle::isosolesTriangle(double const &baseA, double const &sideB, double const &angle, double const (&posOfCentre)[2]){
	//Calculate the positions of the vertices. This is not centred on [0,0].
	B[1] = C[1] = A[0] = 0;
	B[0] = -0.5*baseA; C[0] = 0.5*baseA;
	A[1] = sqrt(sideB*sideB - 0.25 * baseA*baseA);

	double oldCentre[2] = { 0, A[1] / 3 };

	rotateShape(angle, oldCentre);

	//Calculate how much to move the shape to the user specified position.
	double deltaX = posOfCentre[0];
	double deltaY = posOfCentre[1] - oldCentre[1];

	translateShape(deltaX, deltaY);

	//Set the polgon centre to be stored inside the class.
	polygonCentre[0] = posOfCentre[0];
	polygonCentre[1] = posOfCentre[1];
}

void isosolesTriangle::rotateShape(const double &angle, double(&about)[2]){
	//Rotate each individual vertex
	rotatePoint(A, angle, about);
	rotatePoint(B, angle, about);
	rotatePoint(C, angle, about);
	rotatePoint(polygonCentre, angle, about);
}

void isosolesTriangle::translateShape(const double &deltaX, const double &deltaY){
	//Translate each individual vertex
	A[0] += deltaX; B[0] += deltaX; C[0] += deltaX; polygonCentre[0] += deltaX;
	A[1] += deltaY; B[1] += deltaY; C[1] += deltaY; polygonCentre[1] += deltaY;
}

void isosolesTriangle::scale(const double &scaleFactor){
	//Find the displacement between vertices and the centre of the polygon and then scale these vales
	double deltaA[2] = { (A[0] - polygonCentre[0])*scaleFactor, (A[1] - polygonCentre[1])*scaleFactor };
	double deltaB[2] = { (B[0] - polygonCentre[0])*scaleFactor, (B[1] - polygonCentre[1])*scaleFactor };
	double deltaC[2] = { (C[0] - polygonCentre[0])*scaleFactor, (C[1] - polygonCentre[1])*scaleFactor };

	//Find new vertices by adding the displacents to the position of the polygon centre.
	A[0] = deltaA[0] + polygonCentre[0]; A[1] = deltaA[1] + polygonCentre[1];
	B[0] = deltaB[0] + polygonCentre[0]; B[1] = deltaB[1] + polygonCentre[1];
	C[0] = deltaC[0] + polygonCentre[0]; C[1] = deltaC[1] + polygonCentre[1];
}

void isosolesTriangle::info(){
	cout << "Isosoles triangle with vertices at" << endl;

	//Print the vertices to console in (x,y) form
	cout << "(" << A[0] << ", " << A[1] << "), (" << B[0] << ", " << B[1] << "), (" << C[0] << ", " << C[1] << ")" << endl;
}

string isosolesTriangle::stringVertices(){
	// Concatonate vertices that are converted to strings together separated by semi-colons.
	string vertexA = to_string(A[0]) + " " + to_string(A[1]);
	string vertexB = to_string(B[0]) + " " + to_string(B[1]);
	string vertexC = to_string(C[0]) + " " + to_string(C[1]);
	string vertices = "[" + vertexA + "; " + vertexB + "; " + vertexC + "]";
	return vertices;
}

//Functions for the rectangle class----------------------------------------------------------------------------------------------------
rectangle::rectangle(){ A[0] = A[1] = B[0] = B[1] = C[0] = C[1] = D[0] = D[1] = polygonCentre[0] = polygonCentre[1] = 0; }
rectangle::rectangle(double const &baseA, double const &sideB, double const &angle, double const (&posOfCentre)[2]){
	A[0] = -0.5*baseA; A[1] = 0.5*sideB;
	B[0] = 0.5*baseA; B[1] = 0.5*sideB;
	C[0] = 0.5*baseA; C[1] = -0.5*sideB;
	D[0] = -0.5*baseA; D[1] = -0.5*sideB;

	polygonCentre[0] = polygonCentre[1] = 0;

	rotateShape(angle, polygonCentre);

	translateShape(posOfCentre[0], posOfCentre[1]);
}
void rectangle::rotateShape(const double &angle, double(&about)[2]){
	rotatePoint(A, angle, about);
	rotatePoint(B, angle, about);
	rotatePoint(C, angle, about);
	rotatePoint(D, angle, about);
	rotatePoint(polygonCentre, angle, about);
}
void rectangle::scale(const double &scaleFactor){
	double deltaA[2] = { (A[0] - polygonCentre[0])*scaleFactor, (A[1] - polygonCentre[1])*scaleFactor };
	double deltaB[2] = { (B[0] - polygonCentre[0])*scaleFactor, (B[1] - polygonCentre[1])*scaleFactor };
	double deltaC[2] = { (C[0] - polygonCentre[0])*scaleFactor, (C[1] - polygonCentre[1])*scaleFactor };
	double deltaD[2] = { (D[0] - polygonCentre[0])*scaleFactor, (D[1] - polygonCentre[1])*scaleFactor };

	A[0] = deltaA[0] + polygonCentre[0]; A[1] = deltaA[1] + polygonCentre[1];
	B[0] = deltaB[0] + polygonCentre[0]; B[1] = deltaB[1] + polygonCentre[1];
	C[0] = deltaC[0] + polygonCentre[0]; C[1] = deltaC[1] + polygonCentre[1];
	D[0] = deltaD[0] + polygonCentre[0]; D[1] = deltaD[1] + polygonCentre[1];
}
void rectangle::translateShape(const double &deltaX, const double &deltaY){
	A[0] += deltaX; B[0] += deltaX; C[0] += deltaX; D[0] += deltaX; polygonCentre[0] += deltaX;
	A[1] += deltaY; B[1] += deltaY; C[1] += deltaY; D[1] += deltaY; polygonCentre[1] += deltaY;
}
void rectangle::info(){
	cout << "Rectangle with vertices at" << endl;
	cout << "(" << A[0] << ", " << A[1] << "), (" << B[0] << ", " << B[1] << "), (" << C[0] << ", " << C[1] << "), (" << D[0] << ", " << D[1] << ")" << endl;
}

string rectangle::stringVertices(){
	string vertexA = to_string(A[0]) + " " + to_string(A[1]);
	string vertexB = to_string(B[0]) + " " + to_string(B[1]);
	string vertexC = to_string(C[0]) + " " + to_string(C[1]);
	string vertexD = to_string(D[0]) + " " + to_string(D[1]);
	string vertices = "[" + vertexA + "; " + vertexB + "; " + vertexC + "; " + vertexD + "]";
	return vertices;
}

//Functions for the pentagon class----------------------------------------------------------------------------------------------------
pentagon::pentagon(){ A[0] = A[1] = B[0] = B[1] = C[0] = C[1] = D[0] = D[1] = E[0] = E[1] = polygonCentre[0] = polygonCentre[1] = 0; }
pentagon::pentagon(double const &side, double const &angle, double const (&posOfCentre)[2]){
	//Make a pentagon of circumradius 1:
	A[0] = 0, A[1] = 1;
	B[0] = sin(2 * pi / 5); B[1] = cos(2 * pi / 5);
	C[0] = sin(4 * pi / 5); C[1] = -cos(pi / 5);
	D[0] = -sin(4 * pi / 5); D[1] = -cos(pi / 5);
	E[0] = -sin(2 * pi / 5); E[1] = cos(2 * pi / 5);
	polygonCentre[0] = polygonCentre[1] = 0;

	//Resize and reposition pentagon according to user specifications.
	double s = 2 * sin(pi / 5); //Length of side of this unit pentagon
	scale(side / s); //Scale shape up to user specification
	rotateShape(angle, polygonCentre);
	translateShape(posOfCentre[0], posOfCentre[1]);
}

void pentagon::rotateShape(const double &angle, double(&about)[2]){
	rotatePoint(A, angle, about);
	rotatePoint(B, angle, about);
	rotatePoint(C, angle, about);
	rotatePoint(D, angle, about);
	rotatePoint(E, angle, about);
	rotatePoint(polygonCentre, angle, about);
}

void pentagon::scale(const double &scaleFactor){
	double deltaA[2] = { (A[0] - polygonCentre[0])*scaleFactor, (A[1] - polygonCentre[1])*scaleFactor };
	double deltaB[2] = { (B[0] - polygonCentre[0])*scaleFactor, (B[1] - polygonCentre[1])*scaleFactor };
	double deltaC[2] = { (C[0] - polygonCentre[0])*scaleFactor, (C[1] - polygonCentre[1])*scaleFactor };
	double deltaD[2] = { (D[0] - polygonCentre[0])*scaleFactor, (D[1] - polygonCentre[1])*scaleFactor };
	double deltaE[2] = { (E[0] - polygonCentre[0])*scaleFactor, (E[1] - polygonCentre[1])*scaleFactor };

	A[0] = deltaA[0] + polygonCentre[0]; A[1] = deltaA[1] + polygonCentre[1];
	B[0] = deltaB[0] + polygonCentre[0]; B[1] = deltaB[1] + polygonCentre[1];
	C[0] = deltaC[0] + polygonCentre[0]; C[1] = deltaC[1] + polygonCentre[1];
	D[0] = deltaD[0] + polygonCentre[0]; D[1] = deltaD[1] + polygonCentre[1];
	E[0] = deltaE[0] + polygonCentre[0]; E[1] = deltaE[1] + polygonCentre[1];
}

void pentagon::translateShape(const double &deltaX, const double &deltaY){
	A[0] += deltaX; B[0] += deltaX; C[0] += deltaX; D[0] += deltaX; E[0] += deltaX; polygonCentre[0] += deltaX;
	A[1] += deltaY; B[1] += deltaY; C[1] += deltaY; D[1] += deltaY; E[1] += deltaY; polygonCentre[1] += deltaY;
}

void pentagon::info(){
	cout << "Regular pentagon with vertices at" << endl;
	cout << "(" << A[0] << ", " << A[1] << "), (" << B[0] << ", " << B[1] << "), (" << C[0] << ", " << C[1] << "), (" << D[0] << ", " << D[1] << ") ";
	cout << "(" << E[0] << ", " << E[1] << ")" << endl;
}

string pentagon::stringVertices(){
	string vertexA = to_string(A[0]) + " " + to_string(A[1]);
	string vertexB = to_string(B[0]) + " " + to_string(B[1]);
	string vertexC = to_string(C[0]) + " " + to_string(C[1]);
	string vertexD = to_string(D[0]) + " " + to_string(D[1]);
	string vertexE = to_string(E[0]) + " " + to_string(E[1]);
	string vertices = "[" + vertexA + "; " + vertexB + "; " + vertexC + "; " + vertexD + "; " + vertexE + "]";
	return vertices;
}

//Functions for the hexagon class----------------------------------------------------------------------------------------------------
hexagon::hexagon(){ A[0] = A[1] = B[0] = B[1] = C[0] = C[1] = D[0] = D[1] = E[0] = E[1] = F[0] = F[1] = polygonCentre[0] = polygonCentre[1] = 0; }

hexagon::hexagon(double const &side, double const &angle, double const (&posOfCentre)[2]){
	A[0] = -1; A[1] = 0;
	B[0] = -cos(pi / 3); B[1] = sin(pi / 3);
	C[0] = cos(pi / 3); C[1] = sin(pi / 3);
	D[0] = 1; D[1] = 0;
	E[0] = cos(pi / 3); E[1] = -sin(pi / 3);
	F[0] = -cos(pi / 3); F[1] = -sin(pi / 3);
	polygonCentre[0] = polygonCentre[1] = 0;

	double s = 2 * sin(pi / 6);
	scale(side / s);
	rotateShape(angle, polygonCentre);
	translateShape(posOfCentre[0], posOfCentre[1]);
}

void hexagon::rotateShape(const double &angle, double(&about)[2]){
	rotatePoint(A, angle, about);
	rotatePoint(B, angle, about);
	rotatePoint(C, angle, about);
	rotatePoint(D, angle, about);
	rotatePoint(E, angle, about);
	rotatePoint(F, angle, about);
	rotatePoint(polygonCentre, angle, about);
}

void hexagon::scale(const double &scaleFactor){
	double deltaA[2] = { (A[0] - polygonCentre[0])*scaleFactor, (A[1] - polygonCentre[1])*scaleFactor };
	double deltaB[2] = { (B[0] - polygonCentre[0])*scaleFactor, (B[1] - polygonCentre[1])*scaleFactor };
	double deltaC[2] = { (C[0] - polygonCentre[0])*scaleFactor, (C[1] - polygonCentre[1])*scaleFactor };
	double deltaD[2] = { (D[0] - polygonCentre[0])*scaleFactor, (D[1] - polygonCentre[1])*scaleFactor };
	double deltaE[2] = { (E[0] - polygonCentre[0])*scaleFactor, (E[1] - polygonCentre[1])*scaleFactor };
	double deltaF[2] = { (F[0] - polygonCentre[0])*scaleFactor, (F[1] - polygonCentre[1])*scaleFactor };

	A[0] = deltaA[0] + polygonCentre[0]; A[1] = deltaA[1] + polygonCentre[1];
	B[0] = deltaB[0] + polygonCentre[0]; B[1] = deltaB[1] + polygonCentre[1];
	C[0] = deltaC[0] + polygonCentre[0]; C[1] = deltaC[1] + polygonCentre[1];
	D[0] = deltaD[0] + polygonCentre[0]; D[1] = deltaD[1] + polygonCentre[1];
	E[0] = deltaE[0] + polygonCentre[0]; E[1] = deltaE[1] + polygonCentre[1];
	F[0] = deltaF[0] + polygonCentre[0]; F[1] = deltaF[1] + polygonCentre[1];
}

void hexagon::translateShape(const double &deltaX, const double &deltaY){
	A[0] += deltaX; B[0] += deltaX; C[0] += deltaX; D[0] += deltaX; E[0] += deltaX; F[0] += deltaX; polygonCentre[0] += deltaX;
	A[1] += deltaY; B[1] += deltaY; C[1] += deltaY; D[1] += deltaY; E[1] += deltaY; F[1] += deltaY; polygonCentre[1] += deltaY;
}

void hexagon::info(){
	cout << "Regular hexagon with vertices at" << endl;
	cout << "(" << A[0] << ", " << A[1] << "), (" << B[0] << ", " << B[1] << "), (" << C[0] << ", " << C[1] << "), " << endl;
	cout << "(" << D[0] << ", " << D[1] << "), (" << E[0] << ", " << E[1] << "), (" << F[0] << ", " << F[1] << ") " << endl;
}

string hexagon::stringVertices(){
	string vertexA = to_string(A[0]) + " " + to_string(A[1]);
	string vertexB = to_string(B[0]) + " " + to_string(B[1]);
	string vertexC = to_string(C[0]) + " " + to_string(C[1]);
	string vertexD = to_string(D[0]) + " " + to_string(D[1]);
	string vertexE = to_string(E[0]) + " " + to_string(E[1]);
	string vertexF = to_string(F[0]) + " " + to_string(F[1]);
	string vertices = "[" + vertexA + "; " + vertexB + "; " + vertexC + "; " + vertexD + "; " + vertexE + "; " + vertexF + "]";
	return vertices;
}