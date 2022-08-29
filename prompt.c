#include "shell.h"

/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @i: characters read from get_line
 * @command: user's typed in cmd
 * @env: environmental variable linked list
 */
void ctrl_D(int i, char *command, list_t *env)
{
	if (i == 0) /* handles Ctrl+D */
	{
		free(command); /* exit with newline if in shell */
		free_linked_list(env);
		if (isatty(STDIN_FILENO))/* ctrl+d prints newline */
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * ignore_space - returns string without spaces in front
 * @str: string
 * Return: new String
 */
char *ignore_space(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}
/**
 * ctrl_c - ignore Ctrl-C input and prints prompt again
 * @n: takes in int from signal
 */
void ctrl_c(int n)
{
	(void)n;
	write(STDOUT_FILENO, "\n:) ", 4);
}

/**
 * built_in - handle shell builtins (exit, env, cd)
 * @token: user's typed cmd
 * @env: environmental variable
 * @num: take in nth user command typed to write error message
 * @command: bring in command to free
 * Return: 1 if acted on builtin, 0 if not
 */
int built_in(char **token, list_t *env, int num, char **command)
{
	int j = 0;

	/* if user inputs "exit", free cmd tokens & exit */
	if (_strcmp(token[0], "exit") == 0)/*compare string with exit keyword*/
	{
		j = __exit(token, env, num, command);
	}
	/* if user inputs "env", print, free cmd tokens, and reprompt */
	else if (_strcmp(token[0], "env") == 0)
	{
		_env(token, env);
		j = 1;
	}
	/* if user inputs "cd" ,change directory */
	else if (_strcmp(token[0], "cd") == 0)
	{
		j = _cd(token, env, num);
	}
	/* if user inputs "setenv", create | modify linked list node */
	else if (_strcmp(token[0], "setenv") == 0)
	{
		_setenv(&env, token);
		j = 1;
	}
	/* if user inputs "unsetenv", remove linked list node */
	else if (_strcmp(token[0], "unsetenv") == 0)
	{
		_unsetenv(&env, token);
		j = 1;
	}
	return (j);
}
/**
 * prompt - prompt shell repeatedly to user & executes user's cmds
 * @en: envrionmental variables
 * Return: 0 on success
 */
int prompt(char **en)
{
	list_t *env;
	size_t i = 0, n = 0;
	int command_line_no = 0, exit_stat = 0;
	char *command, *n_cmd, **token;

	env = env_linked_list(en);
	do {
		command_line_no++;
		if (isatty(STDIN_FILENO)) /* reprompt if in interactive shell */
			write(STDOUT_FILENO, ":) ", 3);
		else
			non_interactive(env);
		signal(SIGINT, ctrl_c); /* makes ctrl+c not to work in shell */
		command = NULL;
		i = 0; /* reset vars each time loop runs */
		i = get_line(&command); /* read user's cmd in stdin shell*/
		ctrl_D(i, command, env); /* exits shell if ctrl-D */
		n_cmd = command;
		command = ignore_space(command);
		n = 0;
		while (command[n] != '\n') /* replace get_line's \n with \0 */
			n++;
		command[n] = '\0';
		if (command[0] == '\0') /* reprompt if user hits enter only */
		{
			free(n_cmd);
			continue;
		}
		token = NULL;
		token = _str_tok(command, " "); /*token user cmd delim(space)*/
		if (n_cmd != NULL)
			free(n_cmd);
		exit_stat = built_in(token, env, command_line_no, NULL);
		if (exit_stat)
			continue;
		exit_stat = _execve(token, env, command_line_no);
	} while (1); /* keep on repeating untill user exits shell */
	return (exit_stat);
}

