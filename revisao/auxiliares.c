//Passo um: transformação da string argv[1] em matriz tab
int *check_argv(char *arg) // verifica se a string passada contem 16 numeros de um a 4 separados por espaço
{
	int i;
	int j;
	int *tab;

	tab = malloc(16 * sizeof(int)); //separa espaço para os 16 inteiros que conterão as "pistas"
	if (!tab)
		return (error_null()); //erro se espaço alocado por outro programa
	j = 0;
	i = 0;
	if (!arg)
		return (error_null()); //erro se argumento vazio
	while (arg[i] != '\0')
	{
		if ((!(i % 2 == 0 && arg[i] >= '1' && arg[i] <= '4')
			&& !(i % 2 == 1 && arg[i] == ' ')) || i > 31)
			return (error_null()); // erro se pares não estão entre 1 a 4 e ímpares diferente de espaço
		if (i % 2 == 0)
			{
                tab[j] = arg[i] - 48; //transforma  os valores de caracteres 1 a 4 em inteiros de 1 a 4 e aloca na matriz tab
                j++;
            }
        i++;
	}
	if ((i > 0 && (arg[i - 1] < '1' || arg[i - 1] > '4')) || i != 31) //esqueci o pq dessa kk
		return (error_null());
	return (tab);
}

//passo 2: separação do espaço para matriz 5x5 (inclui pistas) e preenchimento das bordar
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

//passo 3: solução
int solveur(int **board, int row, int col)
{
	int val;
	int r_row;
	int r_col;

	val = 1;
	while (val <= 4)
	{
		while (!is_safe(board, val, row, col) && val <= 4) // verifica se valor já foi utilizado, se sim, testa próximo valor
			val++;
		if (val > 4) // se não achou nenhum valor de 0 a 4 que resolva a solução, retorna 0
			return (0);
		board[row][col] = val; // se valor está disponível, é alocado em determinada posição da matriz
		if (!solveur_check_row(board, row, col)) // confere valor de acordo com número de vistas da linha
			return (0);
		if (!solveur_check_col(board, row, col))// confere valor de acordo com número de vistas da coluna
			return (0);
		if (row == 4 && col == 4) // Se chegar até aqui, sem erros, finaliza com sucesso
			return (1);
		r_row = row + (col == 4); // se chegar ao ultimo elemento da coluna, vai para a proxima linha, se não, continua na linha
		r_col = (col == 4) ? 1 : col + 1; // se chegar ao ultimo elemento da coluna, volta para o primeiro (na linha a seguir como determinado em cima)
		if (solveur(board, r_row, r_col)) // realiza a próxima iteração
			return (1);
		board[row][col] = 0;
		val++;
	}
	return (0);
}

int is_safe(int **board, int val, int row, int col) // verifica se valor já foi utilizado nas linhas ou colunas
{
	int i;

	i = 1;
	while (i < 5)
	{
		if (board[i++][col] == val) // se algum outro elemento na coluna tem o mesmo valor retorna 0
			return (0);
	}
	i = 1;
	while (i < 5)
	{
		if (board[row][i++] == val) // se algum outro elemento na linha tem o mesmo valor retorna 0
			return (0);
	}
	return (1); // se o valor não é repetido pode ser utiliazado;
}

int solveur_check_row(int **board, int row, int col)
{
	if (col != 4)
		return (1);
	if (!check_row(board[row]))
	{
		board[row][col] = 0;
		return (0);
	}
	return (1);
}

int check_row(int *row) // confere numero de vistas de determinada coluna de acordo com alocação atual
{
	int i;
	int max; // maximo procura pelo maior valor preenchido
	int count;

	i = 1;
	max = 0;
	count = 0;
	while (i < 5)
	{
		if (row[i] > max) // se o valor da linha a seguir é menor que o da linha anterior não será visivel
		{
			max = row[i]; // se o valor da linha a seguir é maior que o da linha anterior se torna o novo máximo
			count++; // se é maior que os anteriores, será visível, por tanto soma-se a contagem de prédios
		}
		i++;
	}
	if (count != row[0])
		return (0);
	i--;
	max = 0;
	count = 0;
	while (i > 0)
	{
		if (row[i] > max)
		{
			max = row[i];
			count++;
		}
		i--;
	}
	if (count != row[5])
		return (0);
	return (1);
}

int solveur_check_col(int **board, int row, int col)
{
	if (row != 4)
		return (1);
	if (!check_col(board, col))
	{
		board[row][col] = 0;
		return (0);
	}
	return (1);
}

int check_col(int **board, int col)
{
	int *tab;
	int i;

	tab = malloc(6 * sizeof(int));
	i = 0;
	while (i < 6)
	{
		tab[i] = board[i][col];
		i++;
	}
	if (check_row(tab))
	{
		free(tab);
		return (1);
	}
	free(tab);
	return (0);
}