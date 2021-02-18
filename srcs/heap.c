/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:48:25 by judumay           #+#    #+#             */
/*   Updated: 2021/02/18 13:29:27 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

size_t	get_size(size_t size)
{
	if (size <= TINY)
		return (TINY);
	else if (size <= SMALL)
		return (SMALL);
	return (size);
}

size_t	get_heap_size(size_t size)
{
	size_t	real_size;
	size_t	page_size;
	size_t	new_size;

	page_size = (size_t)getpagesize();
	real_size = get_size(size + sizeof(t_block));
	if (real_size <= SMALL)
		new_size = (real_size) * ALLOC + sizeof(t_heap);
	else
		new_size = real_size + sizeof(t_heap);
	new_size += new_size % page_size;
	return (new_size);
}

t_heap	*create_heap(size_t size)
{
	t_heap	*heap;
	size_t	new_size;

	new_size = get_heap_size(size);
	heap = mmap(NULL, new_size,
		PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	heap->size = new_size;
	heap->block = NULL;
	heap->next = NULL;
	return (heap);
}

t_heap	*find_memory(void *allocation)
{
	t_heap	*tmp_heap;
	t_block	*tmp_block;

	tmp_heap = g_heap;
	while (tmp_heap)
	{
		tmp_block = tmp_heap->block;
		while (tmp_block)
		{
			if ((void *)(tmp_block + sizeof(t_block)) == allocation)
				return (tmp_heap);
			tmp_block = tmp_block->next;
		}
		tmp_heap = tmp_heap->next;
	}
	return (NULL);
}
