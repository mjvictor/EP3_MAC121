#include <stdio.h>
#include <stdlib.h>
#include "position.h"


/*Inicializa uma variável do tipo pos. Recebe como parâmetro
o tamanho inicial.*/
pos *create_pos(int max){
	pos *pos;
	pos = malloc (sizeof (pos));
	pos->v = malloc (max * sizeof(int));
	pos->i = 0;
	pos->max = max;
	return pos;
}

/*Libera os valores alocados para a variável do tipo pos.*/
void destroy_pos (pos *p) {
	free (p->v);
	p->v = NULL;
	free (p);
}

/*Adiciona um elemento no vetor v da variável pos. Recebe como
parâmetro uma variável pos e um inteiro x, que será adicionado.*/
void add_pos (pos *pos, int x) {
	if (pos->i == pos->max) reallocate_pos (pos);
	pos->v[pos->i] = x;
	pos->i++;
}

/*Realoca o vetor da variável do tipo pos, caso chegue ao seu 
limite.*/
void reallocate_pos(pos *pos) {
	int *new, i;
	new = malloc ((2*pos->max) * sizeof(int));
	for (i = 0; i < pos->max; i++) {
		new[i] = pos->v[i];
	}
	pos->max *= 2;

	free(pos->v);
	pos->v = new;
}