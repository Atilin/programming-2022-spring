#include <iostream>
#include <map>
using namespace std;

void countNumber()
{
	int x;
	map <int, int> M;
	while (cin >> x)
	{
		if (!M.count(x))
		{
			M[x] = 1;
		}
		else
		{
			M[x]++;
		}
	}
	map <int, int>::iterator i;
	for (i = M.begin(); i != M.end(); i++)
	{
		cout << i->first << " -> " << i->second << endl;
	}
}

int main()
{
	countNumber();

	return EXIT_SUCCESS;
}