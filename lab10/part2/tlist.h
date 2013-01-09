#ifndef _TLIST_H_
#define _TLIST_H

using namespace std;
#include <list>
#include <iostream>

template <typename T>
class TList;
template <typename T>
TList<T> operator+(const TList<T>& lhs , const TList<T>& rhs);
template <typename T>
ostream& operator<<(ostream& os, const TList<T>& rhs);

template <typename T>
class TList
{
	public:

	//TList();

        //destructor
        //~TList();

        //copy constructor
        //StrList(const T& t);

        //assignment operator
        //TList operator=(const TList<T>& rhs);

        int isEmpty() const { return l.isEmpty(); }

        int size() const;

	void addFront(const T& t);

        T popFront();

        void reverse(){l.reverse();}

        TList operator+=(const TList<T>& rhs);
	
	friend ostream& operator<< <T>(ostream& os, const TList<T>& rhs);

        T& operator[](int i);
	
	const T& operator[](int i)const
        {
                return ((TList<T>&)*this)[i];
        };

	private:

		list<T> l;
};

template <typename T>
int TList<T>::size() const
{
	return l.size();
}

template <typename T>
void TList<T>::addFront(const T& t)
{
	l.push_front(t);
}

template <typename T>
T TList<T>::popFront()
{
	T t = l.front();
	l.pop_front();
	return t;
}

template <typename T>
TList<T> TList<T>::operator+=(const TList<T>& rhs)
{
	reverse();
	typename list<T>::const_iterator i;
        for(i = rhs.l.begin(); i != rhs.l.end(); i++){
                l.push_front(*i);
        }
	reverse();
	return *this;
}

template <typename T>
TList<T> operator+(const TList<T>& lhs,const TList<T>& rhs)
{
	TList<T> t(lhs);
	t += rhs;
	return t;
}

template <typename T>
ostream& operator<<(ostream& os, const TList<T>& rhs)
{
	os << "{ ";
        //struct List list = l.list;
  	typename list<T>::const_iterator i;
	for(i = rhs.l.begin(); i != rhs.l.end(); i++){
        	os << *i << " ";
        	
	}
        os << "}";
        return os;
}

template <typename T>
T& TList<T>::operator[](int i)
{
	typename list<T>::iterator it;        
	it = l.begin();
	for(int counter = 0; counter < i; counter++)
        {
		++it;
                
        }
        return *it;

	
}
#endif
