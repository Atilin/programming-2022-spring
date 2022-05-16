#include <iostream>
#include <cstdlib>
#include <cmath>
#include <omp.h>
#include <vector>

using namespace std;

struct Point
{
	double x;
	double y;
	double z;
};

vector <Point> dots;

double dist(Point a, Point b)
{
	return ((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + (a.z - b.z) * (a.z - b.z));
}


double Usual(vector <Point> dots)
{
	int n = dots.size();
	double maxDist = 0;

	double t = omp_get_wtime();

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			double d = dist(dots[i], dots[j]);
			if (d > maxDist)
				maxDist = d;
		}
	}
	cout << "Time: " << omp_get_wtime() - t << endl;
	return sqrt(maxDist);
}


double Static(vector <Point> dots)
{
	int n = dots.size();
	double maxDist = 0;

	double t = omp_get_wtime();

#pragma omp parallel for schedule (static) reduction (max: maxDist)
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			double d = dist(dots[i], dots[j]);
			if (d > maxDist)
				maxDist = d;
		}
	}
	cout << "Time: " << omp_get_wtime() - t << endl;
	return sqrt(maxDist);
}


double Dynamic(vector <Point> dots)
{
	int n = dots.size();
	double maxDist = 0;

	double t = omp_get_wtime();

#pragma omp parallel for schedule (dynamic, 5) reduction (max: maxDist)
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			double d = dist(dots[i], dots[j]);
			if (d > maxDist)
				maxDist = d;
		}
	}
	cout << "Time: " << omp_get_wtime() - t << endl;
	return sqrt(maxDist);
}


double Guided(vector <Point> dots)
{
	int n = dots.size();
	double maxDist = 0;

	double t = omp_get_wtime();

#pragma omp parallel for schedule (guided, 5) reduction (max: maxDist)
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			double d = dist(dots[i], dots[j]);
			if (d > maxDist)
				maxDist = d;
		}
	}
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

	cout << Static(dots) << endl;
	cout << Dynamic(dots) << endl;
	cout << Guided(dots) << endl;

	return EXIT_SUCCESS;
}