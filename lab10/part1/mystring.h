#ifndef __MYSTRING_H__
#define __MYSTRING_H__

using namespace std;

#include <iostream>

class MyString {

    public:

	// default constructor
	MyString();

	// constructor
	MyString(const char* p);

	// destructor
	~MyString();

	// copy constructor 
	MyString(const MyString& s);

	// assignment operator
	MyString& operator=(const MyString& s);

	// returns the length of the string
	int length() const { return len; }
	
	// operator+
	friend MyString operator+(const MyString& s1, const MyString& s2);

	MyString& operator+=(const MyString& s2);
	// put-to operator
	friend ostream& operator<<(ostream& os, const MyString& s);

	// get-from operator
	friend istream& operator>>(istream& is, MyString& s);

	// operator[]
	char& operator[](int i);

	// operator[] const
	const char& operator[](int i) const;

	//testing if the string is empty
	bool operator!() const;

	//test equality of strings

	//for when String object is not on the lhs
	friend bool operator==(const MyString& lhs, const MyString& rhs);

	//test if one string is greater than the other
	//for when String object is not on the lhs
	friend bool operator<(const MyString& lhs, const MyString& rhs);

	//test if strings are unequal
	//test is string literal and string object are not equal
	friend bool operator!=(const MyString& lhs, const MyString& rhs)
	{
		//const MyString temp = p;
		return !(lhs.data == rhs.data);
	}

	//test if string literal is greater than string objectt
	friend bool operator>(const MyString& lhs, const MyString& rhs);
/*	{
		//const MyString temp = p;
		return (rhs.data < lhs.data);
	}*/

	//test is string literal is <= string object
	friend bool operator<=(const MyString& lhs, const MyString& rhs);

	//test is string literal is >= string object
	friend bool operator>=(const MyString& lhs, const MyString& rhs);
/*	{
		//const MyString temp = p;
		return (rhs.data <= lhs.data);
	}*/

    private:

	char* data;

	int len;
};

#endif
