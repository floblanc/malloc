/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:29:36 by judumay           #+#    #+#             */
/*   Updated: 2021/02/18 13:41:14 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

static size_t	print_block(t_block *block)
{
	write(STDOUT_FILENO, "0x", 3);
	ft_puthexa((size_t)block + sizeof(t_block));
	write(STDOUT_FILENO, " - ", 4);
	write(STDOUT_FILENO, "0x", 3);
	ft_puthexa((size_t)block + block->size);
	write(STDOUT_FILENO, " : ", 4);
	ft_putnbr(block->size - sizeof(t_block));
	write(STDOUT_FILENO, " octets\n", 9);
	return (block->size - sizeof(t_block));
}

static size_t	print_mem(t_heap *heap)
{
	t_block	*tmp;
	size_t	size;

	size = 0;
	tmp = heap->block;
	if (heap->block->size <= TINY + sizeof(t_block))
		write(STDOUT_FILENO, "TINY : 0x", 10);
	else if (heap->block->size <= SMALL + sizeof(t_block))
		write(STDOUT_FILENO, "SMALL : 0x", 10);
	else
		write(STDOUT_FILENO, "LARGE : 0x", 10);
	ft_puthexa((size_t)(heap + sizeof(t_heap)));
	write(STDOUT_FILENO, "\n", 2);
	while (tmp)
	{
		size += print_block(tmp);
		tmp = tmp->next;
	}
	return (size);
}

void			show_alloc_mem(void)
{
	t_heap	*tmp;
	size_t	total;

	total = 0;
	pthread_mutex_lock(&g_mutex);
	tmp = g_heap;
	while (tmp)
	{
		total += print_mem(tmp);
		tmp = tmp->next;
	}
	write(STDOUT_FILENO, "Total : ", 8);
	ft_putnbr(total);
	write(STDOUT_FILENO, " octets\n", 9);
	pthread_mutex_unlock(&g_mutex);
	return ;
}
