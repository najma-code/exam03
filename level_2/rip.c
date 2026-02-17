/*
Assignment name  : rip
Expected files   : *.c *.h
Allowed functions: puts, write
--------------------------------------------------------------------------------

Write a program that will take as argument a string containing only parenthesis.
if the parenthesis are unbalanced (for example "())")
your program shall remove the minimum number of parentheses for the expression to be balanced.
By removing we mean replacing by spaces.
You will then print all the solutions (can be more than one).

The order of the solutions is not important.

For example this should work:
$> ./rip '(()' | cat -e
 ()$
( )$
$> ./rip '((()()())())' | cat -e
((()()())())$
$> ./rip '()())()'| cat -e
()() ()$
()( )()$
( ())()$
$> ./rip '(()(()(' | cat -e
(()  ) $
( )( ) $
( ) () $
 ()( ) $
*/

#include <stdio.h>

int	min_removals(const char *str)
{
	int	opened = 0;
	int	closed = 0;

	for (int i = 0; str[i]; i++)
	{
		if (str[i] == '(')
			opened++;
		else if (str[i] == ')')
		{
			if (opened > 0)
				opened--;
			else
				closed++;
		}
	}
	return (opened + closed);
}

void	rip(char *str, int m_fix, int n_fix, int pos)
{
	if (m_fix == n_fix)
	{
		if (min_removals(str) == 0)
			puts(str);
		return ;
	}
	for (int i = pos; str[i]; i++)
	{
		if (str[i] == '(' || str[i] == ')')
		{
			char c = str[i];
			str[i] = ' ';
			rip(str, m_fix, n_fix + 1, i + 1);           
			str[i] = c;
		}
	}
}

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return (1);
	char *str = argv[1];	// To make a copy and make it safer: char str[1024];	strcpy(str, argv[1]);
	int m_fix = min_removals(str);
	if (m_fix == 0)
	{
		puts(str);
		return (0);
	}
	rip(str, m_fix, 0, 0);
	return (0);
}
