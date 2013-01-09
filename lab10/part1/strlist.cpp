#include "strlist.h"
//default constructor
StrList::StrList()
{
	initList(&list);
}

//destructor
StrList::~StrList()
{
	while(list.head)
	{
        	MyString *str = (MyString*)::popFront(&list);
        	delete str;
        }
}

//copy constructor
StrList::StrList(const StrList& l)
{
	initList(&list);
	struct Node *node = l.list.head;
	MyString *str;
	while(node){
		str = new MyString(*(MyString*)node->data);
		::addFront(&list, str);
		node = node->next;
	}
	reverse();
}

//assignment operator
StrList& StrList::operator=(const StrList& rhs)
{
	//avoid self-assignment
	if(this == &rhs)
        	return *this;

        while(list.head){
                MyString *str = (MyString*)::popFront(&list);
                delete str;
        }

        //struct List list2 = rhs.list;
        struct Node *node = rhs.list.head;
        MyString *str;
        while(node){
                str = new MyString(*(MyString*)(node->data));
                ::addFront(&list, str);
                node = node->next;
        }
        reverse();
        return *this;
}

//size()
int StrList::size()const
{
	int size = 0;
	struct Node *node = list.head;
	while(node)
	{
		size++;
		node = node->next;
	}
	return size;
}

//addFront
void StrList::addFront(const MyString& str)
{
	MyString *tmp = new MyString(str);
	::addFront(&list, tmp);
}

//popFront
MyString StrList::popFront()
{
	MyString *tmp = (MyString *)(::popFront(&list));
        MyString str(*tmp);
	delete tmp;
	//cout << tmp << endl;
        return str;
}

//operator+=
StrList StrList::operator+=(const StrList& rhs)
{
	reverse();
        //struct List list2 = rhs.list;
        struct Node *node = rhs.list.head;
        while(node){
                MyString *str = new MyString(*(MyString*)(node->data));
                ::addFront(&list, str);
                node = node->next;
        }
        reverse();
        return *this;
}

//operator+
StrList operator+(const StrList& lhs, const StrList& rhs)
{
       StrList tmp(lhs);
       tmp += rhs;
       return tmp;
}

//output
ostream& operator<<(ostream& os, const StrList& l)
{
  	os << "{ ";
        //struct List list = l.list;
        struct Node *node = l.list.head;
        while(node){
        	os << (*(MyString*)node->data) << " ";
                node = node -> next;
        }
        os << "}";
        return os;	
}
i//operator[]
MyString& StrList::operator[](int i)
{
	struct Node *node = list.head;
	//int counter = 0;
	for(int counter = 0; counter < i; counter++)
	{
		node = node->next;
	}
	return (*(MyString*)(node->data));
}
