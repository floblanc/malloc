/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 17:33:46 by judumay           #+#    #+#             */
/*   Updated: 2021/09/02 18:12:39 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)dest;
	str2 = (unsigned char *)src;
	if (!n || dest == src)
		return (dest);
	while (n--)
		*str1++ = *str2++;
	return (dest);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(size_t nb)
{
	size_t	n;

	n = nb;
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

void	ft_puthexa(size_t nb)
{
	static char	base[17] = "0123456789ABCDEF";

	if (nb < 16)
		write(STDOUT_FILENO, &base[nb], 1);
	else
	{
		ft_puthexa((nb / 16));
		write(STDOUT_FILENO, &base[nb % 16], 1);
	}
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	if (n == 0)
		return ;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}
