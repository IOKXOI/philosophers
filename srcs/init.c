/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 19:48:26 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/09 09:07:20 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_print_mutex(t_global *global)
{
	pthread_mutex_init(&global->print_mutex, NULL);
	return (1);
}

int	init_fork_mutex(t_global *global)
{
	pthread_mutex_init(&global->fork_mutex, NULL);
	return (1);
}

int	init_death_mutex(t_global *global)
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
