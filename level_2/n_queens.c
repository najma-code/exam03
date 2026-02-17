/*
Assignement name : n_queens

Expected files : *.c *.h

Allowed functions : atoi, fprintf, write, calloc, malloc, free, realloc, stdout, stderr

-------------------------------------------------------------------------

Write a program that will print all the solutions to the n queens problem
for a n given as argument.
We will not test with negative values.
The order of the solutions is not important.

You will display the solutions under the following format :
<p1> <p2> <p3> ... \n
where pn are the line index of the queen in each colum starting from 0.

For example this should work :
$> ./n_queens 2 | cat -e

$> ./n_queens 4 | cat -e
1 3 0 2$
2 0 3 1$

$> ./n_queens 7 | cat -e
0 2 4 6 1 3 5$
0 3 6 2 5 1 4$
etc...
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	is_safe(int *positions, int current_col, int current_row)
{
	for (int prev_col = 0; prev_col < current_col; prev_col++)
	{
		int	prev_row = positions[prev_col];
		if (prev_row == current_row ||							// Same row
			prev_row - prev_col == current_row - current_col ||	// Main diagonal
			prev_row + prev_col == current_row + current_col)	// Anti-diagonal
			return (0);
	}
	return (1);
}

void	solve(int *positions, int col, int n)
{
	if (col == n)
	{
	   for (int i = 0; i < n; i++)
		{
			if (i > 0)
				fprintf(stdout, " ");
			fprintf(stdout, "%d", positions[i]);
		}
		fprintf(stdout, "\n");
		return ;
	}
	for (int row = 0; row < n; row++)
	{
		if (is_safe(positions, col, row))
		{
			positions[col] = row;			// Place queen
			solve(positions, col + 1, n);
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	int	n = atoi(argv[1]);
	if (n <= 0)
		return (1);
	int	*positions = malloc(sizeof(int) * n);
	if (!positions)
		return (1);
	solve(positions, 0, n);	
	free(positions);
	return (0);
}
