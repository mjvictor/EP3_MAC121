#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *v;
	int i;
}res;

res *criaRes(int max){
	res *res;
	res = malloc (sizeof (res));
	res->v = malloc (max * sizeof(int));
	res->i = 0;
	return res;
}

void troca (int *a, int *b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int check_sort(int v[], int n){
	int i;
	for (i = 0; i < n-1; i++)
		if (v[i] > v[i+1]) return 1;
	return 0;
}

void three_reverse (int v[], int n){
	int flag = 1, count = 0, i = 0, j, tmp, aux;
	res *result;
	result = criaRes (1000);
	while (i < n*n) {
		if (i%n < n-2){
			if (v[i%n] > v[(i+1)%n] || v[i%n] > v[(i+2)%n]){
				troca(&v[i%n], &v[(i+2)%n]);
				result->v[result->i] = i%n;
				result->i++;
			}
		}
		else if (i%n == n-2){
			if (v[i%n] > v[(i+1)%n] || v[i%n] < v[(i+2)%n]){
				troca(&v[i%n], &v[(i+2)%n]);
				result->v[result->i] = i%n;
				result->i++;
			}
		}
		else {
			if (v[i%n] < v[(i+1)%n] || v[i%n] < v[(i+2)%n]){
				troca(&v[i%n], &v[(i+2)%n]);
				result->v[result->i] = i%n;
				result->i++;
			}
		}
		printf ("i = %d  -> ", i%n);
		for (j = 0; j < n; j++) {
			if (j == 0) printf("[%d, ", v[j]);
			else if (j == n-1) printf("%d]\n", v[j]);
			else printf("%d, ", v[j]);
		}
		i++;
	}
	/*
	for (i = 0; i < result->i; i++){
		printf ("%d| ", result->v[i]);
	}*/
	free (result->v);
}

int main () {
	int *v, n, i;
	scanf("%d", &n);
	v = malloc (n * sizeof(int));
	for (i = 0; i < n; i++) {
		scanf("%d", &v[i]);
	}
	three_reverse (v, n);
	for (i = 0; i < n; i++) {
		if (i == 0) printf("[%d, ", v[i]);
		else if (i == n-1) printf("%d]\n", v[i]);
		else printf("%d, ", v[i]);
	}
	free (v);
	return 0;
}