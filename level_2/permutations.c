/*
Assignment name  : permutations
Expected files   : *.c *.h
Allowed functions: puts, malloc, calloc, realloc, free, write
---------------------------------------------------------------

Write a program that will print all the permutations of a string given as argument.

The solutions must be given in alphabetical order.

We will not try your program with strings containing duplicates (eg: 'abccd').

For example this should work:

$> ./permutations a | cat -e
a$

$> ./permutations ab | cat -e
ab$
ba$

$> ./permutations abc | cat -e
abc$
acb$
bac$
bca$
cab$
cba$
*/

#include <stdio.h>
#include <stdlib.h>

void	ft_swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void	ft_sort(char *str)
{
	int i = 0;
	while (str[i])
	{
		int j = i + 1;
		while (str[j])
		{
			if (str[i] > str[j])
				ft_swap(&str[i], &str[j]);
			j++;
		}
		i++;
	}
}

void	permutation(char *str, char *res, int res_index, int max_index, char *tab)
{
	if (res_index == max_index)
	{
		puts(res);
		return ;
	}
	int i = 0;
	while (i < max_index)
	{
		if (tab[i] == 0)
		{
			res[res_index] = str[i];
			tab[i] = 1;
			permutation(str, res, res_index + 1, max_index, tab);
			tab[i] = 0;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return (1);
	int		i = 0;
	char	*str = argv[1];		// To make a copy and make it safer: char str[1024];	strcpy(str, argv[1]);
	while (str[i])
		i++;
	char	*res = calloc(i + 1, sizeof(char));
	char	*tab = calloc(i + 1, sizeof(char));
	if (!res || !tab)
		return (1);
	ft_sort(str);
	permutation(str, res, 0, i, tab);
	free(res);
	free(tab);
	return (0);
}
