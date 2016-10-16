#include <stdio.h>
#include <stdlib.h>
#include "position.h"

/*Troca os valores a e b*/
void swap (int *a, int *b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

void print_array(int v[], int n){
	int i;
	for (i = 0; i < n; i++) {
		if (i == 0) printf("[%d, ", v[i]);
		else if (i == n-1) printf("%d]\n", v[i]);
		else printf("%d, ", v[i]);
	}
}

/*Recebe um vetor de tamanho n e verifica se ele está ordenado.
Retorna 1 se não está ordenada, e zero caso esteja.*/
int check_sort(int v[], int n){
	int i;
	for (i = 0; i < n-1; i++)
		if (v[i] > v[i+1]) return 1;
	return 0;
}

/*Essa função é usada para checar se é possível ou não ordenar um vetor.
Basicamente a função percorre o vetor uma vez, aplica a três reversão onde
necessário, se após isso não estiver ordenado e o tamanho do vetor for um 
par (explicado melhor no relatório), ele imprime uma mensagem dizendo que não 
é possivel, e atribui -1 ao indice do vetor resultado, isso funciona como uma 
flag na função three_reverse, ignorando assim a ordenação.*/
void check_position (int v[], int n, pos *result) {
	int i, c;
	for (i = 0; i < n-2; i ++) {
		if (v[i] > v[i+2]) {
			swap (&v[i], &v[i+2]);
			add_pos (result, i);
		}
	}

	c = check_sort(v, n);
	if (n%2 == 0 && c) {
		printf("Nao e possivel.\n");
		result->i = -1;
	}
	printf(" check_position:");
	print_array (v, n);
}

/*Essa função inverte dois valores adjacentes num vetor usando apenas a três
reversão. Recebe um vetor de tamanho n, e troca v[i] com v[i+1] aplicando
três reversão.*/
void correct_position(int v[],int n, int i, pos *result) {
	int left, right, j;
	printf("correct_position: ");
	print_array (v, n);
	left = n/2;
	right = (n/2) - 1;
	while (left) {
		i = (i-2)%n;
		if (i < 0) {
			i += n;
		} 
		swap (&v[i%n], &v[(i+2)%n]);
		add_pos (result, i%n);
		left--;
	}
	j = (i+2)%n;
	while (right) {
		swap (&v[j%n], &v[(j+2)%n]);
		add_pos	(result, j%n);
		j = (j+2)%n;
		right--;
	}
	print_array (v, n);
}

/*Ordena um vetor, se possível, usando apenas o movimento três reversão
Recebe como parâmetro apenas o vetor e seu tamanho.*/
void three_reverse (int v[], int n) {
	int i = 0;
	pos *result;

	result = create_pos (n);

	check_position (v, n, result);

	if (result->i != -1) {
		while (check_sort(v, n)) {
			if (i%n < n-2){
				if (v[i%n] > v[(i+2)%n]){
					swap (&v[i%n], &v[(i+2)%n]);
					add_pos (result, i%n);
				}
				else if (v[i%n] > v[(i+1)%n]){
					correct_position (v, n, i%n, result);
					}
			}
			else if (i%n == n-2 && v[i%n] > v[(i+1)%n]) {
				correct_position (v, n, i%n, result);
			}
			i++;
		}
		for (i = 0; i < result->i; i++) {
			printf ("%d\n", result->v[i]);
		}

	}

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


	printf("Vetor ordenado: ");
	print_array (v, n);
	free (v);
	return 0;
}