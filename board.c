# include <stdlib.h>

int **initialize_board(int *vals);
void free_board(int **board);

static void init_columns(int **board, int *vals) // preenche linhas up e down (elementos [0][1] a [0][4] e elementos [5][1] a [5][4])
{
	int i;
	int mode;

	mode = 0;
	while (mode < 2)
	{
		i = 1;
		while (i < 5)
		{
			board[mode * 5][i] = vals[mode * 4 + i - 1];
			i++;
		}
		mode++;
	}
}

static void init_rows(int **board, int *vals) // preenche colunas up e down (elementos [1][0] a [4][0] e elementos [1][5] a [4][5])
{
	int i;
	int mode;

	mode = 0;
	while (mode < 2)
	{
		i = 1;
		while (i < 5)
		{
			board[i][mode * 5] = vals[(mode + 2) * 4 + i - 1];
			i++;
		}
		mode++;
	}
}

int **initialize_board(int *vals)
{
	int i;
	int j;
	int **board;

	i = 0;
	j = 0;
	board = malloc(sizeof(*board) * 6); //recebe elemento de memória de 6 ints
	//sizeof diz quantidade de memória é necessária para esse tipo
	if (!board)
		return (NULL); // por que board seria = 0?
	while (i < 6) //zera os elementos dentro do board
	{
		j = 0;
		board[i] = malloc(sizeof(**board) * 6); //recebe elemento de memória de 6 ints para cada linha
		while (j < 6)
			{
				board[i][j] = 0;
				j++;
			}
		i++;
	}
	init_columns(board, vals);
	init_rows(board, vals);
	return (board);
}
//"boardas" preenchidas, colunas e linhas iniciadas, "meio" = zero;

void free_board(int **board)
{
	int i;

	i = 0;
	while (i < 6)
		free(board[i++]);
	free(board);
}
