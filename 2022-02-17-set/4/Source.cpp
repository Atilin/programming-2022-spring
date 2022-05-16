#include <iostream>
#include <set>
using namespace std;

template <typename T>
set <T> unification(set<T> s1, set<T> s2)
{
	set <T> s3;
	typename set <T>::iterator i;
	for (i = s1.begin(); i != s1.end(); ++i)
	{
		s3.insert(*i);
	}
	for (i = s2.begin(); i != s2.end(); ++i)
	{
		s3.insert(*i);
	}
	return s3;
}

int main()
{
	set <int> s1;
	s1.insert(1);
	s1.insert(2);
	set <int> s2;
	s2.insert(3);
	s2.insert(4);
	set <int> s3;
	s3 = unification(s1, s2);

	set <int>::iterator i;
	for (i = s3.begin(); i != s3.end(); ++i)
		cout << *i << " ";
	cout << endl;

	return EXIT_SUCCESS;
}