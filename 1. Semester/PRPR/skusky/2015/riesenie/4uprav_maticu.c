#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 3

int **uprav(int m1[N][N], int k)
{
	int i, j;

	int **m2 = (int **) malloc(N * sizeof(int *));
	int *space = (int *) calloc(N*N, sizeof(int));

	for (i = 0; i < N; ++i)
		m2[i] = space + (i * N);

	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			if (i > j)
				m2[i][j] = k * m1[i][j]; 

	return m2;
}

void vypis(int **m2)
{
	int i, j;
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j)
			printf("%3d", m2[i][j]);
		puts("");
	}
}

int main()
{
	int m1[][N] = {
		{1, 1, 1},
		{2, 2, 2},
		{3, 3, 3}
	};

	int **m2 = uprav(m1, 2);

	vypis(m2);

	return 0;
}
