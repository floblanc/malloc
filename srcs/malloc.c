/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 11:51:22 by floblanc          #+#    #+#             */
/*   Updated: 2021/12/13 11:51:23 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;
t_heap			*g_heap = NULL;

static void	*alloc(t_heap *heap, t_heap *last, void *allocation, size_t size)
{
	while (!allocation && heap)
	{
		if (get_heap_size(size) == heap->size)
			allocation = add_block(heap, size);
		last = heap;
		heap = heap->next;
	}
	if (!allocation)
	{
		last->next = create_heap(size);
		allocation = add_block(last->next, size);
	}
	return (allocation);
}

void	*malloc(size_t size)
{
	t_heap	*heap;
	t_heap	*last;
	void	*allocation;

	pthread_mutex_lock(&g_mutex);
	allocation = NULL;
	if (!g_heap)
		g_heap = create_heap(size);
	if (g_heap)
	{
		heap = g_heap;
		last = heap;
		allocation = alloc(heap, last, allocation, size);
	}
	pthread_mutex_unlock(&g_mutex);
	return (allocation);
}
