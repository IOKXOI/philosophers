#include "philosopher.h"

//creer tout les threads
int create_philo(t_philo *philo)
{
    philo->i = 0;
    philo->id = malloc(sizeof(pthread_t) * (philo->nb + 1));
    if(!philo->id)
        return (0);
    philo->philo_last_eat = malloc(sizeof(int) * philo->nb);
    if (!philo->philo_last_eat)
        return (0);
    while (philo->i < philo->nb)
    {
        if (pthread_create(&philo->id[philo->i], NULL, &routine, philo))
            printf("error\n");
        usleep(1000);
        philo->i++;
    }
    if (pthread_create(&philo->id[philo->i], NULL, &monitoring, philo))
        printf("error\n");
    return(1);
}

int give_fork(t_philo *philo)
{
    size_t i;

    i = 0;
    philo->fork = malloc(sizeof(bool) * (philo->nb + 2));
    if (!philo->fork)
        return(0);
    while(i < philo->nb + 2)
    {
        philo->fork[i] = false;
        i++;
    }
    return(1);
}

int create_mutex(t_philo *philo)
{
    size_t i;

    i = 0;
    philo->mutex = malloc(sizeof(pthread_mutex_t) * (philo->nb + 2));
    if (!philo->mutex)
        return(0);
    while (i < (philo->nb + 2))
    {
        if (pthread_mutex_init(&philo->mutex[i], NULL))
        {
            return(0);
        //error();
        }
        i++;
    }
    i = 1;
    //lock les fourchettes du philo 1 à nb (fork[0] = fork[nb] et fork[nb+1] = fork[1])
    while (i <= philo->nb)
    {
        if (philo->fork[i - 1] == 0 && philo->fork[i + 1] == 0)
        {
            philo->fork[i] = 1;
            if (i == 1)
            {
                philo->fork[philo->nb + 1] = 1;
                pthread_mutex_lock(&philo->mutex[philo->nb + 1]);
            }
            else if (i == philo->nb)
            {
                philo->fork[0] = 1;
                pthread_mutex_lock(&philo->mutex[0]);
            }
            pthread_mutex_lock(&philo->mutex[i]);
        }
        i++;
    }
    return(1);
}

#include <limits.h>

int main(int argc, char *argv[])
{
    t_philo philo;
    philo.fork = 0;
    philo.nb = 0;
    philo.death = 0;
    if (!args_traitment(argc, argv, &philo))
        return (1);
    if(!give_fork(&philo))
        return(1);
    if(!create_mutex(&philo))
        return(1);
    if (!create_philo(&philo))
        return(1);
    return (0);
}

