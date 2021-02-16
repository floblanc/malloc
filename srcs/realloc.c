/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:30:51 by judumay           #+#    #+#             */
/*   Updated: 2021/02/16 14:35:32 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"










#include <stdio.h>

static t_block	*find_block(t_heap *heap, void *ptr)
{
	t_block	*tmp;

	tmp = heap->block;
	while ((void*)(tmp + sizeof(t_block)) != ptr)
		tmp = tmp->next;
	return(tmp);
}

void	*realloc(void *ptr, size_t size)
{
	void	*new_ptr;
	t_heap	*heap;
	t_block	*block;

	// pthread_mutex_lock(&g_mutex);
	dprintf(1,"WE ARE IN\n");
	heap = find_memory(ptr);
	if (!heap)
		return (NULL);
	block = ptr - sizeof(t_block);
	dprintf(2, "%p\n", &block);
	block = find_block(heap, ptr);
	dprintf(2, "%p\n", &block);
	if (1)
		return(NULL);
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