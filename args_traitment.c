#include "philosopher.h"

static int	argument_count(int argc)
{
	if (argc < 4 || argc > 5)
	{
		printf("usage: number_of_philosophers, time_to_die time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]");
		return (0);
	}
	return (1);
}

static int parsing_argv(int argc, char *argv[], t_philo *philo)
{
	if (!s_atoi(argv[1], &philo->nb) || !s_atoi(argv[2], &philo->time_to_die) ||
		 !s_atoi(argv[3], &philo->mealtime) || !s_atoi(argv[4], &philo->sleep_time))
		return (0);
	if (argc == 6)
	{
		if (!s_atoi(argv[5], &philo->meal_to_eat))
			return (0);
	}
	else
		philo->meal_to_eat = 0;
	return (1);
}

int args_traitment(int argc, char *argv[], t_philo *philo)
{
	if (!argument_count(argc))
		return(0);
	if (!parsing_argv(argc, argv, philo))
		return(0);
	return(1);
}

