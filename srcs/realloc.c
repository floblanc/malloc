/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:30:51 by judumay           #+#    #+#             */
/*   Updated: 2021/02/17 18:30:38 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_block *find_block(t_heap *heap, void *ptr)
{
	t_block *tmp;

	tmp = heap->block;
	while ((void *)(tmp + sizeof(t_block)) != ptr)
		tmp = tmp->next;
	return (tmp);
}

void *realloc(void *ptr, size_t size)
{
	void *new_ptr;
	t_heap *heap;
	t_block *block;

	heap = find_memory(ptr);
	if (!heap)
		return (malloc(size));
	block = find_block(heap, ptr);
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
		if (!(new_ptr = malloc(size)))
			return (ptr);
		if (block->size - sizeof(t_block) <= size)
			size = block->size - sizeof(t_block);
		new_ptr = ft_memcpy(new_ptr, ptr, size);
		free(ptr);
		return (new_ptr);
	}
}