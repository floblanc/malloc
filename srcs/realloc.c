/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:30:51 by judumay           #+#    #+#             */
/*   Updated: 2021/02/17 12:19:35 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

// static t_block *find_block(t_heap *heap, void *ptr)
// {
// 	t_block *tmp;

// 	tmp = heap->block;
// 	while ((void *)(tmp + sizeof(t_block)) != ptr)
// 		tmp = tmp->next;
// 	return (tmp);
// }

void *realloc(void *ptr, size_t size)
{
	void *new_ptr;
	t_heap *heap;
	// t_block	*block;

	// pthread_mutex_lock(&g_mutex);
	heap = find_memory(ptr);
	if (!heap)
		return (NULL);
	// block = find_block(heap, ptr);
	if (1)
		return (NULL);
	else
	{
		new_ptr = malloc(size);
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
		// pthread_mutex_unlock(&g_mutex);
		return (new_ptr);
	}
	// pthread_mutex_unlock(&g_mutex);
	return (ptr);
}