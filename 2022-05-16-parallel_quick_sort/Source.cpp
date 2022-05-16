#include <iostream>
#include <omp.h>
#include<cmath>
#include<cstdlib>

using namespace std;

const int n=1000;

int partition (int a[n], int l, int r)
{
    int i = l-1, j = r;
    int v = a[r];
    while (true)
    {
        while (a[++i] < v);
        while (v < a[--j])
        {
            if (j == l)
            {
                break;
            }
        }
        if (i >= j)
        {
            break;
        }
        swap(a[i], a[j]);
    }
    swap(a[i], a[r]);
    return i;
}

void qsort (int a[n], int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int i = partition(a, l, r);
    qsort(a, l, i - 1);
    qsort(a, i+1, r);
}

void qsort_par (int a[n], int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int i = partition(a, l, r);
      #pragma omp parallel
        {
        #pragma omp single
        {
            #pragma omp task
            qsort(a, l, i - 1);
            #pragma omp task
            qsort(a, i+1, r);
            #pragma omp taskwait
        }
        }
}

int main()
{
    int a[n];
    for (int & x : a)
    x = rand() % 100;

    int b[n];
    for (int i=0;i<n;++i)
    {
        b[i]=a[i];
    }

    double t = omp_get_wtime();
    qsort(a, 0, n-1);
    cout << "Time lin:" << omp_get_wtime() - t <<endl;
    for (int x : a)
    cout << x << " ";
    cout << endl<<endl;

    t = omp_get_wtime();
    qsort_par(b, 0, n-1);
    cout << "Time par:" << omp_get_wtime() - t <<endl;
    for (int x : b)
    cout << x << " ";
    cout << endl;

    return EXIT_SUCCESS;
}
