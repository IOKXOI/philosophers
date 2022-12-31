#include "philosopher.h"

static int think(t_philo *philo)
{
	if (!is_dead(philo->global))
		mutex_print(philo->id, "is thinking", philo->global);
	usleep(100);
	return (1);
}

static int eat(t_philo *philo)
{
	if (!is_dead(philo->global))
	{
		pthread_mutex_lock(&philo->fork_mutex);
		pthread_mutex_lock(&philo->right_fork_mutex);
	}
	if (!is_dead(philo->global))
		mutex_print(philo->id, "has taken a fork", philo->global);
	if (!is_dead(philo->global))
		mutex_print(philo->id, "is eating", philo->global);
	philo->last_eat = gettime();
	//if (!global->global_last_eat[i - 1])
	//{
	//	write(probleme gettime of day);
	//	return (0);
	// }
	usleep(philo->time_to_eat);
	if (!is_dead(philo->global))
	{
		pthread_mutex_unlock(&philo->fork_mutex);
		pthread_mutex_unlock(&philo->right_fork_mutex);
	}
	return (1);
}

static int sleeping(t_philo *philo)
{
	if (!is_dead(philo->global))
		mutex_print(philo->id, "is sleeping", philo->global);
	if (!is_dead(philo->global))
		usleep(philo->time_to_sleep);
	return (1);
}
/*
void *monitoring(void *arg)
{
	int				i;
	int				sleep;
	int 			time;
	int				start;
	t_global 		*global;

	i = 0;
	global = arg;
	pthread_mutex_lock(global->time_to_die_mutex);
	sleep = global->time_to_die;
	pthread_mutex_lock(global->time_to_die_mutex);
	while (i < global->nb)
	{
		start = global->global_last_eat[i];
		time = gettime();
		if ((start + time) >= ((int)(global->start + global->time_to_die)))
		{
			printf("%ld %d died\n", gettime(), i + 1);
			global->death = 1;
		}
		i++;
		if (i == (int)global->nb && !global->death)
			i = 0;
	}
	return (NULL);
}*/

int	check_timer(t_philo *philo, size_t time_to_eat)
{
	if ((philo->last_eat + time_to_eat) <= gettime())
		return (1);
	return (0);
}

void *monitoring(void *arg)
{
	bool		death;
	int			i;
	size_t		time_to_eat;
	t_global 	*global;

	death = 0;
	i = 0;
	global = arg;
	time_to_eat = global->time_to_eat;
	while (!death)
	{
		death = check_timer(&global->philos[i], time_to_eat);
		i++;
		if (i == global->nb)
			i = 0;
	}
	pthread_mutex_lock(&global->death_mutex);
	global->death = 1;
	pthread_mutex_lock(&global->death_mutex);
	return (NULL);
}

void *routine(void *arg)
{
	t_philo		*philo = arg;
	t_global	*global = philo->global;
	while (!is_dead(global) && philo->meals)
	{
		eat(philo);
		sleeping(philo);
		think(philo);
		philo->meals--;
	}
	return (NULL);
}
