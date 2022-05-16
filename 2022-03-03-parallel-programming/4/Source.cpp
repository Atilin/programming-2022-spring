#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>
#include <vector>

using namespace std;

struct Point
{
	int x;
	int y;
	int z;
};

vector <Point> dots;

double dist(Point a, Point b)
{
	return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}

double stream2(vector <Point> dots)
{
	int n = dots.size();
	double maxDist = 0;

	double maxDist1 = 0;
	double maxDist2 = 0;


	double t = omp_get_wtime();

#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < n / sqrt(2); ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					double d = dist(dots[i], dots[j]);
					if (d > maxDist1)
						maxDist1 = d;
				}
			}
		}
#pragma omp section
		{
			for (int i = n / sqrt(2); i < n; ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					double d = dist(dots[i], dots[j]);
					if (d > maxDist2)
						maxDist2 = d;
				}
			}
		}
	}
	maxDist = max(maxDist1, maxDist2);
	cout << "Time: " << omp_get_wtime() - t << endl;
	return sqrt(maxDist);
}

double stream3(vector <Point> dots)
{
	int n = dots.size();
	double maxDist = 0;

	double maxDist1 = 0;
	double maxDist2 = 0;
	double maxDist3 = 0;

	double t = omp_get_wtime();

#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < n / sqrt(3); ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					double d = dist(dots[i], dots[j]);
					if (d > maxDist1)
						maxDist1 = d;
				}
			}
		}
#pragma omp section
		{
			for (int i = n / sqrt(3); i < n * sqrt(2 / 3); ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					double d = dist(dots[i], dots[j]);
					if (d > maxDist2)
						maxDist2 = d;
				}
			}
		}
#pragma omp section
		{
			for (int i = n * sqrt(2 / 3); i < n; ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					double d = dist(dots[i], dots[j]);
					if (d > maxDist3)
						maxDist3 = d;
				}
			}
		}


	}
	maxDist = max(max(maxDist1, maxDist2), maxDist3);
	cout << "Time: " << omp_get_wtime() - t << endl;
	return sqrt(maxDist);
}

double stream4(vector <Point> dots)
{
	int n = dots.size();
	double maxDist = 0;

	double maxDist1 = 0;
	double maxDist2 = 0;
	double maxDist3 = 0;
	double maxDist4 = 0;



	double t = omp_get_wtime();

#pragma omp parallel sections
	{
#pragma omp section
		{
			for (int i = 0; i < n / 2; ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					double d = dist(dots[i], dots[j]);
					if (d > maxDist1)
						maxDist1 = d;
				}
			}
		}
#pragma omp section
		{
			for (int i = n / 2; i < n / sqrt(2); ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					double d = dist(dots[i], dots[j]);
					if (d > maxDist2)
						maxDist2 = d;
				}
			}
		}
#pragma omp section
		{
			for (int i = n / sqrt(2); i < sqrt(3) * n / 2; ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					double d = dist(dots[i], dots[j]);
					if (d > maxDist3)
						maxDist3 = d;
				}
			}
		}
#pragma omp section
		{
			for (int i = sqrt(3) * n / 2; i < n; ++i)
			{
				for (int j = 0; j < i; ++j)
				{
					double d = dist(dots[i], dots[j]);
					if (d > maxDist4)
						maxDist4 = d;
				}
			}
		}

	}
	maxDist = max(max(max(maxDist1, maxDist2), maxDist3), maxDist4);
	cout << "Time: " << omp_get_wtime() - t << endl;
	return sqrt(maxDist);
}


int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		Point p;
		int x;
		cin >> x;
		p.x = x;
		int y;
		cin >> y;
		p.y = y;
		int z;
		cin >> z;
		p.z = z;

		dots.push_back(p);
	}

	cout << stream2(dots) << endl;
	cout << stream3(dots) << endl;
	cout << stream4(dots) << endl;

	return EXIT_SUCCESS;
}