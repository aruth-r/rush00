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

	if (argc != 2)
	{
		error();
		return (0);
	}
	views = check_argv(argv[1]); // verifica se os argumentos passados são válidos.
	if (views == NULL)
		return (0);
	board = initialize_board(views);
	result = solveur(board, 1, 1); // começa em [1][1] e usa recursão até chegar em [4][4]
	if (board == NULL || result == 0)
	{
		error();
		return (0);
	}
	print_board(board);
	free_board(board);
	free(views);
	return (0);
} //Retorna uma matriz bidimensional dinâmica com alturas de torre. Se a torre estiver inacabada, então a altura * é igual a zero. Se a matriz não for mais necessária, ela deve ser removida com a função free ().
