#include <iostream>
#include <conio.h>

using namespace std;

// Example of interface and base classes segregation in Cpp.

// -----------------------------------------------------------------------------------------------------
// Interface class
// -----------------------------------------------------------------------------------------------------
class IShape 
{
	public:
		virtual double getArea() = 0; // pure virtual function providing interface framework.
};

// -----------------------------------------------------------------------------------------------------
// Base class
// -----------------------------------------------------------------------------------------------------
class PolygonBase : IShape
{
	protected:
		double width;
		double height;

	public:
		void setWidth(double w) 
		{
			width = w;
		}

		void setHeight(double h) 
		{
			height = h;
		}
};

class EllipseBase : IShape
{
	protected:
		double minorRadius;
		double greaterRadius;

	public:
		void setMinorRadius(double m) 
		{
			minorRadius = m;
		}

		void setGreaterRadius(double g) 
		{
			greaterRadius = g;
		}
};

class CircleBase : IShape
{
	protected:
		double radius;

	public:
		void setRadius(double r)
		{
			radius = r;
		}
};

// ----------------------------------------------------------------------------------------------------- 
// Derived classes
// -----------------------------------------------------------------------------------------------------
class Rectangle: public PolygonBase 
{
	public:
		double getArea() 
		{ 
			return (width * height); 
		}
};

class Triangle: public PolygonBase
{
	public:
		double getArea() 
		{ 
			return (width * height)/2; 
		}
};

class Ellipse : public EllipseBase
{
	public:
		double getArea()
		{
			return (minorRadius * greaterRadius) * 3.141592653589793238;
		}
};

class Circle : public CircleBase
{
	public:
		double getArea()
		{
			return (radius * radius) * 3.141592653589793238;
		}		
};

int main() 
{
	Rectangle rectangle;
	Triangle  triangle;
	Ellipse   ellipse;
	Circle	circle;
	
	rectangle.setWidth(5);
	rectangle.setHeight(7);
	cout << "Total rectangle area: " << rectangle.getArea() << endl;
	
	triangle.setWidth(5);
	triangle.setHeight(7);
	cout << "Total triangle area: " << triangle.getArea() << endl; 
	
	ellipse.setMinorRadius(2.5);
	ellipse.setGreaterRadius(3.5);
	cout << "Total ellipse area: " << ellipse.getArea() << endl; 
	
	circle.setRadius(3);
	cout << "Total circle area: " << circle.getArea() << endl; 
	
	getch();
}
