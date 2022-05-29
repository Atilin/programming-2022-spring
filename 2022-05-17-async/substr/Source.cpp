#include <iostream>
#include <vector>
#include <string>
#include <future>
#include <chrono>

using namespace std;

const int n = 10000;

void fill_string(string& s)
{
	char symbols[62] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z', 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z', '0','1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for (int i = 0; i < 10000; ++i)
	{
		s.push_back(symbols[rand() % 62]);
	}
}

int block_size(int threads)
{
	return n / threads + (n % threads ? 1 : 0);
}

int Find(string what, string s, int a, int b)
{
	int count = 0;
	int length = what.size();
	for (int i = a; i < b; ++i)
	{
		if (s.substr(i, length) == what)
			++count;
	}
	return count;
}

int Find_thread(string what, string s, int threads, int first_index)
{
	return Find(what, s, first_index, first_index + block_size(threads));
}

int MultiThreadFind(string what, string s, int threads)
{
	vector < future <int> > fut(threads);
	int bl_size = block_size(threads);
	int first_index = 0;
	int i = 0;
	while (first_index < n)
	{
		fut[i] = async(Find_thread, what, s, threads, first_index);
		first_index += bl_size;
		++i;
	}
	int result = 0;
	for (int j = 0; j < threads; ++j)
	{
		result += fut[j].get();
	}
	return result;
}

int main()
{
	string s1;
	fill_string(s1);

	cout << s1 << endl;

	string s2 = "a";
	cout << MultiThreadFind(s2, s1, 8);
	return EXIT_SUCCESS;
}