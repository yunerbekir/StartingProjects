#pragma once
#include"stdafx.h"
#include<iostream>
#include<fstream>
#include<string>
#include "Shape.h"
#include"Line.h"

class Rectangle :public Shape
{
private:
	double m_StartingPointX, m_StartingPointY;
	double m_Height, m_Width;
public:
	//constructors
	Rectangle() { m_StartingPointX = m_StartingPointX = m_Height = m_Width = 0; }
	Rectangle(const double,const double,const double,const double,std::string); // Setting the rectangle
	Rectangle(std::string);
	
	//get methods
	double GetStartX()const { return m_StartingPointX; }
	double GetStartY()const { return m_StartingPointY; }
	double GetHeight()const { return m_Height; };
	double GetWidth()const { return m_Width; };
	double GetArea()const override;
	Line GetFirstDiagonal();
	Line GetSecondDiagonal();
	
	//output operators
	friend std::ofstream& operator<<(std::ofstream& FileStream, const Rectangle& _Rectangle);
	friend std::ostream& operator<<(std::ostream& os, const Rectangle& _Rectangle);

	//other methods
	void Print()const override { std::cout << *this; }
	void Translate(double PointX, double PointY) override;
	void SetCorrectPossition(); // If the rectangle is out of bounds
								// This method displays a message of the
								// problem field and changes it to 0 for the center
								// finds the module for width and heigth
};

