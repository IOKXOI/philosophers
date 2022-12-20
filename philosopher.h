#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_philo
{
	size_t				i;
	bool			*fork;
	bool			death;
	pthread_t		*id;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*death_mutex;
	size_t			nb;
	size_t			timer;
	size_t			mealtime;
	size_t			sleep_time;
	size_t			meal_to_eat;
}	t_philo;

//ARGS
int args_traitment(int argc, char *argv[], t_philo *philo);
void *routine(void *arg);
int s_atoi(char *str, void *nb);

#endif
