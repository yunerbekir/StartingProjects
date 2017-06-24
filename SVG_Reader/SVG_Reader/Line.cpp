#include"stdafx.h"
#include "Line.h"

Line::Line(double _StartX=0, double _StartY=0, double _EndX=0, double _EndY=0, std::string _Color="N\\A")
{
	m_StartX = _StartX;
	m_StartY = _StartY;
	m_EndX = _EndX;
	m_EndY = _EndY;
	SetColor(_Color);
	SetCorrectPossition();
}

Line::Line(std::string _LineOfText)
{
	_LineOfText = FormatString(_LineOfText);
	int MemberStartingPossition=_LineOfText.find("\"")+1;
	m_StartX = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"", MemberStartingPossition+1)+1;
	m_StartY = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"", MemberStartingPossition+1)+1;
	m_EndX = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"",MemberStartingPossition+1)+1;
	m_EndY = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"", MemberStartingPossition+1)+1;
	int LastComma = _LineOfText.find_last_of("\"");
	SetColor(_LineOfText.substr(MemberStartingPossition,LastComma-MemberStartingPossition));
}

void Line::Translate(double PointX, double PointY)
{
	m_StartX += PointX;
	m_EndX += PointX;
	m_StartY += PointY;
	m_EndY += PointY;
	SetCorrectPossition();
	
}

void Line::SetCorrectPossition()
{
	if (m_StartX < 0)
	{
		std::cerr << "The X of the first point was negative and was multiplied by -1.\n";
		m_StartX = Mod(m_StartX);
	}
	if (m_StartY < 0)
	{
		std::cerr << "The Y of the first point was negative and was multiplied by -1.\n";
		m_StartY = Mod(m_StartY);
	}
	if (m_EndX < 0)
	{
		std::cerr << "The X of the second point was negative and was multiplied by -1.\n";
		m_EndX = Mod(m_EndX);
	}
	if (m_EndY < 0)
	{
		std::cerr << "The Y of the second point was negative and was multiplied by -1.\n";
		m_EndY = Mod(m_EndY);
	}
}




std::ofstream& operator<<(std::ofstream& FileStream, const Line& _Line)
{
	//<rect x = "5" y = "5" width = "10" height = "10" fill = "green" / >
	FileStream << " <line x =\"" << _Line.GetStartX() << "\" y1=\""
		<< _Line.GetStartY() << "\" x2=\"" << _Line.GetEndX() << "\" y2=\""
		<< _Line.GetEndY() << "\" color =\"" << _Line.GetColor() << "\" />";
	return FileStream;
}

std::ostream& operator<<(std::ostream& OutputStream, const Line& _Line)
{
	OutputStream << "line " << _Line.GetStartX() << " " << _Line.GetStartY()
		<< " " << _Line.GetEndX() << " " << _Line.GetEndY()
		<< " " << _Line.GetColor();
	return OutputStream;
}


/*double ExtractAndConvert(std::string _LineOfText, int StartingPos)
{
	std::string Value="";
	for (int i = StartingPos; _LineOfText[i] != '"'; ++i)
	{
		Value += _LineOfText[i];
	}
	return std::stod(Value);
}*/