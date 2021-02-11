/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judumay <judumay@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 15:30:14 by judumay           #+#    #+#             */
/*   Updated: 2021/02/11 16:33:45 by judumay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/malloc.h"

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	// trouver endroit memoire
	// if (pas trouvé or deja free)
	//	return ;
	// remove le block
	//
	pthread_mutex_unlock(&g_mutex);
	return ;
}
