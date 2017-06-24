#pragma once
#include "stdafx.h"

#include<cmath>
#include<iostream>
#include<fstream>
#include<string>
#include "Shape.h"


class Line : virtual public Shape
{
private:
	double m_StartX, m_StartY;
	double m_EndX, m_EndY;
	void SetCorrectPossition(); // this method makes shure that
								// the coordinates of the 2 points
								// defining the line are not out of
								//  bonds, and displays a message
								//  when a conversion has taken place
	double GetArea()const override { return 0; }
protected:
public:

	//constructors
	Line() { m_StartX = m_StartY = m_EndX = m_EndY = 0; }
	Line(double, double, double, double, std::string);
	Line(std::string);

	//get methods
	double GetStartX()const { return m_StartX; };
	double GetStartY()const { return m_StartY; };
	double GetEndX()const { return m_EndX; };
	double GetEndY()const { return m_EndY; };
	double GetLength()const {
		return sqrt((m_EndX - m_StartX)*(m_EndX - m_StartX) -
			(m_EndY - m_StartY)*(m_EndY - m_StartY));
	}
	//operators
	friend std::ofstream& operator<<(std::ofstream& FileStream, const Line& _Line);
	friend std::ostream& operator<<(std::ostream& OutputStream, const Line& _Line);

	//other stuff 
	void Print()const override { std::cout << *this; }
	void Translate(double PointX, double PointY) override;

};

