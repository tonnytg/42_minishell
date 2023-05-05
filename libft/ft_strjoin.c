/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 16:55:33 by antthoma          #+#    #+#             */
/*   Updated: 2022/07/01 23:36:37 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*m;

	if (!s1 || !s2)
		return (NULL);
	m = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!m)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		m[i++] = s1[j++];
	j = 0;
	while (s2[j])
		m[i++] = s2[j++];
	m[i] = '\0';
	return (m);
}
