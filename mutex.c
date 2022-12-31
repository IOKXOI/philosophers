/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:32:26 by sydauria          #+#    #+#             */
/*   Updated: 2022/12/31 16:02:18 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
/*
void mutex_access(t_global *global, pthread_mutex_t *mutex, size_t value, int (*ft)(), void *arg);
{
	pthread_mutex_lock(mutex);
	ft(global);
	pthread_mutex_unlock(mutex);
}

void set_death(t_global *global)
{
	global->death = 1;
}*/

int	is_dead(t_global *global)
{
	pthread_mutex_lock(&global->death_mutex);
	if (global->death)
	{
		pthread_mutex_unlock(&global->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&global->death_mutex);
	return (0);
}
