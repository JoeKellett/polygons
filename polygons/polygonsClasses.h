#ifndef POLYGONSCLASSES_H
#define POLYGONSCLASSES_H //Do not attempt to define the same thing twice.

#include<iostream>
#include<typeinfo>
#include<cmath>
#include<string>

//Functions used by all the classes
void rotatePoint(double point[2], const double &angle, const double(&about)[2]);
void translatePoint(double point[2], const double &deltaX, const double &deltaY);


class polygon {
protected:
	double polygonCentre[2]; //Coordinate that is common to all polygons
public:
	polygon(){};
	virtual ~polygon(){}; //Virtual distructor, this gets overridden by derived classes.

	//Pure virtual functions
	virtual	void rotateShape(const double &angle, double(&about)[2]) = 0;
	virtual void scale(const double &scaleFactor) = 0;
	virtual void translateShape(const double &deltaX, const double &deltaY) = 0;
	virtual void info() = 0; //Prints info for the user regarding that polygon
	virtual std::string stringVertices() = 0; //Outputs vertices in a matlab friendly form.

	//Function to rotate about the centre of shape by default if no point of rotation is supplied. It is NOT overloaded. Note this only works with base class pointers!
	void rotateShape(const double &angle);
};

class isosolesTriangle : public polygon{
protected:
	double A[2], B[2], C[2]; //Vertices
public:
	//Functions delcared here but defined in polygonsClasses.cpp
	~isosolesTriangle(){}; //Destructor
	isosolesTriangle(); //Default constructor
	isosolesTriangle(double const &baseA, double const &sideB, double const &angle, double const (&posOfCentre)[2]); //Parameterised constructor
	void rotateShape(const double &angle, double(&about)[2])override; //Override key word to insure that compiler throws and error when there is no successful overriding.
	void scale(const double &scaleFactor)override; //Scales the shape about the cetre
	void translateShape(const double &deltaX, const double &deltaY)override;
	void info()override; //Provides information about the shape to console
	std::string stringVertices()override; //Creates a string of the vertices for file writing
};

class rectangle : public polygon {
protected:
	double A[2], B[2], C[2], D[2];
public:
	~rectangle(){};
	rectangle();
	rectangle(double const &baseA, double const &sideB, double const &angle, double const (&posOfCentre)[2]);
	void rotateShape(const double &angle, double(&about)[2])override;
	void scale(const double &scaleFactor)override;
	void translateShape(const double &deltaX, const double &deltaY)override;
	void info()override;
	std::string stringVertices()override;
};

class pentagon : public polygon {
protected:
	double A[2], B[2], C[2], D[2], E[2];
public:
	~pentagon(){};
	pentagon();
	pentagon(double const &side, double const &angle, double const (&posOfCentre)[2]);
	void rotateShape(const double &angle, double(&about)[2])override;
	void scale(const double &scaleFactor)override;
	void translateShape(const double &deltaX, const double &deltaY)override;
	void info()override;
	std::string stringVertices()override;
};

class hexagon : public polygon {
protected:
	double A[2], B[2], C[2], D[2], E[2], F[2];
public:
	~hexagon(){};
	hexagon();
	hexagon(double const &side, double const &angle, double const (&posOfCentre)[2]);
	void rotateShape(const double &angle, double(&about)[2])override;
	void scale(const double &scaleFactor)override;
	void translateShape(const double &deltaX, const double &deltaY)override;
	void info()override;
	std::string stringVertices()override;
};

#endif