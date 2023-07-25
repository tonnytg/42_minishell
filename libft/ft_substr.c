/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:15:28 by antthoma          #+#    #+#             */
/*   Updated: 2022/07/01 23:37:30 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	src_count;
	size_t	sub_count;
	char	*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	src_count = 0;
	while (src_count < len && s[start + src_count])
		src_count++;
	sub = ft_calloc((1 * src_count) + 1, sizeof(char));
	sub_count = 0;
	while (sub_count < src_count)
	{
		sub[sub_count] = s[start + sub_count];
		sub_count++;
	}
	sub[sub_count] = '\0';
	return (sub);
}
