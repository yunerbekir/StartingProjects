#include "stdafx.h"
#include "Circle.h"

Circle::Circle(double _CenterX = 0, double _CenterY = 0, double _Radius = 0, std::string _Color = (std::string)"N\\A")
{
	m_CenterX = Mod(_CenterX);
	m_CenterY = Mod(_CenterY);
	m_Radius = Mod(_Radius);
	SetColor(_Color);
}


// formating for propper file output
std::ofstream & operator<<(std::ofstream & FileStream, const Circle & _Circle)
{
	//circle cx="5" cy="5" r="10" fill="blue" />
	FileStream << " <circle cx=\"" << _Circle.GetCenterX() << "\" cy=\""
		<< _Circle.GetCenterY() << "\" r=\"" << _Circle.GetRadius()
		<< "\" fill=\"" << _Circle.GetColor() << "\" />";
	return FileStream;
}

// formating for propper output
std::ostream & operator<<(std::ostream & OutputStream, const Circle& _Circle)
{
	OutputStream << "circle " << _Circle.GetCenterX() << " " << _Circle.GetCenterY()
		<< " " << _Circle.GetRadius() << " " << _Circle.GetColor();
	return OutputStream;
}

// extracting information from a stribg
Circle::Circle(std::string _LineOfText)
{
	_LineOfText = FormatString(_LineOfText);
	int MemberStartingPossition = _LineOfText.find("\"") + 1;
	m_CenterX = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"", MemberStartingPossition + 1) + 1;
	m_CenterY = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"", MemberStartingPossition + 1) + 1;
	m_Radius = ExtractAndConvert(_LineOfText, MemberStartingPossition);

	MemberStartingPossition = _LineOfText.find("\"", MemberStartingPossition + 1) + 1;
	int LastComma = _LineOfText.find_last_of("\"");
	ChangeColor(_LineOfText.substr(MemberStartingPossition, LastComma - MemberStartingPossition));
	Print();
	std::cout << "\n";
}

Circle::Circle(const Circle& _Circle)
{
	m_CenterX = _Circle.GetCenterX();
	m_CenterY = _Circle.GetCenterY();
	m_Radius = _Circle.GetRadius();
	SetColor(_Circle.GetColor());
}



// translating the circle
void Circle::Translate(double PointX, double PointY)
{
	m_CenterX = Mod(m_CenterX + PointX);
	m_CenterY = Mod(m_CenterY + PointY);
}
