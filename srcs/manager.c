/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:21:36 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/09 08:43:07 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_timer(t_philo philo, size_t time_to_die)
{
	if (gettime(philo.time_start) > philo.last_eat + time_to_die)
	{
		mutex_print(philo.id, "died", philo.global);
		return (1);
	}
	if (!philo.meals)
		return (-1);
	return (0);
}

size_t	gettime(struct timeval start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((1e3 * ((&end)->tv_sec - (&start)->tv_sec)) \
	+ (1e-3 * ((&end)->tv_usec - (&start)->tv_usec)));
}

void	custom_sleep(t_philo *philo, size_t action_time)
{
	while (action_time > 5000)
	{
		if (!is_dead(philo->global))
			usleep(5000);
		action_time -= 5000;
	}
	usleep(action_time);
}

void	mutex_print(int id, char *str, t_global *global)
{
	pthread_mutex_lock(&global->print_mutex);
	if (!is_dead(global))
		printf("%ld %d %s\n", gettime(global->philos->time_start), id, str);
	pthread_mutex_unlock(&global->print_mutex);
}
