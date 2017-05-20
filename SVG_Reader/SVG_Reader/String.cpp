#include "stdafx.h"
#include "String.h"
#include<cstring>
#include<iostream>

String::String()
{
	m_Beginning = nullptr;
	m_Length = 0;
}

String::String(const String& _String)
{
	m_Length = _String.Length();
	m_Beginning=new char[m_Length];
	for (int i = 0; i < m_Length; ++i)
	{
		m_Beginning[i] = _String[i];
	}
}

String::String(const char* _String)
{
	m_Length = strlen(_String);
	m_Beginning = new char[m_Length];
	for (int i=0; i<m_Length; ++i)
	{
		m_Beginning[i] = _String[i];
	}
}

String::~String()
{
	delete[] m_Beginning;
}

String& String::operator=(const String& _String)
{
	Clear();
	m_Length = _String.Length();
	m_Beginning = new char[m_Length];
	for (int i = 0; i<m_Length; ++i)
	{
		m_Beginning[i] = _String[i];
	}
	return *this;
}

String String::operator+(const String& _String)const
{
	String NewString(*this);
	NewString += _String;
	return NewString;
}

String& String::operator+=(const String& _String)
{
	String Temp(*this);
	Clear();
	m_Beginning = new char[Temp.Length() + _String.Length()];
	for (int i = 0; i < Temp.Length(); ++i)
	{
		m_Beginning[i] = Temp[i];
	}
	m_Length = Temp.Length();
	for (int i = 0; i < _String.Length(); ++i)
	{
		m_Beginning[m_Length + i] = _String[i];
	}
	m_Length += _String.Length();
	return *this;
}

const char& String::operator[](int _Index)const
{
	return m_Beginning[_Index];
}

char& String::operator[](int _Index)
{
	return m_Beginning[_Index];
}


void String::Append(const String& _String)
{
	*this += _String;
}

String String::Concatenate(const String& _String) const
{
	return (*this + _String);
}

void String::Clear()
{
	delete[] m_Beginning;
	m_Beginning = nullptr;
	m_Length = 0;
}

std::ostream & operator<<(std::ostream & os, const String & _String)
{
	for (int i = 0; i < _String.m_Length; ++i)
	{
		os << _String.m_Beginning[i];
	}
	return os;
}
