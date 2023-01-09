/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:20:20 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/09 06:44:51 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	think(t_philo *philo)
{
	mutex_print(philo->id, "is thinking", philo->global);
	return (0);
}

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->global->fork_mutex);
	pthread_mutex_lock(philo->left_fork_mutex);
	pthread_mutex_lock(&philo->right_fork_mutex);
	pthread_mutex_unlock(&philo->global->fork_mutex);
	//mutex_print(philo->id, "left_fork_lock", philo->global);
	//mutex_print(philo->id, "his_fork_lock", philo->global);
	mutex_print(philo->id, "has taken a fork", philo->global);
	mutex_print(philo->id, "has taken a fork", philo->global);
	philo->last_eat = gettime(philo->time_start);
	mutex_print(philo->id, "is eating", philo->global);
	usleep(philo->time_to_eat);
		//	printf("%ld finished to eat\n", gettime(philo->time_start));
	//custom_sleep(philo, philo->time_to_eat);
	//mutex_print(philo->id, "finished eating", philo->global);
	pthread_mutex_unlock(philo->left_fork_mutex);
	pthread_mutex_unlock(&philo->right_fork_mutex);
	return (1);
}

static int	sleeping(t_philo *philo)
{
	mutex_print(philo->id, "is sleeping", philo->global);
	custom_sleep(philo, philo->time_to_sleep);
	return (1);
}

int	check_timer(t_philo philo, size_t time_to_die)
{
	
	//if ((philo.last_eat + time_to_die) <= gettime(philo->time_start))
	if (gettime(philo.time_start) > philo.last_eat + time_to_die)
	{
		mutex_print(philo.id, "died", philo.global);
		return (1);
	}
	if (!philo.meals)
		return (-1);
	return (0);
}

void	*monitoring(void *arg)
{
	int			death;
	int			i;
	int			simualation_running;
	size_t		time_to_die;
	t_global	*global;

	death = 0;
	i = 0;
	global = arg;
	time_to_die = global->time_to_die;
	simualation_running = global->nb;
	while (!death)
	{
		if (global->philos[i].end == 0)
		{
			death = check_timer(global->philos[i], time_to_die);
			if (death == -1)
			{
				death = 0;
				global->philos[i].end = 1;
				simualation_running--;
				if (!simualation_running)
					return (NULL);
			}
		}
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
		eat(philo);
		philo->meals--;
		if (philo->meals)
		{
			sleeping(philo);
			think(philo);
		}
	}
	return (NULL);
}
