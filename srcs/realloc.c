/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:30:51 by judumay           #+#    #+#             */
/*   Updated: 2021/09/02 18:11:05 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_block	*find_block(t_heap *heap, void *ptr)
{
	t_block	*tmp;

	tmp = heap->block;
	while ((void *)(tmp + sizeof(t_block)) != ptr)
		tmp = tmp->next;
	return (tmp);
}

static void	*realloc_n(void *ptr, size_t size, t_block *block)
{
	void	*new_ptr;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (get_size(block->size) == get_size(size + sizeof(t_block)))
	{
		block->size = size + sizeof(t_block);
		return (ptr);
	}
	else
	{
		new_ptr = malloc(size);
		if (!new_ptr)
			return (ptr);
		if (block->size - sizeof(t_block) <= size)
			size = block->size - sizeof(t_block);
		new_ptr = ft_memcpy(new_ptr, ptr, size);
		free(ptr);
		return (new_ptr);
	}
}

void	*realloc(void *ptr, size_t size)
{
	t_heap	*heap;
	t_block	*block;
	void	*new_ptr;

	pthread_mutex_lock(&g_mutex);
	heap = find_memory(ptr);
	if (!heap)
	{
		pthread_mutex_unlock(&g_mutex);
		return (NULL);
	}
	block = find_block(heap, ptr);
	new_ptr = realloc_n(ptr, size, block);
	pthread_mutex_unlock(&g_mutex);
	return (new_ptr);
}
