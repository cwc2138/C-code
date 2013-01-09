#include <cassert>
#include "mystring.h"

int main()
{
	MyString s1 = "hello";
	MyString s2 = "world";
	//testing ==
	assert(s1 == "hello");
	assert("world" == s2);
	//testing !=
	assert(s1 != s2);
	assert("blah" != s1);
	assert(s1 != "blah");
	//testing <
	assert(s1 < s2);
	assert(s2 < "zzzzzzzzzzzzz");
	assert("he" < s1);
	//testing >
	assert(s2 > s1);
	assert("helloo" > s1);
	assert(s2 > "worl");
	//testing <=
	assert(s1 <= s2);
	assert(s1 <= "helloworld");
	assert(s2 <= "zzzzzzzzzzzzzzzzz");
	//testing >=
	assert(s2 >= s1);
	assert("zzzzzzzzzzzzzzzz" >= s1);

	MyString sp(" ");
	MyString period(".");
	MyString str;

	str += "This" + sp + "should" + sp
	+= "work" + sp + "without"
	+= sp + "any" + sp + "memory"
	+= sp + "leak"
	+= period;

	cout << str << endl;

	return 0;
}

