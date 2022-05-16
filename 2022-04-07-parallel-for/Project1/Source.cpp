#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>

using namespace std;

bool prime(int n)
{
	if (n == 1) return false;
	if (n % 2 == 0 && n != 2) // отдельно проверим делимость на 2
		return false;
	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return false;
	// выход из функции, как только нашли делитель
	return true; // цикл закончился, делителей не нашлось
}

int primeNumbersUsual(int n)
{
	int count = 0;
	if (n == 2)
		count = 1;

	for (int i = 3; i <= n; i += 2)
	{
		if (prime(i) == true)
		{
			count++;
		}
	}
	return count;
}


int primeNumbersStatic(int n)
{
	int count = 0;
	if (n >= 2)
		count = 1;

#pragma omp parallel for schedule (static) reduction (+: count)
	for (int i = 3; i <= n; i += 2)
		if (prime(i))
		{
			count++;
		}
	return count;
}


int primeNumbersDynamic(int n)
{
	int count = 0;
	if (n >= 2)
		count = 1;

#pragma omp parallel for schedule (dynamic, 5) reduction (+: count)
	for (int i = 3; i <= n; i += 2)
		if (prime(i))
		{
			count++;
		}
	return count;
}


int primeNumbersGuided(int n)
{
	int count = 0;
	if (n >= 2)
		count = 1;

#pragma omp parallel for schedule (guided, 5) reduction (+: count)
	for (int i = 3; i <= n; i += 2)
		if (prime(i))
		{
			count++;
		}
	return count;
}

int main()
{
	int n;
	cin >> n;

	double t = omp_get_wtime();

	cout << primeNumbersUsual(n) << endl;

	cout << "Usual Time: " << omp_get_wtime() - t << endl;


	t = omp_get_wtime();

	cout << primeNumbersStatic(n) << endl;

	cout << "Static Time: " << omp_get_wtime() - t << endl;


	t = omp_get_wtime();

	cout << primeNumbersDynamic(n) << endl;

	cout << "Dynamic Time: " << omp_get_wtime() - t << endl;


	t = omp_get_wtime();

	cout << primeNumbersGuided(n) << endl;

	cout << "Guided Time: " << omp_get_wtime() - t << endl;



	return EXIT_SUCCESS;
}