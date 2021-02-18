/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:44:28 by judumay           #+#    #+#             */
/*   Updated: 2021/02/18 14:54:35 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	i;
	int	*pointer;

	pointer = (int *)calloc(10, sizeof(int));
	if (!pointer)
		return (0);
	i = -1;
	while (++i < 9)
		pointer[i] = i;
	i = -1;
	while (++i < 10)
		printf("%d ", pointer[i]);
	printf("\n");
	free(pointer);
	return (0);
}
