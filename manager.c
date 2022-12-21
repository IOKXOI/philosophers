/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:21:36 by sydauria          #+#    #+#             */
/*   Updated: 2022/12/21 19:17:02 by sydauria         ###   ########.fr       */
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
	return(tv.tv_sec + tv.tv_usec);
}
/*
void mutex_access(t_philo *philo, pthread_mutex_t *mutex, size_t value, int (*ft)(), void *arg);
{
	pthread_mutex_lock(mutex);
	ft(philo);
	pthread_mutex_unlock(mutex);
}

void set_death(t_philo *philo)
{
	philo->death = 1;
}*/


