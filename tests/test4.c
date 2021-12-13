/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:53:02 by floblanc          #+#    #+#             */
/*   Updated: 2021/12/13 11:53:03 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <stdlib.h>

#define M 1048576

void	print(char *s)
{
	write(1, s, strlen(s));
}

int	main(void)
{
	char	*addr1;
	char	*addr2;
	char	*addr3;

	addr1 = (char *)malloc(16 * M);
	strcpy(addr1, "Bonjour\n");
	print(addr1);
	addr2 = (char *)malloc(16 * M);
	addr3 = (char *)realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	print(addr3);
	return (0);
}
