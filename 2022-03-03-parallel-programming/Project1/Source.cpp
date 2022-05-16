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


int primeNumbersParallel(int n)
{
	int count = 0;
	if (n == 2)
		count = 1;

	int border = ((n ^ (3 / 2) + 1) / 2) ^ (2 / 3);
	if (border % 2 == 0)
	{
		border++;
	}

#pragma omp parallel sections reduction(+:count)
	{
#pragma omp section
		{
			for (int i = 3; i < border; i += 2)
			{
				if (prime(i))
				{
					count++;
				}
			}
		}
#pragma omp section
		{
			for (int i = border; i <= n; i += 2
				)
			{
				if (prime(i))
				{
					count++;
				}
			}
		}
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

	cout << primeNumbersParallel(n) << endl;

	cout << "Parallel Time: " << omp_get_wtime() - t << endl;


	return EXIT_SUCCESS;
}