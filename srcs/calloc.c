/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:50:30 by floblanc          #+#    #+#             */
/*   Updated: 2021/12/13 11:50:37 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	*return_calloc(void *ptr, size_t size)
{
	ptr = malloc(size);
	if (!ptr)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	return (ptr);
}

void	*calloc(size_t nmemb, size_t size)
{
	void	*first_ptr;
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = NULL;
	while (nmemb > 0)
	{
		if (ptr == NULL)
		{
			ptr = return_calloc(ptr, size);
			if (!ptr)
				return (NULL);
			first_ptr = ptr;
		}
		else
		{
			ptr = return_calloc(ptr, size);
			if (!ptr)
				return (NULL);
		}
		ft_bzero(ptr, size);
		nmemb--;
	}
	pthread_mutex_unlock(&g_mutex);
	return (first_ptr);
}
