/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 13:57:32 by caalbert          #+#    #+#             */
/*   Updated: 2023/06/24 14:02:13 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pipe(const char *write_msg, char *read_buffer)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	write(pipefd[1], write_msg, ft_strlen(write_msg) + 1);
	read(pipefd[0], read_buffer, ft_strlen(write_msg) + 1);
	close(pipefd[0]);
	close(pipefd[1]);
}
