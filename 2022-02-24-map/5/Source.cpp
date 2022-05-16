#include <iostream>
#include <map>
#include <set>
using namespace std;

template <class T1, class T2, class T3>

map<T1, T3> compositionOfFunctions(map<T1, T2> M1, map<T2, T3> M2)
{
	map <T1, T3> M;
	typename map <T1, T2>::iterator i;
	for (i = M1.begin(); i != M1.end(); i++)
	{
		M[i->first] = M2[M1[i->first]];
	}
	return M;
}

void print(map<int, int> M)
{
	map <int, int>::iterator i;
	for (i = M.begin(); i != M.end(); i++)
		cout << i->first << " -> " << i->second << endl;
}

int main()
{
	map<int, int> M1 = { {1, 2}, {2, 3}, {3, 4}, {4, 5} };
	map<int, int> M2 = { {2, 3}, {3, 4}, {4, 5}, {5, 6} };

	map<int, int> M;
	M = compositionOfFunctions(M1, M2);

	print(M1);
	cout << endl;
	print(M2);
	cout << endl;
	print(M);

	return EXIT_SUCCESS;
}