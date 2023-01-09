/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:20:20 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/09 09:18:10 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eat(t_philo *philo)
{
	if (!is_dead(philo->global))
	{
		pthread_mutex_lock(&philo->global->fork_mutex);
		pthread_mutex_lock(philo->left_fork_mutex);
		pthread_mutex_lock(&philo->right_fork_mutex);
		pthread_mutex_unlock(&philo->global->fork_mutex);
		mutex_print(philo->id, "has taken a fork", philo->global);
		mutex_print(philo->id, "has taken a fork", philo->global);
		philo->last_eat = gettime(philo->time_start);
		mutex_print(philo->id, "is eating", philo->global);
		custom_sleep(philo, philo->time_to_eat);
		pthread_mutex_unlock(philo->left_fork_mutex);
		pthread_mutex_unlock(&philo->right_fork_mutex);
		return (1);
	}
	return (0);
}

static int	sleeping(t_philo *philo)
{
	if (!is_dead(philo->global))
	{
		mutex_print(philo->id, "is sleeping", philo->global);
		custom_sleep(philo, philo->time_to_sleep);
		return (1);
	}
	return (0);
}

static int	think(t_philo *philo)
{
	if (!is_dead(philo->global))
	{
		mutex_print(philo->id, "is thinking", philo->global);
		return (1);
	}
	return (0);
}

static int	check_each_philo(int *death, int *end, t_philo *philo)
{
	if (philo->end == 0)
	{
		*death = check_timer(*philo, philo->global->time_to_die);
		if (*death == -1)
		{
			*death = 0;
			philo->end = 1;
			(*end)--;
			if (*end == 0)
				return (0);
		}
	}
	return (1);
}

void	*monitoring(void *arg)
{
	int			i;
	int			death;
	int			end;
	size_t		time_to_die;
	t_global	*global;

	death = 0;
	i = 0;
	global = arg;
	time_to_die = global->time_to_die;
	end = global->nb;
	while (!death)
	{
		if (!check_each_philo(&death, &end, &global->philos[i]))
			return (NULL);
		i++;
		if (i == global->nb)
			i = 0;
	}
	pthread_mutex_lock(&global->death_mutex);
	global->death = 1;
	pthread_mutex_unlock(&global->death_mutex);
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo		*philo;
	t_global	*global;

	philo = arg;
	global = philo->global;
	gettimeofday(&philo->time_start, NULL);
	if (philo->id % 2 == 0 || (philo->id % 2 != 0 && philo->id == global->nb))
		custom_sleep(philo, philo->time_to_eat / 2);
	while (!is_dead(global) && philo->meals)
	{
		if (eat(philo))
		{
			philo->meals--;
			if (philo->meals)
			{
				if (sleeping(philo))
					if (!think(philo))
						return (NULL);
			}
		}
	}
	return (NULL);
}
