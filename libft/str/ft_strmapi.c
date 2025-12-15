/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:52:07 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/01 01:49:36 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
char ft_letstry(unsigned int c, char s)
{
    int l;
    l = c % 2;
    if (l == 0)
        s = s - 32;
    else
        return (s);
    return (s);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*allocated;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	allocated = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (!allocated)
		return (NULL);
	while (i < ft_strlen(s))
	{
		allocated[i] = f(i, s[i]);
		i++;
	}
	return (allocated);
}