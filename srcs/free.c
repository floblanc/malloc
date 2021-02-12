/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:30:14 by judumay           #+#    #+#             */
/*   Updated: 2021/02/12 12:17:48 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static void	remove_heap(t_heap *heap)
{
	t_heap	*tmp_heap;
	t_heap *prev_heap;

	prev_heap = NULL;
	tmp_heap = g_heap;
	while (tmp_heap != heap)
	{
		prev_heap = tmp_heap;
		tmp_heap = tmp_heap->next;
	}
	if (prev_heap)
	// if (tmp_bloc->prev)
	{
	// (tmp_heap->prev)->next = tmp_heap->next;
	// (tmp_heap->next)->prev = tmp_heap->prev;
	}
	else
	{
		g_heap = tmp_heap->next;
		// if (tmp_heap->next)
		// 	(tmp_heap->next)->prev = NULL;
	}
	munmap((void*)(heap), heap->size);
}

static void	remove_block(t_heap *heap, void *ptr)
{
	t_block	*tmp_block;
	t_block *prev_block;

	prev_block = NULL;
	tmp_block = heap->block;
	while ((void*)(tmp_block + sizeof(t_block)) != ptr)
	{
		prev_block = tmp_block;
		tmp_block = tmp_block->next;
	}
	tmp_block->free = 1;
	if (prev_block)
		prev_block->next = tmp_block->next;
	else
		heap->block = tmp_block->next;
	while (prev_block->next && (prev_block->next)->free == 0)
		prev_block = prev_block->next;
	tmp_block->next = prev_block->next;
	prev_block->next = tmp_block;
}

void	free(void *ptr)
{
	t_heap *heap;


	pthread_mutex_lock(&g_mutex);
	if (!(heap = find_memory(ptr)))
	{
		pthread_mutex_unlock(&g_mutex);
		return;
	}
	remove_block(heap, ptr);
	if (heap->block == NULL)
		remove_heap(heap);
	pthread_mutex_unlock(&g_mutex);
	return ;
}