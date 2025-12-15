/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gifanell <gifanell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:48:33 by gifanell          #+#    #+#             */
/*   Updated: 2025/12/15 06:41:21 by gifanell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	long	i;
	long	sign;
	long	number;

	i = 0;
	sign = 1;
	number = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = (number * 10) + (nptr[i] - '0');
		i++;
	}
	return (number * sign);
}
/* DESCRIPTION
	ENG
	The atoi() function converts the initial portion of the string pointed
	to by str to int representation.
	ITA
	La funzione atoi() converte una stringa in un numero/int.
	La stringa passata come parametro può iniziare con un numero arbitrario
	di spazi come determinato da isspace(3).
	Dopo il numero arbitrario di spazi bianchi, può esserci un singolo
	segno opzionale "+" o "-".
	Il resto della stringa verrà convertito in int, fermandosi al primo
*/	