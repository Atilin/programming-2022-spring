#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>

using namespace std;

int main()
{
	int n;
	cin >> n;

	double pi = 0;
	double t = omp_get_wtime();

	for (int i = 1; i <= n; ++i)
	{
		pi += 16.0 * n / (4.0 * n * n + 4.0 * i * i - 4 * i + 1);
	}
	cout << "Usual Time: " << omp_get_wtime() - t << endl;
	cout << "PI: " << pi << endl;



	pi = 0;
	t = omp_get_wtime();

#pragma omp parallel for schedule (static) reduction (+: pi)
	for (int i = 0; i < n; i++)
		pi = pi + 16.0 * n / (4.0 * n * n + 4.0 * i * i - 4 * i + 1);
	cout << "Static Time: " << omp_get_wtime() - t << endl;
	cout << "PI: " << pi << endl;

	pi = 0;
	t = omp_get_wtime();

#pragma omp parallel for schedule (dynamic, 5) reduction (+: pi)
	for (int i = 0; i < n; i++)
		pi = pi + 16.0 * n / (4.0 * n * n + 4.0 * i * i - 4 * i + 1);
	cout << "Dynamic Time: " << omp_get_wtime() - t << endl;
	cout << "PI: " << pi << endl;

	pi = 0;
	t = omp_get_wtime();

#pragma omp parallel for schedule (guided, 5) reduction (+: pi)
	for (int i = 0; i < n; i++)
		pi = pi + 16.0 * n / (4.0 * n * n + 4.0 * i * i - 4 * i + 1);
	cout << "Guided Time: " << omp_get_wtime() - t << endl;
	cout << "PI: " << pi << endl;


	return EXIT_SUCCESS;
}