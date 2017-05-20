#include "stdafx.h"

#include "Shape.h"

double ExtractAndConvert(std::string _LineOfText, int &StartingPos)
{
	std::string Value = "";
	for (; _LineOfText[StartingPos] != '"'; ++StartingPos)
	{
		Value += _LineOfText[StartingPos];
	}
	return std::stod(Value);
}

double Mod(double Number)
{
	if (Number < 0) return Number*(-1);
	return Number;
}

std::string FormatString(std::string _LineOfText) // format is "<number>" ... "<color>"
{
	if (_LineOfText.find("/n") == std::string::npos) return _LineOfText;
	int InsertionPossition = 0;
	_LineOfText.insert(PossitionOfFirstLetter(_LineOfText), "<");
	while (true)
	{
		InsertionPossition = PossitionOfFirstNumber(_LineOfText, InsertionPossition); // finding the numbers and putting "
		if (InsertionPossition == -1) break;										// before and afther them
		_LineOfText.insert(InsertionPossition, "\"");
		InsertionPossition = _LineOfText.find(" ", InsertionPossition);
		_LineOfText.insert(InsertionPossition, "\"");
	}
	InsertionPossition = PossitionOfFirstNumber(_LineOfText); // skipping the shape name
	InsertionPossition = PossitionOfFirstLetter(_LineOfText, InsertionPossition); // finding the color possition
	_LineOfText.insert(InsertionPossition, "\"");
	_LineOfText += " "; // adding " " at the end of the string just in case
	InsertionPossition = InsertionPossition = _LineOfText.find(" ", InsertionPossition);
	_LineOfText.insert(InsertionPossition, "\""); // doing the same thing as with the numbers
	return _LineOfText;
}

int PossitionOfFirstNumber(std::string _LineOfText, unsigned int _Possition)
{
	for (unsigned int i = _Possition; i < _LineOfText.length(); ++i)
	{
		if (_LineOfText[i] >= '0'&&_LineOfText[i] <= '9')
		{
			return i;	// returns i when a number has been found
		}
	}
	return -1; // returns -1 when a number hasn't been found
}
int PossitionOfFirstLetter(std::string _LineOfText, unsigned int _Possition)
{
	for (unsigned int i = _Possition; i < _LineOfText.length(); ++i)
	{
		if (_LineOfText[i] >= 'a'&&_LineOfText[i] <= 'z' || _LineOfText[i] >= 'A'&&_LineOfText[i] <= 'Z')
		{
			return i;	// returns i when a letter has been found
		}
	}
	return -1; // returns -1 when a letter hasn't been found
}