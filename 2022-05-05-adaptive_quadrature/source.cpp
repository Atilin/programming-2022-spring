#include <iostream>
#include <omp.h>
#include <cmath>
#include <cstdlib>

using namespace std;

double f(double x)
{
	return 1 / (1 + x * x);
}

double integr(double (*f)(double), double A, double B)
{
	double ans = 0;
	for (int i = 0; i < 10; ++i)
	{
		ans += (f(A + ((B - A) / 10) * i) + f(A + ((B - A) / 10) * (i + 1))) / 2 * (B - A) / 10;
	}
	return ans;
}

double integral_lin(double (*f)(double), double A, double B)
{
	double full = integr(f, A, B);
	double left = integr(f, A, (A + B) / 2);
	double right = integr(f, (A + B) / 2, B);
	double ans = full - (left + right);

	if (-1e-10 < ans && ans < 1e-10)
	{
		return full;
	}
	return integral_lin(f, A, (A + B) / 2) + integral_lin(f, (A + B) / 2, B);
}

double integral_par(double (*f)(double), double A, double B, bool flag = true)
{
	double full = integr(f, A, B);
	double left = integr(f, A, (A + B) / 2);
	double right = integr(f, (A + B) / 2, B);
	double ans = full - (left + right);

	if (-1e-10 < ans && ans < 1e-10)
	{
		return full;
	}
	double a = 0;
	double b = 0;
	if (flag)
	{
#pragma omp parallel
		{
#pragma omp single
			{
#pragma omp task
				a = integral_par(f, A, (A + B) / 2, false);

#pragma omp task
				b = integral_par(f, (A + B) / 2, B, false);
			}
		}
	}
	else
	{
		a = integral_lin(f, A, (A + B) / 2);
		b = integral_lin(f, (A + B) / 2, B);
	}
	return a + b;
}

int main()
{
	double t = omp_get_wtime();
	cout << integral_lin(f, 0, 1) << endl;
	cout << "Time linear:" << omp_get_wtime() - t << endl << endl;

	t = omp_get_wtime();
	cout << integral_par(f, 0, 1) << endl;
	cout << "Time parallel:" << omp_get_wtime() - t << endl;

	return 0;
}