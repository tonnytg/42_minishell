/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/06/03 20:13:06 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handler(int signal_num)
{
	(void)signal_num;
	printf ("\n");
}

void	signal_handler(int signal_num)
{
	if (signal_num == SIGQUIT)
		;
	else if (signal_num == SIGTERM)
		exit(0);
}

void	signals_handler(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
}
