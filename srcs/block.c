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
		heap->block = block;
	}
	else
	{
		tmp_block = heap->block;
		save_block = NULL;
		available_mem = 0;
		while (tmp_block)
		{
			tmp_block = tmp_block->next;
		}
	}
	return ((void*)block);
}