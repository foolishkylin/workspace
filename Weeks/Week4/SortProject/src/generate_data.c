#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ini()
{
    srand(time(NULL));
    FILE *fp = fopen("data.txt","w+");
    if (fp == NULL) return;
	for(int i = 0; i < 1e5; i++)
		fprintf(fp, "%d ", rand());
}

int main()
{
    ini();
	return 0;
}
