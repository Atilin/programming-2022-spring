#include<iostream>
#include<future>

using namespace std;

double f(double x)
{
	return 1 / (1 + x * x);
}
double pi(int n, int a, int b)
{
	double sum = 0;
	for (int i = a; i <= b; ++i)
	{
		sum += f((2.0 * i - 1) / (2.0 * n));
	}
	return 4 * sum / n;
}

int main()
{
	future<double> f1 = async(pi, 9999999, 1, 9999999 / 2);
	future<double> f2 = async(pi, 9999999, 9999999 / 2 + 1, 9999999);
	cout << f1.get() + f2.get();
	return 0;
}