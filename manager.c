/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:21:36 by sydauria          #+#    #+#             */
/*   Updated: 2022/12/31 06:09:02 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

size_t gettime(void)
{
	int time;
	struct timeval tv;

	time = gettimeofday(&tv, NULL);
	if (time == -1)
	{
		//error("");
		return (0);
	}
	return((tv.tv_sec * 1000) + tv.tv_usec);
}

int	mutex_print(int nb, char *str, t_global *global)
{
	nb++;
	pthread_mutex_lock(&global->print_mutex);
	printf("%ld %d %s\n", gettime(), nb, str);
	pthread_mutex_unlock(&global->print_mutex);
	return (1);
}
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


