/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:33:46 by judumay           #+#    #+#             */
/*   Updated: 2021/02/15 12:13:06 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	ft_putnbr(size_t nb)
{
	char	c;

	if (nb < 10)
	{
		c = (char)(nb + 48);
		write(STDOUT_FILENO, &c, 1);
	}
	else
	{
		ft_putnbr(nb / 10);
		c = nb % 10;
		write(STDOUT_FILENO, &c, 1);
	}
}

void	ft_puthexa(size_t nb)
{
	static char base[17] = "0123456789ABCDEF";

	if (nb < 16)
		write(STDOUT_FILENO, &base[nb], 1);
	else
	{
		ft_puthexa((nb / 16));
		write(STDOUT_FILENO, &base[nb % 16], 1);
	}
}
