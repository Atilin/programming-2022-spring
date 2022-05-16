#include <iostream>
#include <set>
using namespace std;
int main()
{
	int x;
	set <int> s;
	while (cin >> x)
	{
		s.insert(x);
	}
	set <int>::iterator i;
	for (i = s.begin(); i != s.end(); ++i)
		cout << *i << " ";
	cout << endl;
	return EXIT_SUCCESS;
}