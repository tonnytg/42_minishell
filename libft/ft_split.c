/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antthoma <antthoma@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 13:33:57 by antthoma          #+#    #+#             */
/*   Updated: 2022/07/11 14:21:40 by antthoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
	}
	return (count);
}

static int	ft_word_len(char const *s, int i, char c)
{
	int	count;

	count = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		count++;
	}
	return (count);
}

static void	ft_c_arr_sub(char **arr, char const *s, char c)
{
	int	i;
	int	j;
	int	k;
	int	total_words;

	i = 0;
	j = 0;
	total_words = ft_count_words(s, c);
	while (i < total_words)
	{
		k = 0;
		while (s[j] == c)
			j++;
		arr[i] = (char *)malloc((ft_word_len(s, j, c) + 1) * sizeof(char));
		while (s[j] && s[j] != c)
		{
			arr[i][k] = s[j];
			k++;
			j++;
		}
		arr[i][k] = '\0';
		i++;
	}
	arr[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		total_words;

	if (!s)
		return (NULL);
	total_words = ft_count_words(s, c);
	arr = malloc((total_words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	ft_c_arr_sub(arr, s, c);
	return (arr);
}
