// SVG_Reader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<iostream>
#include<vector>
#include<fstream>
#include<String>
#include<cmath>
#include<stdlib.h>

#include "Shape.h"
#include "Line.h"
#include "Circle.h"
#include "Rectangle.h"



void Help();
void OpenFileAndLoadToMemory(std::string& _Directory);
std::string GetFileName(std::string& _Directory);
void AddElementToCorrectVector(std::string& _LineOfText);
void CloseFile();
void SaveFile(std::string);
void SaveFileAs(std::string Directory);
void ExitProgram();
void PrintAllVectors();
void Erase(unsigned int);
void Translate(double PointX = 0, double PointY = 0, unsigned  int Figure = 0);

//Within
void Within(std::string Figure);
void WithinCircle(Circle);
void WithinRectangle(Rectangle);

//std::string FormatString(std::string); // format is "<number>" ... "<color>"
//int PossitionOfFirstNumber(std::string _LineOfText, unsigned int _Possition = 0);
//int PossitionOfFirstLetter(std::string _LineOftext, unsigned int _Possition = 0);
std::string GetShapeName(std::string);

// Contains in Rectangle
bool PointInRectangle(Rectangle, double, double);
bool LineInRectangle(Rectangle, Line);
bool CircleInRectangle(Rectangle, Circle);
bool RectangleInRectangle(Rectangle, Rectangle);

//Contains in circle
bool PointInCircle(Circle, double, double);
bool LineInCircle(Circle, Line);
bool RectangleInCircle(Circle, Rectangle);
bool CircleInCircle(Circle, Circle);




// all figures are stored in diferent vectors, and the figures are displayed and worked with
// in the order Lines -> Circles -> Rectangles
std::vector<Line> VectorOfLines;
std::vector<Circle> VectorOfCircles;
std::vector<Rectangle> VectorOfRectangles;
unsigned int ShapesCount = 0;


/*int main()
{
	Circle k(5, 5, 4, "black");
	std::cout << PointInCircle(k, 0, 5);
	std::cout << PointInCircle(k, 6, 5);
}*/



int main()
{
	bool flag = true;
	std::string Command;
	while (flag)
	{

		std::cout << "Type >help for help.\n";
		std::getline(std::cin, Command);
		if (Command.substr(0, 4) == ">cls") system("cls");
		else if (Command.substr(0,5) == ">help") Help();
		else if (Command.substr(0, 5) == ">exit") break;
		else if (Command.substr(0, 5) == ">open")
		{
			OpenFileAndLoadToMemory(Command.substr(6));
			std::string FileName = GetFileName(Command.substr(6));
			std::string FileDirectory = Command.substr(PossitionOfFirstLetter(Command, 6));
			std::cout << FileName << " has been opened successfully.\n";
			while (true)
			{
				std::getline(std::cin, Command);
				if (Command.substr(0, 6) == ">close")
				{
					CloseFile();
					std::cout << FileName << " has been closed successfully.\n";
					break;
				}
				else if (Command.substr(0, 7) == ">saveas")
				{
					SaveFileAs(Command.substr(PossitionOfFirstLetter(Command, 7)));
					std::cout << GetFileName(Command.substr(PossitionOfFirstLetter(Command, 8))) << " has been saved successfully.\n";
				}
				else if (Command.substr(0, 5) == ">save")
				{
					SaveFile(FileDirectory);
					std::cout << FileName << " has been saved successfuln.\n";
				}
				else if ((Command.substr(0, 5)) == ">exit")
				{
					ExitProgram();
					flag = false;
					break;
				}
				else if ((Command.substr(0, 6) == ">print"))
				{
					PrintAllVectors();
				}
				else if ((Command.substr(0, 6)) == ">erase")
				{
					int Number = std::stoi(Command.substr(PossitionOfFirstNumber(Command, 7), Command.find_first_of(' ', 8)));
					Erase(Number);
				}
				else if ((Command.substr(0, 7) == ">create"))
				{
					AddElementToCorrectVector(FormatString(Command.substr(8)));
					std::cout << GetShapeName(Command.substr(8)) << "(" << ShapesCount << ") has been created successfuly.\n";
				}
				else if ((Command.substr(0, 10)) == ">translate")
				{
					int NumberPossition = PossitionOfFirstNumber(Command, 6); // finding the possition of the first number
					int IntervalPossition = Command.find_first_of(' ', NumberPossition); // finding the interval after that number
					double PointX = std::stod(Command.substr(NumberPossition, IntervalPossition)); // converting the number to double

					NumberPossition = PossitionOfFirstNumber(Command, IntervalPossition); // PossitionSecondNum= the number after the white space after the first number
					IntervalPossition = Command.find_first_of(' ', NumberPossition); // and so on
					double PointY = std::stod(Command.substr(NumberPossition, IntervalPossition));

					Command.push_back(' '); // adding one just in case

					int FigureNumber = 0;
					NumberPossition = PossitionOfFirstNumber(Command, IntervalPossition);
					if (NumberPossition != -1)
					{
						IntervalPossition = Command.find_first_of(' ', NumberPossition);
						FigureNumber = std::stoi(Command.substr(NumberPossition, IntervalPossition));
					}
					Translate(PointX, PointY, FigureNumber);
				}
				else if (Command.substr(0, 7) == ">within")
				{
					Within(Command.substr(8));
				}
				else if (Command.substr(0, 5) == ">help") Help();
			}
		}
	}
}

