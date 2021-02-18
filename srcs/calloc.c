/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:37:30 by judumay           #+#    #+#             */
/*   Updated: 2021/02/18 14:55:07 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
	void	*first_ptr;
	void	*ptr;

	ptr = NULL;
	while (nmemb > 0)
	{
		if (ptr == NULL)
		{
			if (!(ptr = malloc(size)))
				return (NULL);
			first_ptr = ptr;
		}
		else
		{
			if (!(ptr = malloc(size)))
				return (NULL);
		}
		ft_bzero(ptr, size);
		nmemb--;
	}
	return (first_ptr);
}
