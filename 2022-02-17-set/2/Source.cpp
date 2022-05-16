#include <iostream>
#include <set>
#include <vector>
using namespace std;
int main()
{
	int x;
	set <int> s;
	set <int> output;
	while (cin >> x)
	{
		if (s.count(x) == 1)
		{
			output.insert(x);
		}
		s.insert(x);
	}
	set <int>::iterator i;
	for (i = output.begin(); i != output.end(); ++i)
		cout << *i << " ";
	cout << endl;
	return EXIT_SUCCESS;
}