// this will display out all commands that are accepted from the application
void Help()
{
	system("cls");
	std::cout << "This application accepts the following commands:\n";
	std::fstream file;
	file.open("help.txt", std::ios::in);
	std::string k;
	while (!file.eof())
	{
		std::getline(file, k);
		std::cout <<k<<"\n";
		if (file.eof()) break;
	}
	file.close();
}

// opens file and loads it
void OpenFileAndLoadToMemory(std::string& _Directory)
{
	std::fstream File;
	File.open(_Directory, std::ios::in | std::ios::out); //trying to open the file
	if (!File.is_open())  // if the file is not oppened then it doesn't exist
	{
		std::cout << _Directory << "\n";
		std::cerr << "File doesn't exist creating...\n";
		File.open(_Directory, std::ios::out); // and so it creates that file.
	}
	else // if the file exists then we read from it
	{
		std::string LineOfText;
		// I use this so that I can skip the first few lines of text
		do
		{
			std::getline(File, LineOfText);
		} while (LineOfText != "<svg>"); // my aim is to reach the part where the the figures information is stored
		do
		{
			std::getline(File, LineOfText); // we read line by line
			AddElementToCorrectVector(LineOfText); // and then add it to the correct vector

		} while (LineOfText != "</svg>"); // we do that till the end of the figure list
	}
	File.close();
}

std::string GetFileName(std::string& _Directory)
{
	int Pos = _Directory.find_last_of('\\'); // this skips sub-folders and finds the possition of the file we need
	std::string k = _Directory.substr(Pos + 1); 
	if (k == "") // if we didn't have a path and just a file name, this part takes care of that
	{
		k = _Directory.substr(PossitionOfFirstLetter(_Directory)); 
	}
	return k;
}

void AddElementToCorrectVector(std::string& _LineOfText)
{
	if (_LineOfText.find("<line") != std::string::npos)
	{
		VectorOfLines.push_back(Line(_LineOfText));
		++ShapesCount;
	}
	else if (_LineOfText.find("<circle") != std::string::npos)
	{
		VectorOfCircles.push_back(Circle(_LineOfText));
		++ShapesCount;
	}
	else if (_LineOfText.find("<rect") != std::string::npos)
	{
		VectorOfRectangles.push_back(Rectangle(_LineOfText));
		++ShapesCount;
	}
}

void CloseFile()
{
	VectorOfCircles.clear();
	VectorOfLines.clear();
	VectorOfRectangles.clear();
	ShapesCount = 0;
}

