/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 16:48:25 by judumay           #+#    #+#             */
/*   Updated: 2021/02/12 12:18:03 by floblanc         ###   ########.fr       */
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

t_heap	*create_heap(size_t size)
{
	t_heap		*heap;
	size_t		diff;
	size_t		page_size;
	size_t		heap_size;

	diff = 0;
	page_size = getpagesize();
	heap_size = (size + sizeof(t_block));
	if (heap_size <= SMALL)
		heap_size = heap_size * ALLOC + sizeof(t_heap);
	else
		heap_size = heap_size + sizeof(t_heap);
	if ((diff = heap_size % (size_t)page_size) != 0)
		heap_size += diff;
	heap = mmap(NULL, heap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
	heap->size = heap_size;
	heap->block = NULL;
	heap->next = NULL;
	return (heap);
}

t_heap		*find_memory(void *allocation)
{
	t_heap	*tmp_heap;
	t_block	*tmp_block;

	tmp_heap = g_heap;
	while (tmp_heap)
	{
		tmp_block = tmp_heap->block;
		while (tmp_block)
		{
			if ((void*)(tmp_block + sizeof(t_block)) == allocation)
				return (tmp_heap);
			tmp_block = tmp_block->next;
		}
		tmp_heap = tmp_heap->next;
	}
	return (NULL);
}
