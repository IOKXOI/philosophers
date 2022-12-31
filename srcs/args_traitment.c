#include "philosopher.h"

static int	argument_count(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("usage: number_of_philosopher, time_to_die, time_to_eat, time_to_sleep, [number_of_times_each_philosopher_must_eat]");
		return (0);
	}
	return (1);
}

static int parsing_argv(int argc, char *argv[], t_global *global)
{
	if (!s_atoi(argv[1], &global->nb) || !s_atoi(argv[2], &global->time_to_die) ||
		 !s_atoi(argv[3], &global->time_to_eat) || !s_atoi(argv[4], &global->time_to_sleep))
		return (0);
	if (argc == 6)
	{
		if (!s_atoi(argv[5], &global->meal_to_eat))
			return (0);
	}
	else
		global->meal_to_eat = -1;
	return (1);
}

int args_traitment(int argc, char *argv[], t_global *global)
{
	if (!argument_count(argc))
		return(0);
	if (!parsing_argv(argc, argv, global))
		return(0);
	return(1);
}

