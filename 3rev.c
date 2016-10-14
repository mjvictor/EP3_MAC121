#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int *v;
	int i;
}pos;


void intercalate (int ini, int mid, int end, int v[]){
	int *w, i, j, k = 0;
	w = malloc ((end - ini) * sizeof(int));

	for (i = ini, j = mid; i < mid && j < end;) {
		if (v[i] > v[j]) {
			w[k] = v[j];
			k++; j++;
		}
		else {
			w[k] = v[i];
			k++; i++;
		}
	}

	while (i < mid) {
		w[k] = v[i];
		k++; i++;
	} 
	while (j < end) {
		w[k] = v[j];
		k++; j++;
	}

	for (i = ini; i < end; i++) v[i] = w[i - ini]; 
 	free (w);
}

void mergesort (int ini, int end, int v[]) {
	if (ini < (end - 1)) {
		int mid = (ini + end)/2;
		mergesort (ini, mid, v);
		mergesort (mid, end, v);
		intercalate (ini , mid, end, v);
	}
}

int *duplicate_array (int v[], int n) {
	int *w, i;
	w = malloc (n * sizeof(int));
	for (i = 0; i < n; i++) w[i] = v[i];
	return w;
}

pos *create_pos(int max){
	pos *pos;
	pos = malloc (sizeof (pos));
	pos->v = malloc (max * sizeof(int));
	pos->i = 0;
	return pos;
}

void destroy_pos (pos *p) {
	free (p->v);
	p->v = NULL;
	free (p);
}


void troca (int *a, int *b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

int find (int v[], int n, int x) {
	int i;
	for (i = 0; i < n; i++) {
		if (v[i] == x) {
			return i;
		}
	}
}

void correct_position (pos *even, pos *odd, int v[], int n, pos *result) {
	int x, y, i, j;
	while (even->i >= 0){
		printf ("SHIT!\n");
		x = even->v[even->i];
		printf ("HOLY!\n");
		y = odd->v[odd->i];
		printf ("SHIT!\n");
		i = find(v, n, x);
		j = find(v, n, y);
		while (i <= n-1){
			printf ("HOLY!\n");
			troca (&v[i], &v[i+2]);
			result->v[result->i] = i;
			result->i++;
			i += 2;
		}		
		while (j >= 1){
			printf ("BURGER!\n");
			troca (&v[j], &v[j-2]);
			result->v[result->i] = j-2;
			result->i++;
			j -= 2;
		}
		troca(&v[i], &v[j]);
		result->v[result->i] = i;
		result->i++;
		even->i--;
		odd->i--;
	}
}

void check_position (int v[], int n, pos *result){
	int *w, i, j, k = 0, l = 0;
	pos *even, *odd;
	
	even = create_pos ((n/2) + 1);
	odd = create_pos ((n/2) + 1);
	w = duplicate_array (v, n);
	mergesort (0, n, w);
	for (i = 0; i < n; i++){
		j = find (w, n, v[i]);
		if (i%2 != j%2) 
			if (i%2 == 0){
				even->v[even->i] = v[i];
				even->i++;
			}
			else {
				odd->v[odd->i] = v[i];
				odd->i++;
			}
	}
	if (n%2) {
		if (even->i) correct_position (even, odd, v, n,result);
	}
	else {
		if(even->i) {
			printf("Nao e possivel.\n");
			result->i = -1;
		}
	}
	destroy_pos (even);
	destroy_pos (odd);	
}

int check_sort(int v[], int n){
	int i;
	for (i = 0; i < n-1; i++)
		if (v[i] > v[i+1]) return 1;
	return 0;
}

void three_reverse (int v[], int n){
	int flag = 1, count = 0, i = 0, j, tmp, aux;
	pos *result;
	result = create_pos (1000);
	check_position (v, n, result);
	if (result->i != -1){
		while (check_sort(v, n)) {
			if (i%n < n-2){
				if (v[i%n] > v[(i+1)%n] || v[i%n] > v[(i+2)%n]){
					troca(&v[i%n], &v[(i+2)%n]);
					result->v[result->i] = i%n;
					result->i++;
					printf ("i = %d  -> ", i%n);
					for (j = 0; j < n; j++) {
						if (j == 0) printf("[%d, ", v[j]);
						else if (j == n-1) printf("%d]\n", v[j]);
						else printf("%d, ", v[j]);
					}
				}
			}
			else if (i%n == n-2){
				if (v[i%n] > v[(i+1)%n] || v[i%n] < v[(i+2)%n]){
					troca(&v[i%n], &v[(i+2)%n]);
					result->v[result->i] = i%n;
					result->i++;
					printf ("i = %d  -> ", i%n);
					for (j = 0; j < n; j++) {
						if (j == 0) printf("[%d, ", v[j]);
						else if (j == n-1) printf("%d]\n", v[j]);
						else printf("%d, ", v[j]);
					}
				}
			}
			else {
				if (v[i%n] < v[(i+1)%n] || v[i%n] < v[(i+2)%n]){
					troca(&v[i%n], &v[(i+2)%n]);
					result->v[result->i] = i%n;
					result->i++;
					printf ("i = %d  -> ", i%n);
					for (j = 0; j < n; j++) {
						if (j == 0) printf("[%d, ", v[j]);
						else if (j == n-1) printf("%d]\n", v[j]);
						else printf("%d, ", v[j]);
					}
				}
			}
			i++;
		}
	}

	/*
	for (i = 0; i < result->i; i++){
		printf ("%d| ", result->v[i]);
	}*/
	destroy_pos (result);
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