/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:08:11 by judumay           #+#    #+#             */
/*   Updated: 2021/09/03 11:51:52 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static t_block	*create_block(void *addr, size_t block_size, t_block *next)
{
	t_block	*block;

	block = addr;
	block->size = block_size;
	block->free = false;
	block->next = next;
	return (block);
}

void	*put_in(t_heap *heap, size_t block_size)
{
	t_block	*tmp;

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
			tmp->next = create_block((void *)tmp + tmp->size,
					block_size, tmp->next);
			return (tmp->next);
		}
		tmp = tmp->next;
	}
	tmp->next = create_block((void *)tmp + tmp->size, block_size, NULL);
	return (tmp->next);
}

static bool	fit_in(t_heap *heap, size_t block_size)
{
	t_block		*tmp;
	size_t		size;

	size = sizeof(t_heap);
	tmp = heap->block;
	while (tmp)
	{
		size += tmp->size;
		tmp = tmp->next;
	}
	return (heap->size - size > block_size);
}

void	*add_block(t_heap *heap, size_t size)
{
	t_block	*block;
	size_t	block_size;

	block = NULL;
	block_size = size + sizeof(t_block);
	if (heap->block == NULL)
	{
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
