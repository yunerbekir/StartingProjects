#pragma once
#include "stdafx.h"

#include<iostream>
#include<fstream>
#include<string>
#include "Shape.h"

class Circle : public Shape
{
private:
	double m_CenterX, m_CenterY, m_Radius;
	// void SetCorrectPossition() was not written because 
	// the code can work without it
public:
	// default consturctor with copy constructor and to make sure that
	// the center of the circle is in the correct quadrant and that the
	// radius is not < 0
	Circle(double _CenterX, double _CenterY, double _Radius, std::string _Color);
	Circle(std::string);
	Circle(const Circle&);
	// get methods
	double GetCenterX() const { return m_CenterX; }
	double GetCenterY() const { return m_CenterY; }
	double GetRadius() const { return m_Radius; }
	double GetArea()const override{ return 3.14*m_Radius*m_Radius; }

	// operators
	friend std::ofstream& operator<<(std::ofstream& FileStream, const Circle& _Circle);
	friend std::ostream& operator<<(std::ostream& OutputStream, const Circle& _Circle);

	// other methods
	void Print()const override{ std::cout << *this; }
	void Translate(double PointX, double PointY) override; 
};
