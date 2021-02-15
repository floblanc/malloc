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
	t_heap	*free_heap;
	t_heap *prev_heap;

	prev_heap = NULL;
	free_heap = g_heap;
	while (free_heap != heap)
	{
		prev_heap = free_heap;
		free_heap = free_heap->next;
	}
	if (prev_heap)
		prev_heap->next = free_heap->next;
	else
		g_heap = free_heap->next;
	munmap((void*)(heap), heap->size);
}

static void	remove_block(t_heap *heap, void *ptr)
{
	t_block	*free_block;
	t_block *prev_block;
	t_block *actual_block;

	prev_block = NULL;
	free_block = heap->block;
	while ((void*)(free_block + sizeof(t_block)) != ptr)
	{
		prev_block = free_block;
		free_block = free_block->next;
	}
	if (prev_block)
		prev_block->next = free_block->next;
	else
		heap->block = free_block->next;
	// free_block->free = 1;
	//defrag
	actual_block = prev_block->next;
	while (actual_block->next)
	{
		actual_block -= free_block->size;
		prev_block->next = actual_block;
		prev_block = actual_block;
		actual_block = actual_block->next;
	}
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