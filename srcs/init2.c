/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:38:54 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/09 08:49:13 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_each_philo(int i, t_global *global)
{
	int		meal;
	size_t	time_to_eat;
	size_t	time_to_die;
	size_t	time_to_sleep;

	meal = global->meal_to_eat;
	time_to_eat = global->time_to_eat * 1000;
	time_to_die = global->time_to_die * 1000;
	time_to_sleep = global->time_to_sleep * 1000;
	global->philos[i].id = i + 1;
	global->philos[i].meals = meal;
	global->philos[i].end = 0;
	global->philos[i].time_to_eat = time_to_eat;
	global->philos[i].time_to_die = time_to_die;
	global->philos[i].time_to_sleep = time_to_sleep;
	global->philos[i].global = global;
	if (pthread_mutex_init(&global->philos[i].right_fork_mutex, NULL))
		return (0);
	if (i > 0)
		global->philos[i].left_fork_mutex \
		= &global->philos[i - 1].right_fork_mutex;
	if (i == global->nb - 1)
		global->philos[0].left_fork_mutex = &global->philos[i].right_fork_mutex;
	return (1);
}

int	init_philo_struct(t_global *global)
{
	int		i;

	i = 0;
	while (i < global->nb)
	{
		if (!init_each_philo(i, global))
			return (0);
		i++;
	}
	return (1);
}

int	init(t_global *global)
{
	if (!init_print_mutex(global))
		return (0);
	if (!init_fork_mutex(global))
		return (0);
	if (!init_death_mutex(global))
		return (0);
	if (!init_philo_array(global))
		return (0);
	if (!init_philo_struct(global))
		return (0);
	if (!init_storage_id(global))
	{
		free(global->philos);
		return (0);
	}
	return (1);
}
