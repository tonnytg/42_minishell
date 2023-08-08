/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fd.c.                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	test_fd_adapter(t_cmds *cmds)
{
	int		bytes_read;
	char	*msg1;
	char	buffer[1024];
	char	*msg2;

	msg1 = cmds->current->phrase;
	write(STDOUT_FILENO, msg1, ft_strlen(msg1));
	write(STDOUT_FILENO, "\n", 1);
	if (cmds->current->prev != NULL)
	{
		printf("inside\n");
		bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
		if (bytes_read < 0)
			exit(EXIT_FAILURE);
		buffer[bytes_read] = '\0';
		msg2 = ft_strdup(buffer);
		write(STDOUT_FILENO, msg2, ft_strlen(msg2));
	}
	return (0);
}
