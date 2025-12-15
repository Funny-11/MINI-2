/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:43:01 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/01 01:42:03 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;

	if (src == NULL && dst == NULL)
		return (dst);
	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	while (n > 0)
	{
		*(p_dst++) = *(p_src++);
		n--;
	}
	return (dst);
}