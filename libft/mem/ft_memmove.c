/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:07:59 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/01 01:42:23 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*pdst;
	char	*psrc;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	pdst = (char *)dst;
	psrc = (char *)src;
	if (pdst > psrc)
	{
		i = n;
		while (i > 0)
		{
			pdst[i - 1] = psrc[i - 1];
			i--;
		}
		return ((void *)dst);
	}
	i = 0;
	while (i < n)
	{
		pdst[i] = psrc[i];
		i++;
	}
	return ((void *)dst);
}