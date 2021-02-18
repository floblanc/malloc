/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 14:37:30 by judumay           #+#    #+#             */
/*   Updated: 2021/02/18 15:38:18 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	*return_calloc(void *ptr, size_t size)
{
	if (!(ptr = malloc(size)))
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	return (ptr);
}

void		*calloc(size_t nmemb, size_t size)
{
	void	*first_ptr;
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = NULL;
	while (nmemb > 0)
	{
		if (ptr == NULL)
		{
			if (!(ptr = return_calloc(ptr, size)))
				return (NULL);
			first_ptr = ptr;
		}
		else
		{
			if (!(ptr = return_calloc(ptr, size)))
				return (NULL);
		}
		ft_bzero(ptr, size);
		nmemb--;
	}
	pthread_mutex_unlock(&g_mutex);
	return (first_ptr);
}