void SaveFile(std::string FileDirectory)
{
	// adding the first few lines of text to the file
	std::ofstream File;
	File.open(FileDirectory, std::ios::out);
	File << "< ? xml version = \"1.0\" standalone = \"no\" ? >\n";
	File << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\n";
	File << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n";
	File << "<svg>\n";
	// adding the figures currently in memory
	for (unsigned int i = 0; i < VectorOfLines.size(); ++i)
	{
		File << VectorOfLines[i] << "\n";
	}
	for (unsigned int i = 0; i < VectorOfCircles.size(); ++i)
	{
		File << VectorOfCircles[i] << "\n";
	}
	for (unsigned int i = 0; i < VectorOfRectangles.size(); ++i)
	{
		File << VectorOfRectangles[i] << "\n";
	}
	File << "</svg>\n";
}

// saves current figures in the memory to the desired location
void SaveFileAs(std::string Directory)
{
	std::fstream File1;
	File1.open(Directory, std::ios::out);
	SaveFile(Directory);
	File1.close();
}

void ExitProgram()
{
	std::cerr << "Exiting the program...";
}

// displays all figures to the console
void PrintAllVectors()
{
	if (!ShapesCount)
	{
		std::cout << "No shapes have been loaded to memory.\n";
		return;
	}
	unsigned int Count = 1;
	for (unsigned int i = 0; i < VectorOfLines.size(); ++i, ++Count)
	{
		std::cout << Count << " " << VectorOfLines[i] << "\n";
	}
	for (unsigned int i = 0; i < VectorOfCircles.size(); ++i, ++Count)
	{
		std::cout << Count << " " << VectorOfCircles[i] << "\n";
	}
	for (unsigned int i = 0; i < VectorOfRectangles.size(); ++i, ++Count)
	{
		std::cout << Count << " " << VectorOfRectangles[i] << "\n";
	}
}

// erases a figure
void Erase(unsigned int _ElementPossition)
{
	if (_ElementPossition > ShapesCount) std::cout << "There is no figure number " << _ElementPossition << "!\n";
	if (VectorOfLines.size() >= _ElementPossition)
	{
		VectorOfLines.erase(VectorOfLines.begin() + _ElementPossition - 1);
		std::cout << "Erased a line" << "(" << _ElementPossition << ").\n";
		return;
	}
	else _ElementPossition -= VectorOfLines.size();
	if (VectorOfCircles.size() >= _ElementPossition)
	{
		VectorOfCircles.erase(VectorOfCircles.begin() + _ElementPossition - 1);
		std::cout << "Erased a circle" << "(" << _ElementPossition + VectorOfLines.size() << ").\n";
		return;
	}
	else _ElementPossition -= VectorOfCircles.size();
	if (VectorOfRectangles.size() >= _ElementPossition)
	{
		VectorOfRectangles.erase(VectorOfRectangles.begin() + _ElementPossition - 1);
		std::cout << "Erased a rectangle" << "(" << _ElementPossition + VectorOfCircles.size() + VectorOfLines.size() << ").\n";
	}
}

//translates a figure
void Translate(double PointX, double PointY, unsigned int Figure)
{
	if (Figure > ShapesCount) std::cout << "There is no figure number " << Figure << "!\n";
	else if (Figure == 0)
	{
		for (unsigned int i = 0; i < VectorOfLines.size(); ++i)
		{
			VectorOfLines[i].Translate(PointX, PointY);
		}
		for (unsigned int i = 0; i < VectorOfCircles.size(); ++i)
		{
			VectorOfCircles[i].Translate(PointX, PointY);
		}
		for (unsigned int i = 0; i < VectorOfRectangles.size(); ++i)
		{
			VectorOfRectangles[i].Translate(PointX, PointY);
		}
		std::cout << "Translated all figures.\n";
	}
	else if (VectorOfLines.size() >= Figure)
	{
		VectorOfLines[Figure - 1].Translate(PointX, PointY);
		std::cout << "Translated figure " << "(" << Figure << ").\n";
	}
	else if (VectorOfLines.size() + VectorOfCircles.size() >= Figure)
	{
		VectorOfCircles[Figure - 1 - VectorOfLines.size()].Translate(PointX, PointY);
		std::cout << "Translated figure " << "(" << Figure << ").\n";
	}
	else if (VectorOfLines.size() + VectorOfCircles.size() + VectorOfRectangles.size() >= Figure)
	{
		VectorOfCircles[Figure - 1 - VectorOfCircles.size() - VectorOfLines.size()].Translate(PointX, PointY);
		std::cout << "Translated figure " << "(" << Figure << ").\n";
	}
}

