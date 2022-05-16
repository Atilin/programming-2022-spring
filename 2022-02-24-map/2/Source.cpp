#include <iostream>
#include <map>
using namespace std;

map<int, int> makeMap()
{
	map <int, int> M;
	int numberOfPairs;
	cin >> numberOfPairs;
	for (int i = 0; i < numberOfPairs; ++i)
	{
		int key = 0;
		cin >> key;
		int data = 0;
		cin >> data;
		M[key] = data;
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
	map <int, int> M;
	M = makeMap();
	print(M);

	return EXIT_SUCCESS;
}