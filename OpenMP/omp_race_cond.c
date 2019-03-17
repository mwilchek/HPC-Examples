#include <stdio.h>
#include <omp.h>
int main (void)
{
        int i,j,N;
        N = 512;
        int x[N];
#pragma omp parallel for
        for(i = 0; i < N; i++)
        {
                j = i;
                x[j] = j;
        }
        for(i = 0; i < N; i++)
        {
                if(x[i] != i)
                        printf("Error at %d: x[%d] is %d.\n", i, i, x[i]);
        }
        return 0;
}
