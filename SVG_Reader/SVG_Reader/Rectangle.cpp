
#include "stdafx.h"
#include "Rectangle.h"

Rectangle::Rectangle(const double _StartingPointX, const double _StartingPointY, const double _Height, const double _Width, std::string _Color)
{
	m_StartingPointX = _StartingPointX;
	m_StartingPointY = _StartingPointY;
	m_Height = _Height;
	m_Width = _Width;
	SetColor(_Color);
	SetCorrectPossition();
}

// parsing a string and getting the desired information
Rectangle::Rectangle(std::string _LineOfText)
{
	_LineOfText = FormatString(_LineOfText);
	int MemberStartingPossition = _LineOfText.find("\"") + 1;
	m_StartingPointX = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"", MemberStartingPossition + 1) + 1;
	m_StartingPointY = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"", MemberStartingPossition + 1) + 1;
	m_Width = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"", MemberStartingPossition + 1) + 1;
	m_Height = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"", MemberStartingPossition + 1) + 1;
	int LastComma = _LineOfText.find_last_of("\"");
	SetColor(_LineOfText.substr(MemberStartingPossition, LastComma - MemberStartingPossition));
}

double Rectangle::GetArea() const
{
	return m_Height*m_Width;
}

// finding the first diagonal
Line Rectangle::GetFirstDiagonal()
{
	return Line(m_StartingPointX, m_StartingPointY, m_StartingPointX + m_Width, m_StartingPointY + m_Height, "N\\A");
}

// finding the second diagonal
Line Rectangle::GetSecondDiagonal()
{
	return Line(m_StartingPointX, m_StartingPointY + m_Height, m_StartingPointX + m_Width, m_StartingPointY, "N\\A");
}

// translating the rectangle
void Rectangle::Translate(double PointX, double PointY)
{
	m_StartingPointX += PointX;
	m_StartingPointY += PointY;
	SetCorrectPossition();
}


// setting the correct possition of the rectangle
void Rectangle::SetCorrectPossition()
{
	if (m_StartingPointX < 0)
	{
		m_StartingPointX = 0;
		std::cerr << "The starting point's Ox Coordinate is invalid.\nAnd has been set to 0";
	}
	if (m_StartingPointY < 0)
	{
		m_StartingPointY = 0;
		std::cerr << "The starting point's Oy Coordinate is invalid.\nAnd has been set to 0";
	}
	if (m_Width < 0)
	{
		m_Width = Mod(m_Width);
		std::cerr << "The width has been multiplied by -1.\n";
		if (m_StartingPointX - m_Width >= 0)
		{
			m_StartingPointX -= m_Width;
			std::cerr << "The Starting point's X coordinate has been normalised.\n";
		}

	}
	if (m_Height < 0)
	{
		m_Height = Mod(m_Height);
		std::cerr << "The heigth has been multiplied by -1.\n";
		if (m_StartingPointY - m_Height >= 0)
		{
			m_StartingPointY -= m_Height;
			std::cerr << "The Starting point's Y coordinate has been normalised.\n";
		}
	}

}


// formating for propper file output
std::ofstream& operator<<(std::ofstream& FileStream, const Rectangle& _Rectangle)
{
	FileStream << " <rect x=\"" << _Rectangle.GetStartX() << "\" y=\""
		<< _Rectangle.GetStartY() << "\" width = \"" << _Rectangle.GetWidth()
		<< "\" height=\"" << _Rectangle.GetHeight() << "\" fill=\""
		<< _Rectangle.GetColor() << "\" />";
	return FileStream;
}


// formating for propper output
std::ostream& operator<<(std::ostream& OutputStream, const Rectangle& _Rectangle)
{
	OutputStream << "rectangle " << _Rectangle.GetStartX() << " " << _Rectangle.GetStartY()
		<< " " << _Rectangle.GetWidth() << " " << _Rectangle.GetHeight() << " "
		<< _Rectangle.GetColor();
	return OutputStream;

}





