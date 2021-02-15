/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:08:11 by floblanc          #+#    #+#             */
/*   Updated: 2021/02/15 14:33:19 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static	t_block *create_block(void *addr, size_t block_size, t_block *next)
{
	t_block	*block;

	block = addr;
	block->size = block_size;
	block->next = next;
	return (block);
}

static	t_block	*available_size(t_heap *heap, size_t block_size)
{
	size_t	size;
	t_block	*tmp;

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
		return (tmp->next = create_block(heap->block + size, block_size, NULL));
	return (NULL);
}

void	*add_block(t_heap *heap, size_t size)
{
	t_block	*block;

	block = create_block(NULL, size + sizeof(t_block), NULL);
	if (heap->block == NULL)
	{
		block = (void *)(heap + sizeof(t_heap));
		heap->block = block;
	}
	else
		block = available_size(heap, block->size);
	return ((void*)(block + sizeof(t_block)));
	// return ((void*)block);
}
