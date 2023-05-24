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

int	exit_adapter(const char *arg)
{
	int	exit_code;
	int	i;

	/* NOTE: need to implements some way to count how many are in `arg`
	 * After converts attibuit in a variable to copare on `if`.
	 * Something like that:
	 *  
	 * 		int converted_arg = arg; 
	 * 		
	 * 		if (converted_arg > 2)
	 * 			...
	 * 
	*/
	if (arg > 2)
		print_message("bash: exit: too many arguments", 127);
	i = 0;
	while (arg[1])
	{
		if (!ft_isdigit(arg[i]) && (arg[i] != '-' || i != 0))
		{
			printf("bash: exit: %s: numeric argument required\n", arg);
			exit(2);
		}
	}
	exit_code = ft_atoi(arg);
	if(exit_code < 0)
		exit_code = (exit_code % 256 + 256) % 256;
	ft_printf("args for exit: %s\n", arg);
	return (exit_code);
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