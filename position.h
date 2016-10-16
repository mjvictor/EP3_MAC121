/*Definir a variável e as operações para um tipo pos.*/
#ifndef __POSITION_H__
#define __POSITION_H__

/*Nessa struct o vetor v guardará os índices dos movimentos
três Reversão, o i será o índice atual desse vetor e max o 
tamanho do vetor.*/
typedef struct {
	int *v;
	int i;
	int max;
}pos;

/*Inicializa uma variável do tipo pos. Recebe como parâmetro
o tamanho inicial.*/
pos *create_pos(int max);

/*Libera os valores alocados para a variável do tipo pos.*/
void destroy_pos (pos *p);

/*Adiciona um elemento no vetor v da variável pos. Recebe como
parâmetro uma variável pos e um inteiro x, que será adicionado.*/
void add_pos (pos *pos, int x);

/*Realoca o vetor da variável do tipo pos, caso chegue ao seu 
limite.*/
void reallocate_pos(pos *pos);

#endif