// displays figures within a given figure
void Within(std::string Figure)
{
	Figure += " \"black\"";
	if (Figure.find("rectangle") != std::string::npos)
	{
		Rectangle k(Figure);
		WithinRectangle(k);
	}
	if (Figure.find("circle") != std::string::npos)
	{
		Circle k(Figure);
		WithinCircle(k);
	}
}


// displays figures within a circle
void WithinCircle(Circle _Circle)
{
	int FigureNumber = 0;
	// parsing the vector that contains the Lines
	for (unsigned int i = 0; i < VectorOfLines.size(); ++i)
	{
		++FigureNumber;
		if (LineInCircle(_Circle, VectorOfLines[i]))
		{
			std::cout << FigureNumber << ". " << VectorOfLines[i] << "\n";
		}
	}
	// parsing the vector that contains the Circles
	for (unsigned int i = 0; i < VectorOfCircles.size(); ++i)
	{
		++FigureNumber;
		if (CircleInCircle(_Circle, VectorOfCircles[i]))
		{
			std::cout << FigureNumber << ". " << VectorOfCircles[i] << "\n";
		}
	}
	// parsing the vector that contains the Rectangles
	for (unsigned int i = 0; i < VectorOfRectangles.size(); ++i)
	{
		++FigureNumber;
		if (RectangleInCircle(_Circle, VectorOfRectangles[i]))
		{
			std::cout << FigureNumber << ". " << VectorOfRectangles[i] << "\n";
		}
	}
}

// displays figures that are cointained in the inputed rectangle
void WithinRectangle(Rectangle _Rectangle)
{
	int FigureNumber = VectorOfCircles.size() + VectorOfLines.size();
	for (unsigned int i = 0; i < VectorOfLines.size(); ++i)
	{
		++FigureNumber;
		if (LineInRectangle(_Rectangle, VectorOfLines[i]))
		{
			std::cout << FigureNumber << ". " << VectorOfLines[i] << "\n";
		}
	}
	for (unsigned int i = 0; i < VectorOfCircles.size(); ++i)
	{
		++FigureNumber;
		if (CircleInRectangle(_Rectangle, VectorOfCircles[i]))
		{
			std::cout << FigureNumber << ". " << VectorOfCircles[i] << "\n";
		}
	}
	for (unsigned int i = 0; i < VectorOfRectangles.size(); ++i)
	{
		++FigureNumber;
		if (RectangleInRectangle(_Rectangle, VectorOfRectangles[i]))
		{
			std::cout << FigureNumber << ". " << VectorOfRectangles[i] << "\n";
		}
	}
}



/*std::string FormatString(std::string _LineOfText) // format is "<number>" ... "<color>"
{
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
}*/

/*int PossitionOfFirstNumber(std::string _LineOfText, unsigned int _Possition)
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
}*/

// returns the name of a shape
std::string GetShapeName(std::string _LineOfText)
{
	if (_LineOfText.find("line") != std::string::npos) return "Line";
	else if (_LineOfText.find("circle") != std::string::npos) return "Circle";
	else if (_LineOfText.find("rectangle") != std::string::npos) return "Rectangle";
	else return "Not a valid Figure";
}

// tells whether a point is in a rectangle
bool PointInRectangle(Rectangle _Rectangle, double PointX, double PointY)
{
	bool FirstPart = (PointX <= _Rectangle.GetStartX() && PointX >= _Rectangle.GetStartX() - _Rectangle.GetWidth() ||
		PointX >= _Rectangle.GetStartX() && PointX <= _Rectangle.GetWidth() - _Rectangle.GetStartX());
	bool SecondPart = (PointY <= _Rectangle.GetStartY() && PointY >= _Rectangle.GetStartY() - _Rectangle.GetWidth() ||
		PointY >= _Rectangle.GetStartY() && PointY <= _Rectangle.GetWidth() - _Rectangle.GetStartY());
	return (FirstPart&&SecondPart);
}

