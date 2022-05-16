#include <iostream>
#include <set>
#include <vector>
using namespace std;
int main()
{
	int x;
	set <int> s1;
	set <int> s2;
	set <int> s3;
	while (cin >> x)
	{
		if (s1.count(x) == 1)
		{
			if (s2.count(x) == 1)
			{
				s3.insert(x);
			}
			s2.insert(x);
		}
		s1.insert(x);
	}
	set <int>::iterator i;
	for (i = s2.begin(); i != s2.end(); ++i)
	{
		if (s3.count(*i) == 0)
		{
			cout << *i << " ";
		}
	}
	cout << endl;
	return EXIT_SUCCESS;
}