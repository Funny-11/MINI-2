/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:35:16 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/01 01:46:30 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c && *s)
		s++;
	if (*s)
		return ((char *)s);
	else if (!*s && 0 == (char)c)
		return ((char *)s);
	else
		return (NULL);
}