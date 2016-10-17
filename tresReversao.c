/*
Nome: Victor Martins João
Nº USP: 9793551
*/

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
    int i, k, c, s = 0;
    for (k = n-2; k >= 0; k -= 2){
        for (i = 0; i < k; i ++) {
            if (v[i] > v[i+2]) {
                swap (&v[i], &v[i+2]);
                add_pos (result, i);
                s++;
            }
        }
    }

    c = check_sort(v, n);
    if (n%2 == 0 && c) {
        printf("Nao e possivel.\n");
        result->i = -1;
    }
}

/*Essa função inverte dois valores adjacentes num vetor usando apenas a três
reversão. Recebe um vetor de tamanho n, e troca v[i] com v[i+1] aplicando
três reversão.*/
void correct_position(int v[],int n, int i, pos *result) {
    int left, right, j;

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
        add_pos (result, j%n);
        j = (j+2)%n;
        right--;
    }
}

/*Ordena um vetor, se possível, usando apenas o movimento três reversão
Recebe como parâmetro apenas o vetor e seu tamanho.*/
void three_reverse (int v[], int n) {
    int i = 0, s = 0;
    pos *result;

    result = create_pos (n);

    check_position (v, n, result);

    if (result->i != -1) {
        while (check_sort(v, n)) {
            s++;
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

    free (v);
    return 0;
}