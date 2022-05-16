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
	double n;
	cin >> n;

	double phi = 0;

	double t = omp_get_wtime();

	for (int i=0; i <= n; ++i)
	{
		arr[i] = sin(phi+i*PI/(2*n));
	}
	cout << "Usual Time: " << omp_get_wtime() - t << endl;

	//for (int i = 0; i <= n; ++i)
	//{
	//	cout << arr[i] << ' ';
	//}
	//cout << endl << endl;

	t = omp_get_wtime();

#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < n/2; ++i)
			{
				arr[i] = sin(phi + i * PI / (2 * n));
			}
		}
#pragma omp section
		{
			for (int i = n/2; i <= n; ++i)
			{
				arr[i] = sin(phi + i * PI / (2 * n));
			}
		}
	}
	cout << "Parallel Time: " << omp_get_wtime() - t << endl;
	/*for (int i = 0; i <= n; ++i)
	{
		cout << arr[i] << ' ';
	}*/
	cout << endl;
	return EXIT_SUCCESS;
}