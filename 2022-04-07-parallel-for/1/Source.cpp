#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <omp.h>

#define PI 3.14159265

using namespace std;

double arr[9999999];

int main()
{
	int n;
	cin >> n;

	double t = omp_get_wtime();

	for (int i = 0; i <= n; ++i)
	{
		arr[i] = sin(i * PI / (2 * n));
	}
	cout << "Usual Time: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();

#pragma omp parallel for schedule (static)
	for (int i = 0; i <= n; ++i)
	{
		arr[i] = sin(i * PI / (2 * n));
	}
	cout << "Static Time: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();

#pragma omp parallel for schedule (dynamic, 5)
	for (int i = 0; i <= n; ++i)
	{
		arr[i] = sin(i * PI / (2 * n));
	}
	cout << "Dynamic Time: " << omp_get_wtime() - t << endl;

	t = omp_get_wtime();

#pragma omp parallel for schedule (guided, 5)
	for (int i = 0; i <= n; ++i)
	{
		arr[i] = sin(i * PI / (2 * n));
	}
	cout << "Guided Time: " << omp_get_wtime() - t << endl;


	cout << endl;
	return EXIT_SUCCESS;
}