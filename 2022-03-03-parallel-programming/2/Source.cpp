#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>

using namespace std;

int main()
{
	double n;
	cin >> n;

	double pi = 0;

	double t = omp_get_wtime();

	for (int i = 1; i <= n; ++i)
	{
		pi += 16 * n / (4 * n * n + 4 * i * i - 4 * i + 1);
	}
	cout << "Usual Time: " << omp_get_wtime() - t << endl;
	cout << "PI: " << pi << endl;



	pi = 0;

	t = omp_get_wtime();

#pragma omp parallel sections reduction(+:pi)
	{
#pragma omp section
		{
			for (int i = 1; i < n/2; ++i)
			{	
				pi += 16 * n / (4 * n * n + 4 * i * i - 4 * i + 1);
			}
		}
#pragma omp section
		{
			for (int i = n/2; i <= n; ++i)
			{
				pi += 16 * n / (4 * n * n + 4 * i * i - 4 * i + 1);
			}
		}
	}
	cout << "Parallel Time: " << omp_get_wtime() - t << endl;
	cout << "PI: " << pi << endl;


	return EXIT_SUCCESS;
}