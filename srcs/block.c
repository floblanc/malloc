/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:08:11 by floblanc          #+#    #+#             */
/*   Updated: 2021/02/17 16:51:45 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_block *create_block(void *addr, size_t block_size, t_block *next)
{
	t_block *block;

	block = addr;
	block->size = block_size;
	block->free = false;
	block->next = next;
	return (block);
}

void *put_in(t_heap *heap, size_t block_size)
{
	t_block *tmp;

	tmp = heap->block;
	if (tmp->free == true)
	{
		tmp = create_block((void *)tmp + tmp->size, block_size, tmp->next);
		return (tmp);
	}
	while (tmp->next)
	{
		if (tmp->next->free == true)
		{
			// write(STDOUT_FILENO, "Before create_block in while\n", 30);
			tmp->next = create_block((void *)tmp + tmp->size, block_size, tmp->next);
			return (tmp->next);
		}
		tmp = tmp->next;
	}
	// write(STDOUT_FILENO, "Before create_block after while\n", 33);
	tmp->next = create_block((void *)tmp + tmp->size, block_size, NULL);
	return (tmp->next);
}

static bool fit_in(t_heap *heap, size_t block_size)
{
	t_block *tmp;
	size_t size;

	size = sizeof(t_heap);
	tmp = heap->block;
	while (tmp)
	{
		size += tmp->size;
		tmp = tmp->next;
	}
	return (heap->size - size > block_size);
}

void *add_block(t_heap *heap, size_t size)
{
	t_block *block;
	size_t block_size;

	// write(STDOUT_FILENO, "Before create_block\n", 21);
	block = NULL;
	block_size = size + sizeof(t_block);
	// write(STDOUT_FILENO, "After create_block\n", 20);
	if (heap->block == NULL)
	{
		// write(STDOUT_FILENO, "Heap->block == NULL\n", 21);
		block = create_block((void *)(heap + sizeof(t_heap)), block_size, NULL);
		heap->block = block;
	}
	else
	{
		if (fit_in(heap, size + sizeof(t_block)))
			block = put_in(heap, block_size);
	}
	if (block == NULL)
		return (NULL);
	return ((void *)(block + sizeof(t_block)));
}
