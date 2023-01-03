/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sydauria <sydauria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 09:17:16 by sydauria          #+#    #+#             */
/*   Updated: 2023/01/03 23:42:30 by sydauria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	create_philo(t_global *global)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < global->nb)
	{
		global->philos[i].last_eat = gettime();
		if (pthread_create(&global->wait_id[i], NULL, &routine, &global->philos[i]))
			printf("error\n");
		usleep(200);
		i++;
	}
	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, global))
		printf("error\n");
	pthread_join(monitor, NULL);
	while (i < global->nb)
	{
		pthread_join(global->wait_id[i], NULL);
		i++;
	}
	return (1);
}

int	clean(t_global *global)
{
	free(global->wait_id);
	free(global->philos);
	return (1);
}

void	*only_one(void *arg)
{
	t_global	*global;

	global = arg;
	usleep(global->time_to_die);
	printf("%ld 1 is dead\n", gettime());
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_global	global;

	global.nb = 0;
	global.time_to_eat = 0;
	global.meal_to_eat = 0;
	global.time_to_die = 0;
	global.death = 0;
	if (!args_traitment(argc, argv, &global))
		return (1);
	if (!init(&global))
		return (1);
	if (global.nb > 1)
	{
		global.start = gettime();
		if (!create_philo(&global))
			return (1);
	}
	else if (!only_one(&global))
		return (1);
	clean(&global);
	return (0);
}
