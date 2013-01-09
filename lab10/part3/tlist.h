#ifndef __TLIST_H__
#define __TLIST_H__

using namespace std;
#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
class TList;
template <typename T>
ostream& operator<<(ostream& os, const TList<T>& rhs);
template <typename T>
TList<T> operator+(const TList<T>& lhs, const TList<T>& rhs);

template <typename T>
class TList{

   public:

	int isEmpty() const
	{
		return v.empty(); 
	};

        int size() const 
	{ 
		return v.size(); 
	};

        void addFront(const T& t);

        T popFront();

        void reverse();

        TList<T> operator+=(const TList<T>& rhs);

        friend ostream& operator<< <T>(ostream& os, const TList<T>& rhs);

        T& operator[](int i);

        const T& operator[](int i) const
	{
		 return ((TList<T>&)*this)[i];
	};

   private:

	vector<T> v;
};

template <typename T>
void TList<T>::addFront(const T& t)
{
	v.insert(v.begin(),t);
}

template <typename T>
T TList<T>::popFront()
{
	T t = v.front();
        v.erase(v.begin());
        return t;
}

template <typename T>
void TList<T>::reverse()
{
	::reverse(v.begin(), v.end());
}

template <typename T>
TList<T> TList<T>::operator+=(const TList<T>& rhs)
{
	v.insert(v.end(), rhs.v.begin(), rhs.v.end());
        return *this;
}

template <typename T>
TList<T> operator+(const TList<T>& lhs, const TList<T>& rhs)
{
        TList<T> tmp(lhs);
        tmp += rhs;
        return tmp;
}

template <typename T>
ostream& operator<< (ostream& os, const TList<T>& rhs)
{
	os << "[ ";
        typename vector<T>::const_iterator it;
        for(it = rhs.v.begin(); it != rhs.v.end(); ++it){
        	os << *it << " ";
        }
        os << "]";
        return os;
}

template <typename T>
T& TList<T>::operator[](int i){
        return v[i];
}
#endif
