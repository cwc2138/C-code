#include <cstring>
#include <cstdio>

#include "mystring.h"

// default constructor

MyString::MyString() 
{
/*#ifdef BASIC4TRACE
    fprintf(stderr, "BASIC4TRACE: (%p)->MyString()\n", this);
#endif*/

    data = new char[1];
    data[0] = '\0';
    
    len = 0;
}

// constructor

MyString::MyString(const char* p)
{
/*#ifdef BASIC4TRACE
    fprintf(stderr, "BASIC4TRACE: (%p)->MyString(const char *)\n", this);
#endif*/

    if (p) {
	len = strlen(p);
	data = new char[len+1];
	strcpy(data, p);
    } else {
	data = new char[1];
	data[0] = '\0';
	len = 0;
    }
}

// destructor

MyString::~MyString() 
{
/*#ifdef BASIC4TRACE
    fprintf(stderr, "BASIC4TRACE: (%p)->~MyString()\n", this);
#endif*/

    delete[] data;
}

// copy constructor 

MyString::MyString(const MyString& s) 
{
/*#ifdef BASIC4TRACE
    fprintf(stderr, "BASIC4TRACE: (%p)->MyString(const MyString&)\n", this);
#endif*/

    len = s.len;
    
    data = new char[len+1];
    strcpy(data, s.data);
}

// assignment operator

MyString& MyString::operator=(const MyString& rhs)
{
/*#ifdef BASIC4TRACE
    fprintf(stderr, "BASIC4TRACE: (%p)->op=(const MyString&)\n", this);
#endif*/

    if (this == &rhs) {
	return *this;
    }

    // first, deallocate memory that 'this' used to hold

    delete[] data;

    // now copy from rhs
    
    len = rhs.len;

    data = new char[len+1];
    strcpy(data, rhs.data);

    return *this;
}

// operator+

MyString operator+(const MyString& s1, const MyString& s2)
{
/*#ifdef BASIC4TRACE
    fprintf(stderr, 
	    "BASIC4TRACE: op+(const MyString&, const MyString&)\n");
#endif*/

    MyString temp;
//    delete [] temp.data;
	temp = s1;
	temp += s2;

	return temp;
}

MyString& MyString::operator+=(const MyString& s2)
{
	size_t newLen = len + s2.len;
	char* temp = new char[newLen + 1];

	strcpy(temp, data);
	strcpy(temp + len, s2.data);
	delete [] data;
	data = temp;
	len = newLen;
	return *this;
}

ostream& operator<<(ostream& os, const MyString& s)
{
    os << s.data;
    return os;
}

// get-from operator

istream& operator>>(istream& is, MyString& s)
{
    // this is kinda cheating, but this is just to illustrate how this
    // function can work.
    
    string temp;
    is >> temp;

    delete[] s.data;

    s.len = strlen(temp.c_str());
    s.data = new char[s.len+1];
    strcpy(s.data, temp.c_str());

    return is;
}

// operator[] - in real life this function should be declared inline

char& MyString::operator[](int i) 
{
    return data[i];
}

// operator[] const - in real life this should be inline

const char& MyString::operator[](int i) const
{
    // illustration of casting away constness
    return ((MyString&)*this)[i];
}

//testing if the string is empty
bool MyString::operator!() const
{
	return len == 0;
}
	
//test equality of strings
bool operator==(const MyString& lhs, const MyString& rhs)
{
	return strcmp(lhs.data, rhs.data) == 0;
}

//test if one string is greater
bool operator>(const MyString& lhs, const MyString& rhs)
{
	return (strcmp(lhs.data, rhs.data) > 0);
}

//test if one string is lesser
bool operator<(const MyString& lhs, const MyString& rhs)
{
	return (strcmp(lhs.data, rhs.data) < 0);
}

//test if one string is lesser or equal
bool operator<=(const MyString& lhs, const MyString& rhs)
{
	return (strcmp(lhs.data, rhs.data) <= 0);
}

//test if one string is greater or equal
bool operator>=(const MyString& lhs, const MyString& rhs)
{
	return (strcmp(lhs.data, rhs.data) >= 0);
}
