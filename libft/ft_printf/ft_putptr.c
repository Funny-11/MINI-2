/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 14:50:41 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/01 01:33:07 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(unsigned long ptr)
{
	int	count;

	count = 0;
	if (!ptr)
	{
		count += write(1, "(nil)", 5);
		return (count);
	}
	else
	{
		count += write(1, "0x", 2);
		count += ft_puthex(ptr, true);
	}
	return (count);
}