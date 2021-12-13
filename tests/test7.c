/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:54:21 by floblanc          #+#    #+#             */
/*   Updated: 2021/12/13 11:54:22 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	i;
	int	*pointer;

	pointer = (int *)calloc(20, sizeof(int));
	if (!pointer)
		return (0);
	i = -1;
	while (++i < 19)
		pointer[i] = i;
	i = -1;
	while (++i < 20)
		printf("%d ", pointer[i]);
	printf("\n");
	free(pointer);
	return (0);
}
