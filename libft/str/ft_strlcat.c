/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:48:39 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/01 01:48:17 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	l_dest;
	size_t	l_src;
	size_t	i;

	l_dest = ft_strlen(dest);
	l_src = ft_strlen(src);
	i = 0;
	if (size <= l_dest)
		return (l_src + size);
	while (src[i] != '\0' && ((l_dest + i) < (size - 1)))
	{
		dest[l_dest + i] = src[i];
		i++;
	}
	dest[l_dest + i] = '\0';
	return (l_dest + l_src);
}