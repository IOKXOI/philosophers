/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:48:26 by sydauria          #+#    #+#             */
/*   Updated: 2022/12/23 03:31:56 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_print_mutex(t_philo *philo)
{
	pthread_mutex_init(&philo->print_mutex, NULL);
	return (1);
}

static int	init_death_mutex(t_philo *philo)
{
	pthread_mutex_init(&philo->death_mutex, NULL);
	return (1);
}


static int	init_last_eat_array(t_philo *philo)
{
	int	i;

	i = 0;
	philo->philo_last_eat = malloc(sizeof(size_t) * philo->nb);
	if (!philo->philo_last_eat)
		return (0);
	while ((size_t)i < philo->nb)
	{
		philo->philo_last_eat[i] = gettime();
		if (philo->philo_last_eat[i] == (size_t)0)
		{
			free(philo->philo_last_eat);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_mutex_fork(t_philo *philo)
{
	int	i;

	i = 1;
	philo->fork_mutex = malloc(sizeof(pthread_mutex_t) * (philo->nb + 1));
	if (!philo->fork_mutex)
		return (0);
	while ((size_t)i < philo->nb + 1)
	{
		pthread_mutex_init(&philo->fork_mutex[i], NULL);
		i++;
	}
	philo->fork_mutex[0] = philo->fork_mutex[philo->nb];
	return (1);
}

int	init(t_philo *philo)
{
	if (!init_print_mutex(philo))
		return (0);
	if (!init_death_mutex(philo))
		return (0);
	if (!init_last_eat_array(philo))
		return (0);
	if (!init_mutex_fork(philo))
	{
		free(philo->philo_last_eat);
		return (0);
	}
	return (1);
}

