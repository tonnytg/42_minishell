/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/07/02 12:43:45 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* TODO: search_code_caracter must return number of caracter founded or -1 */
int	search_code_caracter(char *str)
{
	int	i;
	int	type_quote;

	i = 0;
	type_quote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
			type_quote = 47;
		i++;
	}
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			type_quote = 42;
		i++;
	}
	return (type_quote);
}
