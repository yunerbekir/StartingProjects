#pragma once

#include "stdafx.h"

#include <string>

#include "String.h"
#include<iostream>


double ExtractAndConvert(std::string _LineOfText, int &StartingPos);
double Mod(double Number);
int PossitionOfFirstNumber(std::string _LineOfText, unsigned int _Possition = 0);
int PossitionOfFirstLetter(std::string _LineOftext, unsigned int _Possition = 0);
std::string FormatString(std::string _LineOfText);

class Shape    // This is the Parent class
{
private:
	std::string m_Color;

protected:
	void SetColor(std::string& _Color){m_Color = _Color;}
public:
	std::string GetColor()const { return m_Color; };
	Shape() { m_Color = "N\\A"; }
	virtual void Print()const = 0;
	virtual void Translate(double, double) = 0;
	virtual double GetArea()const = 0;

};


