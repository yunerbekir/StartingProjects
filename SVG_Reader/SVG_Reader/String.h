#pragma once
#include<iostream>


class String
{
private:
	char* m_Beginning;
	int m_Length;

public:

	// Constructors
	String();
	String(const String&);
	String(const char*);

	// Destructor
	~String();

	// Operations
	String& operator=(const String&);
	String operator+(const String&)const;
	String& operator+=(const String&);
	const char& operator[](int _Index)const;
	char& operator[](int _Index);
	friend std::ostream& operator<<(std::ostream& os, const String& _String);

	

	// Methods
	void Append(const String&);
	String Concatenate(const String&)const;
	int Length()const { return m_Length; };
	void Clear();
};
