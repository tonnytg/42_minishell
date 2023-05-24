/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c.                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void print_message(const char *message, int code)
{
	ft_printf("%s\n", message);
	exit(code);
}

static int	ft_isnumber(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void validate_numeric_argument(char **converted_arg, int count_arg)
{
	int i;

	i = 0;
	if (count_arg <= 1)
		return ;
	while (converted_arg[1][i])
	{
		if (!ft_isnumber(converted_arg[i]))
		{
			printf("bash: exit: %s: numeric argument required\n", converted_arg[i]);
			exit(2);
		}
		i++;
	}
}

static void free_converted_args(char **converted_arg, int count_arg)
{
	int i;

	i = 0;
	while (i < count_arg)
	{
		free(converted_arg[i]);
		i++;
	}
	free(converted_arg);
}


int	exit_adapter(const char *arg)
{
	char	**converted_arg;
	int		count_arg;
	int		exit_code;

	converted_arg = ft_split(arg, ' ');
	count_arg = 0;
	while (converted_arg[count_arg])
		count_arg++;
	if (count_arg > 1)
		print_message("bash: exit: too many arguments", 127);
	validate_numeric_argument(converted_arg, count_arg);
	if (count_arg > 0)
		exit_code = ft_atoi(converted_arg[0]);
	else
		exit_code = 0;
	if(exit_code < 0)
		exit_code = (exit_code % 256 + 256) % 256;
	print_message("exit", exit_code);
	free_converted_args(converted_arg, count_arg);
	exit(exit_code);
}

/*
 * NOTE: On lines 30 and 31, the code handles negative values. 
 * This piece of code transforms the negative value into a corresponding positive 
 * value in the range between 0 and 255, similar to the behavior of Bash.
 * 
 * (https://www.gnu.org/software/bash/manual/bash.html#Definitions)
 * 3.7.5 Exit Status
 * The exit status of an executed command is the value returned by the waitpid 
 * system call or equivalent function. Exit statuses fall between 0 and 255, 
 * though, as explained below, the shell may use values above 125 specially. 
 * Exit statuses from shell builtins and compound commands are also limited to this range. 
 * Under certain circumstances, the shell will use special values to indicate 
 * specific failure modes.
*/