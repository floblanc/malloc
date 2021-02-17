/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:33:07 by judumay           #+#    #+#             */
/*   Updated: 2021/02/17 13:49:08 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
#define MALLOC_H

#include <unistd.h>
#include <sys/mman.h>
#include <pthread.h>
#include <stdbool.h>

#define ALLOC 100
#define TINY 256
#define SMALL 4096

typedef struct s_block
{
	size_t size;
	bool free;
	struct s_block *next;
} t_block;

typedef struct s_heap
{
	size_t size;
	t_block *block;
	struct s_heap *next;
} t_heap;

extern t_heap *g_heap;
extern pthread_mutex_t g_mutex;

/*
** malloc.c
*/

void *malloc(size_t size);

/*
** free.c
*/

void free(void *ptr);

/*
** realloc.c
*/

void *realloc(void *ptr, size_t size);

/*
** heap.c
*/

t_heap *create_heap(size_t size);
t_heap *find_memory(void *allocation);
size_t get_size(size_t size);
size_t get_heap_size(size_t size);

/*
** block.c
*/

void *add_block(t_heap *heap, size_t size);

/*
** show_alloc_mem.c
*/

void show_alloc_mem(void);

/*
** utils.c
*/

size_t ft_strlen(const char *str);
void ft_putnbr(size_t nb);
void ft_puthexa(size_t nb);
void *ft_memcpy(void *dest, const void *src, size_t n);

#endif
