/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:42:42 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/01 01:40:06 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp_ptr;
	unsigned char	c;

	tmp_ptr = (unsigned char *) s;
	c = '\0';
	while (n--)
		*tmp_ptr++ = c;
}