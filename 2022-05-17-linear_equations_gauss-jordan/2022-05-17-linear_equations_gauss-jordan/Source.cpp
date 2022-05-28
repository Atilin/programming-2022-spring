#include<iostream>
#include<omp.h>
#include<cmath>

using namespace std;

void divide(double** a, int line, int length, double c)
{
	for (int i = 0; i < length; ++i)
	{
		a[line][i] /= c;
	}
}

void subtract(double** a, int line_1, int line_2, int length, double c)
{
	for (int i = 0; i < length; ++i)
	{
		a[line_1][i] -= a[line_2][i] * c;
	}
}

void swap(double* & string, double* & string_max)
{
	double* temp = string;
	string = string_max;
	string_max = temp;
}

int max_string(double** a, int column, int height)
{
	int max = column;
	for (int i = column; i < height; ++i)
	{
		if (abs(a[i][column]) > abs(a[max][column]))
		{
			max = i;
		}
	}
	return max;
}

void transform_lin(double** a, int height, int length)
{
	for (int i = 0; i < length - 1; ++i)
	{
		swap(a[i], a[max_string(a, i, height)]);
		divide(a, i, length, a[i][i]);
		for (int j = 0; j < height; ++j)
		{
			if (j != i)
			{
				subtract(a, j, i, length, a[j][i]);
			}
		}
	}
}

void transform_par(double** a, int height, int length)
{

	for (int i = 0; i < length - 1; ++i)
	{
		swap(a[i], a[max_string(a, i, height)]);
		divide(a, i, length, a[i][i]);
#pragma omp parallel for schedule(static, 5)
		for (int j = 0; j < height; ++j)
		{
			if (j != i)
			{
				subtract(a, j, i, length, a[j][i]);
			}
		}
	}
}

void print(double** a, int height, int length)
{
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < length; ++j)
		{
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}


int main()
{
	int height = 0;
	int length = 0;
	cout << "Number of equations: ";
	cin >> height;
	length = height + 1;
	double** a_lin = new double* [height];
	double** a_par = new double* [height];
	for (int i = 0; i < height; ++i)
	{
		a_lin[i] = new double[length];
		a_par[i] = new double[length];
	}
	cout << "Enter expanded matrix:" << endl;
	for (int i = 0; i < height; ++i)
	{
		for (int j = 0; j < length; ++j)
		{
			cin >> a_lin[i][j];
			a_par[i][j] = a_lin[i][j];
		}
	}

	cout << endl;
	double t = omp_get_wtime();
	transform_lin(a_lin, height, length);
	cout << "Time lin:" << omp_get_wtime() - t << endl;
	print(a_lin, height, length);

	t = omp_get_wtime();
	transform_par(a_lin, height, length);
	cout << "Time parl:" << omp_get_wtime() - t << endl;
	print(a_lin, height, length);


	return EXIT_SUCCESS;
}