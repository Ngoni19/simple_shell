#include "shell.h"

/**
 * t_strlen - returns token's string length for mallocing
 * @str: a token
 * @pos: index position in user's cmd typed into shell
 * @delm: delimeter (e.g. " ")for tokenization of str
 * Return: token length
 */
int t_strlen(char *str, int pos, char delm)
{
	int len = 0;

	while ((str[pos] != delm) && (str[pos] != '\0'))
	{
		pos++;
		len++;
	}
	return (len);
}

/**
 * t_size - returns number of delim ignoring continuous delim
 * @str: user's cmd typed
 * @delm: delimeter
 * Return: number of delims so that (num token = delims + 1)
 */
int t_size(char *str, char delm)
{
	int i = 0, num_delim = 0;

	while (str[i] != '\0')
	{
		if ((str[i] == delm) && (str[i + 1] != delm))
		{
			/* handle continuous delimiters */
			num_delim++;
		}
		if ((str[i] == delm) && (str[i + 1] == '\0'))
		{
			/*handle continuous delims after full command */
			num_delim--;
		}
		i++;
	}
	return (num_delim);
}

/**
 * ignore_delm - returns a version of string without delims ++
 * @str: string
 * @delm: delimiter (e.g. " ;")
 * Return: new string (e.g. "    ls -a" --> "ls -a")
 */
char *ignore_delm(char *str, char delm)
{
	while (*str == delm)
		str++;
	return (str);
}

/**
 * _str_tok - tokenizes a string & returns an array of tokens
 * @str: user's cmd typed into shell
 * @delm: delimeter (e.g. " ");
 * Return: an array of tokens (e.g. {"ls", "-l", "/tmp"}
 */
char **_str_tok(char *str, char *delm)
{
	int buffsize = 0, p = 0, S_i = 0, i = 0, len = 0, Se_i = 0, t = 0;
	char **toks = NULL, deli_ch;

	deli_ch = delm[0];
	/* creates new version of string ignoring delims infront*/
	str = ignore_delm(str, deli_ch);
	/* malloc ptrs to store array of tokens (buffsize + 1), and NULL ptr */
	buffsize = t_size(str, deli_ch);
	toks = malloc(sizeof(char *) * (buffsize + 2));
	if (toks == NULL)
		return (NULL);
	while (str[Se_i] != '\0')	/* find string ending index */
		Se_i++;
	while (S_i < Se_i)
	{ /* malloc lengths for each token ptr in array */
		if (str[S_i] != deli_ch)
		{
			len = t_strlen(str, S_i, deli_ch);
			toks[p] = malloc(sizeof(char) * (len + 1));
			if (toks[p] == NULL)
				return (NULL);
			i = 0;
			while ((str[S_i] != deli_ch) && (str[S_i] != '\0'))
			{
				toks[p][i] = str[S_i];
				i++;
				S_i++;
			}
			toks[p][i] = '\0'; /* null terminate at end*/
			t++;
		}
		/* handle repeated delimeters then increment ptr after ("ls __-l")*/
		if (S_i < Se_i && (str[S_i + 1] != deli_ch && str[S_i + 1] != '\0'))
			p++;
		S_i++;
	}
	p++;
	toks[p] = NULL; /* set last array ptr to NULL */
	return (toks);
}

