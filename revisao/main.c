#include <stdlib.h>
void print_board(int **board);
int solveur(int **board, int row, int col);
int solveur_check_row(int **board, int row, int col);
int solveur_check_col(int **board, int row, int col);
int *check_argv(char *arg);
int check_row(int *row);
int check_col(int **board, int column);
int is_safe(int **board, int val, int row, int col);
int **initialize_board(int *vals);
void free_board(int **board);
void ft_putchar(char c);
void ft_putstr(char *str);
void error(void);
int *error_null(void);


int main(int argc, char **argv)
{
	int **board;
	int *views;
	int result;

	if (argc != 2) // erro se não são dois argumentos
	{
		error();
		return (0);
	}
	views = check_argv(argv[1]); // checagem se parametro condiz com esperado
	if (views == NULL)
		return (0);
	board = initialize_board(views); //cria espaço e preenche as bordar com os pontos de vista
	result = solveur(board, 1, 1); // começa em [1][1] e usa a própria função usa recursão até chegar em [4][4]
	if (board == NULL || result == 0) // se não existe solução retorna erro
	{
		error();
		return (0);
	}
	print_board(board); //imprime solução, se houver
	free_board(board); // libera espaço ocupado pela matriz 5x5
	free(views); // libera espaço ocupado pela matriz de parâmetros
	return (0);
}