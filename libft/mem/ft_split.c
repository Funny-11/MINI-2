/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 17:04:24 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/01 01:43:04 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_counter_words(const char *string, char c)
{
	int	i;
	int	words_n;
	int	start;

	i = 0;
	words_n = 0;
	start = 1;
	while (string[i] != '\0')
	{
		if (string[i] != c && start)
		{
			words_n++;
			start = 0;
		}
		else if (string[i] == c)
			start = 1;
		i++;
	}
	return (words_n);
}

static char	**dealloc(char **allocated, int j)
{
	int	i;

	i = 0;
	(void)j;
	while (allocated && allocated[i])
	{
		free(allocated[i]);
		i++;
	}
	free(allocated);
	return (NULL);
}

static char	**allocate_word(char **allocated, char const *s, char c)
{
	int	start;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > start)
		{
			allocated[j] = ft_substr(s, start, i - start);
			if (!allocated[j])
				return (dealloc(allocated, j));
			j++;
		}
	}
	return (&allocated[j]);
}

char	**ft_split(char const *s, char c)
{
	char	**allocated;
	int		words;
	int		j;

	j = 0;
	words = ft_counter_words(s, c);
	if (!s || s == NULL)
		return (NULL);
	if (s == 0)
		return ((char **)ft_strdup(""));
	allocated = ft_calloc((words + 1), sizeof(char *));
	if (!allocated)
		return (dealloc(allocated, j));
	allocate_word(allocated, s, c);
	return (allocated);
}