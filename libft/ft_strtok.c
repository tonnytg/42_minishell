/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: caalbert <caalbert@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 02:55:02 by antthoma          #+#    #+#             */
/*   Updated: 2023/08/17 01:56:01 by caalbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char *ft_strtok(char *str, const char *delim, int trigger, int *quote)
{
    static char	*next_token;
    char		*current_token;

    if (trigger == 1)
        next_token = NULL;
    if (str != NULL)
        next_token = str;
    if (next_token == NULL)
        return NULL;
    if (*quote == 1 && *next_token == '\"')
        next_token++;
    current_token = next_token;
    while (*next_token != '\0')
	{
        if (*quote == 0 && *next_token == '\"')
		{
            *quote = 1;
            current_token = next_token + 1;
        }
		else if (*quote == 1 && *next_token == '\"')
		{
            *quote = 0;
            *next_token = '\0';
        } else if (*quote == 0 && strchr(delim, *next_token) != NULL)
            break ;Ó
        next_token++;
    }
    if (*next_token != '\0') {
        *next_token = '\0';
        next_token++;
    }
    return current_token;
}



/*char	*ft_strtok(char *str, const char *delim, int trigger, int *quote)
{
    static char	*next_token;
    char		*current_token;

    if (trigger == 1)
        next_token = NULL;
    if (str != NULL)
        next_token = str;
    if (next_token == NULL)
        return NULL;
    *quote = 0;
    if (*next_token == '\"')
	{
        *quote = 1;
        next_token++;
    }
    current_token = next_token;
    while (*next_token != '\0') {
        if (*quote == 1 && *next_token == '\"')
            break ;
        else if (*quote == 0 && strchr(delim, *next_token) != NULL)
            break ;
        next_token++;
    }
    if (*next_token != '\0') {
        *next_token = '\0';
        next_token++;
    }
    return (current_token);
}*/

