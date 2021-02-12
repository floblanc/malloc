/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: floblanc <floblanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:31:40 by judumay           #+#    #+#             */
/*   Updated: 2021/02/12 12:07:59 by floblanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

pthread_mutex_t g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	t_heap	*heap;
	t_heap	*last;
	void	*allocation;


	pthread_mutex_lock(&g_mutex);
	allocation = NULL;
	if (!g_heap)
		g_heap = create_heap(size);
	heap = g_heap;
	while (!allocation && heap)
	{
		if (get_size(size) == heap->size)
			allocation = add_block(last->next, size);
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
