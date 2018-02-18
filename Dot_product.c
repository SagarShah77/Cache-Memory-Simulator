#include <stdio.h>

#define N 9

main()
{
    int i, sum=0;
    
    int v1[9] = {0, 1, 1, 4, 2, 6, 8, 1, 8},
	    v2[9] = {2, 3, 3, 6, 4, 8, 0, 3, 0};

    for(i=0;i<=N;i++)
    {
        sum+=(v1[i] * v2[i]);
    }

    printf("\nFINAL DOT PRODUCT OF TWO VECTORS IS: %d",sum);
}
