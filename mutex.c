/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 20:32:26 by sydauria          #+#    #+#             */
/*   Updated: 2022/12/22 20:33:39 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
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

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->death_mutex);
	if (philo->death)
	{
		pthread_mutex_unlock(&philo->death_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->death_mutex);
	return (1);
}
