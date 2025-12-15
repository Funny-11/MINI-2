/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:47:30 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/01 01:41:16 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	size_t				i;

	str = (const unsigned char *)s;
	i = 0;
	while (n > 0)
	{
		if (str[i] == (unsigned char)c)
			return ((void *)&str[i]);
		i++;
		n--;
	}
	return (NULL);
}