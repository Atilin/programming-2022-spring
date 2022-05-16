#include <iostream>
#include <map>
#include <set>
using namespace std;

template <class T1, class T2>

map<T1, T2> sumOfFunctions(map<T1, T2> M1, map<T1, T2> M2)
{
	map <T1, T2> M;
	typename map <T1, T2>::iterator i;
	for (i = M1.begin(); i != M1.end(); i++)
	{
		M[i->first] = M1[i->first] + M2[i->first];
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
	map<int, int> M1 = { {1, 40}, {2, 20}, {4, 10},{5, 0} };
	map<int, int> M2 = { {1, 45}, {2, 25}, {4, 15},{5, 5} };

	map<int, int> M;
	M = sumOfFunctions(M1, M2);

	print(M1);
	cout << endl;
	print(M2);
	cout << endl;
	print(M);

	return EXIT_SUCCESS;
}