// tells whether a line is in a rectangle
bool LineInRectangle(Rectangle _Rectangle, Line _Line)
{
	bool FirstPart = PointInRectangle(_Rectangle, _Line.GetStartX(), _Line.GetStartY());
	bool SecondPart = PointInRectangle(_Rectangle, _Line.GetEndX(), _Line.GetEndY());
	return (FirstPart&&SecondPart);
}

//tells whether a rectangle is in a rectangle
bool RectangleInRectangle(Rectangle ToCheckIn, Rectangle ToCheck)
{
	Line FirstDiagonal = ToCheck.GetFirstDiagonal();
	Line SecondDiagonal = ToCheck.GetSecondDiagonal();
	bool FirstPart = LineInRectangle(ToCheckIn, FirstDiagonal);
	bool SecondPart = LineInRectangle(ToCheckIn, SecondDiagonal);
	return (FirstPart&&SecondPart);
}

//tells whether a circle is in a rectangle
bool CircleInRectangle(Rectangle _Rectangle, Circle _Circle)
{
	Line OyLine(_Circle.GetCenterX(), _Circle.GetCenterY() - _Circle.GetRadius(), _Circle.GetCenterX(), _Circle.GetCenterY() + _Circle.GetRadius(), "N\\A");
	Line OxLine(_Circle.GetCenterX() - _Circle.GetRadius(), _Circle.GetCenterY(), _Circle.GetCenterX() + _Circle.GetRadius(), _Circle.GetCenterY(), "N\\A");
	bool FirstPart = LineInRectangle(_Rectangle, OyLine);
	bool SecondPart = LineInRectangle(_Rectangle, OxLine);
	return (FirstPart&&SecondPart);
}

// tells whether a point is in a circle, we find the distance between the point and the center of the circle
// then we compare it to the radius
bool PointInCircle(Circle _Circle, double PointX, double PointY)
{
	double DistancePointCenter = sqrt((_Circle.GetCenterX() - PointX)*(_Circle.GetCenterX() - PointX) +
		(_Circle.GetCenterY() - PointY)*(_Circle.GetCenterY() - PointY));
	if (_Circle.GetRadius() >= DistancePointCenter) return true;
	else return false;
}
// tells us whether a line is in a circle
bool LineInCircle(Circle _Circle, Line _Line)
{
	bool FirstPart = PointInCircle(_Circle, _Line.GetStartX(), _Line.GetStartY());
	bool SecondPart = PointInCircle(_Circle, _Line.GetEndX(), _Line.GetEndY());
	return (FirstPart&&SecondPart);
}
// tells us wheter a rectangle is in a circle
bool RectangleInCircle(Circle _Circle, Rectangle _Rectangle)
{
	Line FirstDiagonal = _Rectangle.GetFirstDiagonal();
	Line SecondDiagonal = _Rectangle.GetSecondDiagonal();
	bool FirstPart = LineInCircle(_Circle, FirstDiagonal);
	bool SecondPart = LineInCircle(_Circle, SecondDiagonal);
	return (FirstPart&&SecondPart);
}
//tells us wheter a circle is in a circle
bool CircleInCircle(Circle ToCheckIn, Circle ToChek)
{
	double DistanceBetweeenCenters = sqrt((ToCheckIn.GetCenterX() - ToChek.GetCenterX())*(ToCheckIn.GetCenterX() - ToChek.GetCenterX()) +
		(ToCheckIn.GetCenterY() - ToChek.GetCenterY())*(ToCheckIn.GetCenterY() - ToChek.GetCenterY()));
	if (ToCheckIn.GetRadius() >= DistanceBetweeenCenters + ToChek.GetRadius()) return 1;
	else return 0;
}