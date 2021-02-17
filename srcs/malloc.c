/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:31:40 by judumay           #+#    #+#             */
/*   Updated: 2021/02/17 18:34:07 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;
t_heap *g_heap = NULL;

#include <stdio.h>

void *malloc(size_t size)
{
	t_heap *heap;
	t_heap *last;
	void *allocation;

	// write(STDOUT_FILENO, "Start Malloc\n", 14);
	pthread_mutex_lock(&g_mutex);
	allocation = NULL;
	if (!g_heap)
	{
		// write(STDOUT_FILENO, "Before Heap Creation\n", 22);
		g_heap = create_heap(size);
		// write(STDOUT_FILENO, "After Heap Creation\n", 21);
	}
	// write(STDOUT_FILENO, "Check g_heap\n", 14);
	if (!g_heap)
		return (NULL);
	heap = g_heap;
	last = heap;
	// write(STDOUT_FILENO, "Before malloc while\n", 21);
	while (!allocation && heap)
	{
		if (get_heap_size(size) == heap->size)
		{
			allocation = add_block(heap, size);
			// write(STDOUT_FILENO, "After add_block\n", 17);
		}
		last = heap;
		heap = heap->next;
	}
	if (!allocation)
	{
		// write(STDOUT_FILENO, "********No allocation found********\n", 37);
		// write(STDOUT_FILENO, "Before Heap Creation\n", 22);
		last->next = create_heap(size);
		// write(STDOUT_FILENO, "After Heap Creation\n", 21);
		// write(STDOUT_FILENO, "Before add_block\n", 18);
		allocation = add_block(last->next, size);
		// write(STDOUT_FILENO, "After add_block\n", 17);
	}
	pthread_mutex_unlock(&g_mutex);
	// write(STDOUT_FILENO, "End\n", 5);
	return (allocation);
}
