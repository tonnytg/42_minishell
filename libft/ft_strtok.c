/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*       calbert  <calbert@student.42sp.org.br>   +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/04/26 00:17:13 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim, int tigger)
{
	static char	*next_token;
	char		*current_token;

	if (tigger == 1)
		next_token = NULL;
	if (str != NULL)
		next_token = str;
	if (next_token == NULL)
		return (NULL);
	while (*next_token != '\0' && ft_strchr(delim, *next_token) != NULL)
		next_token++;
	if (*next_token == '\0')
	{
		next_token = NULL;
		return (NULL);
	}
	current_token = next_token;
	next_token = ft_strpbrk(next_token, delim);
	if (next_token != NULL)
	{
		*next_token = '\0';
		next_token++;
	}
	return (current_token);
}
