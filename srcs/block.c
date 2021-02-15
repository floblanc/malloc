/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:08:11 by floblanc          #+#    #+#             */
/*   Updated: 2021/02/12 12:46:34 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

t_block *create_block(void *addr, size_t block_size)
{
	t_block	*block;

	block = addr;
	block->size = block_size;
	block->next = NULL;
	return (block);
}

t_block	*available_size(t_heap *heap, size_t block_size)
{
	size_t	size;
	t_block	*tmp;
	t_block	*block;

	tmp = NULL;
	size = sizeof(t_heap);
	if (heap->block)
	{
		tmp = heap->block;
		while (tmp->next)
		{
			size += tmp->size;
			tmp = tmp->next;
		}
		size += tmp->size;
	}
	if (heap->size - size >= block_size)
		return (tmp->next = create_block(heap->block + size, block_size));
	return (NULL);
}

void	*add_block(t_heap *heap, size_t size)
{
	t_block	*block;
	t_block	*tmp_block;
	t_block	*save_block;
	size_t	available_mem;

	block = NULL;
	block->size = size + sizeof(t_block);
	block->next = NULL;
	if (heap->block == NULL)
	{
		block = heap + sizeof(t_heap);
		heap->block = block;
	}
	else
		block = available_size(size, block->size);
	return ((void*)block);
	// return ((void*)block + sizeof(t_block));
}