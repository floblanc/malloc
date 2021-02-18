/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:31:40 by judumay           #+#    #+#             */
/*   Updated: 2021/02/18 13:25:09 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
t_heap *g_heap = NULL;

void	*malloc(size_t size)
{
	t_heap	*heap;
	t_heap	*last;
	void	*allocation;

	pthread_mutex_lock(&g_mutex);
	allocation = NULL;
	if (!g_heap && !(g_heap = create_heap(size)))
		return (NULL);
	heap = g_heap;
	last = heap;
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
	pthread_mutex_unlock(&g_mutex);
	return (allocation);
}
