/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:48:26 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/05 13:40:48 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	init_print_mutex(t_global *global)
{
	pthread_mutex_init(&global->print_mutex, NULL);
	return (1);
}

static int	init_fork_mutex(t_global *global)
{
	pthread_mutex_init(&global->fork_mutex, NULL);
	return (1);
}

static int	init_death_mutex(t_global *global)
{
	pthread_mutex_init(&global->death_mutex, NULL);
	return (1);
}

int	init_philo_array(t_global *global)
{
	global->philos = malloc(sizeof(t_philo) * global->nb);
	if (!global->philos)
		return (0);
	return (1);
}

int	init_storage_id(t_global *global)
{
	global->wait_id = malloc(sizeof(pthread_t) * global->nb);
	if (!global->wait_id)
		return (0);
	return (1);
}

int	init_philo_struct(t_global *global)
{
	int		i;
	int		meal;
	size_t	time_to_eat;
	size_t	time_to_die;
	size_t	time_to_sleep;

	i = 0;
	meal = global->meal_to_eat;
	time_to_eat = global->time_to_eat;
	time_to_die = global->time_to_die;
	time_to_sleep = global->time_to_sleep;
	while (i < global->nb)
	{
		global->philos[i].id = i;
		global->philos[i].meals = meal;
		global->philos[i].end = 0;
		global->philos[i].time_to_eat = time_to_eat;
		global->philos[i].time_to_die = time_to_die;
		global->philos[i].time_to_sleep = time_to_sleep;
		global->philos[i].global = global;
		if (pthread_mutex_init(&global->philos[i].right_fork_mutex, NULL))
			return (0);
		if (i > 0)
			global->philos[i].left_fork_mutex = &global->philos[i - 1].right_fork_mutex;
		if (i == global->nb - 1)
			global->philos[0].left_fork_mutex = &global->philos[i].right_fork_mutex;
		i++;
	}
	return (1);
}

int	init(t_global *global)
{
	if (!init_print_mutex(global))
		return (0);
	if (!init_death_mutex(global))
		return (0);
	if (!init_philo_array(global))
		return (0);
	if (!init_fork_mutex(global))
		return (0);
	if (!init_storage_id(global))
	{
		free(global->philos);
		return (0);
	}
	if (!init_philo_struct(global))
		return (0);
	return (1);
}

