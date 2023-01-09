/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 05:21:36 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/09 02:15:23 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
size_t	gettime(void)
{
	int				time;
	struct timeval	tv;

	time = gettimeofday(&tv, NULL);
	if (time == -1)
	{
		//error("");
		return (0);
	}
	return ((tv.tv_sec * 1000) + (tv.tv_usec));
}*/

size_t	gettime(struct timeval start)
{
	struct timeval	end;

	gettimeofday(&end, NULL);
	return ((1e3 * ((&end)->tv_sec - (&start)->tv_sec)) + (1e-3 * ((&end)->tv_usec - (&start)->tv_usec)));
}


void custom_sleep(t_philo *philo, size_t action_time)
{
	while(action_time >5000)
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
	{
		// if (id == 1)
		// 	dprintf(global->fd1, "%ld %d %s\n", gettime(global->philos->time_start), id, str);
		// else if (id == 2)
		// 	dprintf(global->fd2, "%ld %d %s\n", gettime(global->philos->time_start), id, str);
		// else if (id == 3)
		// 	dprintf(global->fd3, "%ld %d %s\n", gettime(global->philos->time_start), id, str);
		// else if (id == 4)
		// 	dprintf(global->fd4, "%ld %d %s\n", gettime(global->philos->time_start), id, str);
		// else
			printf("%ld %d %s\n", gettime(global->philos->time_start), id, str);
	}
	pthread_mutex_unlock(&global->print_mutex);
}
