// g++ -o barrier barrier.cpp -fopenmp

#include <omp.h>
#include <stdio.h>

int main( )
{
    int a[10];

    #pragma omp parallel num_threads(10)
    {
        int num = omp_get_thread_num();
        a[num] = 0;
    	printf("a[%d] = %d\n", num, a[num]);

        #pragma omp barrier

        a[num] = 1;
        printf("a[%d] = %d\n", num, a[num]);
    }
}
