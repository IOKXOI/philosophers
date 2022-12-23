#include "philosopher.h"

//creer tout les threads
int create_philo(t_philo *philo)
{
	int i;
    philo->i = 0;
    philo->id = malloc(sizeof(pthread_t) * (philo->nb));
    if(!philo->id)
        return (0);
    while (philo->i < philo->nb)
    {
        if (pthread_create(&philo->id[philo->i], NULL, &routine, philo))
            printf("error\n");
        philo->i++;
    }
    //if (pthread_create(&philo->id[philo->i], NULL, &monitoring, philo))
     //   printf("error\n");
	i = 0;
	while ((size_t)i < philo->nb)
	{
		pthread_join(philo->id[i], NULL);
		i++;
	}
    return(1);
}

int	clean(t_philo *philo)
{
	free(philo->philo_last_eat);
	free(philo->id);
	free(philo->fork_mutex);
	return (1);
}

int main(int argc, char *argv[])
{
	t_philo philo;
	philo.fork = 0;
	philo.nb = 0;
	philo.death = 0;
	if (!args_traitment(argc, argv, &philo))
		return (1);
	if(!init(&philo))
		return(1);
	if (!create_philo(&philo))
		return(1);
	clean(&philo);
	return (0);
}
