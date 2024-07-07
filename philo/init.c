/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:49:40 by recherra          #+#    #+#             */
/*   Updated: 2024/05/24 17:49:45 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

//args error handling
int args_error_handling(char *str)
{
    printf("%s\n", str);
    return 1;
}

//sanitize the input
int	sanitize(int ac, char **av, t_shared *shared)
{
	if ((shared->n_philos = ft_atoi(av[1])) == -1)
	    return args_error_handling("Invalid philos number!");
	else if ((shared->ttd = ft_atoi(av[2])) == -1)
	    return args_error_handling("Invalid time to die!");
	else if ((shared->tte = ft_atoi(av[3])) == -1)
        return args_error_handling("Invalid time to eat!");
	else if ((shared->tts = ft_atoi(av[4])) == -1)
        return args_error_handling("Invalid time to sleep!");
	else if (ac == 6)
	{
        if ((shared->must_eat_times = ft_atoi(av[5])) == -1)
            return args_error_handling("Invalid must eat times!");
    }
	return (0);
}


//ACTIONS

long get_curr_time()
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

//  eat
void    ft_eat(t_ph *philo)
{
    pthread_mutex_lock(&philo->right_fork->fork);
    printf("%d has taken a fork\n", philo->id);
    pthread_mutex_lock(&philo->left_fork->fork);
    printf("%d has taken a fork\n", philo->id);
    printf("%d is eating\n", philo->id);
    philo->meals_count++;
    philo->eating = 1;
    philo->last_meal = get_curr_time();
    usleep(philo->shared->tte * 1000);
    philo->eating = 0;
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_unlock(&philo->left_fork->fork);
}

//  sleep
void    ft_sleep(t_ph *philo)
{
    printf("%d is sleeping\n", philo->id);
    usleep(philo->shared->tts * 1000);
}

//  think
void ft_think(t_ph *philo)
{
    printf("%d is thinking\n", philo->id);
}

void	*routine(void *arg)
{
    t_ph *philo = (t_ph *)arg;


    /*
     *  put even philosopher on sleep
     * */

    while (1)
    {
        if (philo->shared->dead)
            break;
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
    }
    return (NULL);
}


int is_dead(t_shared *shared)
{
    printf("jack\n");
    int i = 0;

    while (i < shared->n_philos)
    {
        if (get_curr_time() > shared->philos[i].last_meal && !shared->philos[i].eating)
        {
            printf("%d died\n", shared->philos[i].id);
            pthread_mutex_lock(&shared->dead_mutex);
            shared->dead = 1;
            pthread_mutex_unlock(&shared->dead_mutex);
            return 1;
        }
        i++;
    }
    return 0;
}

int is_all_full(t_shared *shared)
{
    int i = 0;

    while (i < shared->n_philos)
    {
        if (shared->philos[i].meals_count >= shared->must_eat_times)
        {
            pthread_mutex_lock(&shared->eat_mutex);
            shared->phil_is_full++;
            pthread_mutex_unlock(&shared->eat_mutex);
        }
        i++;
    }
    if (shared->phil_is_full == shared->n_philos)
    {
        pthread_mutex_lock(&shared->full_mutex);
        shared->all_full = 1;
        pthread_mutex_unlock(&shared->full_mutex);
        return 1;
    }
    return 0;
}


int	main(int ac, char **av)
{
	t_shared *shared;

	// parsing starts
	if (ac != 5 && ac != 6)
	{
		printf("You should provide more/less args!\n");
		return (1);
	}
	shared = malloc(sizeof(t_shared));

	if (!shared)
	    return 1;
	if (sanitize(ac, av, shared))
		return (1);

	//  allocate && init
	if (init_all(shared))
	    return 1;

	//threads
	int i = 0;

	while (i < shared->n_philos)
	{
	    pthread_create(&shared->philos[i].thread, NULL, routine, &shared->philos[i]);
	    i++;
	}

    // Monitor philosophers
    while (1)
    {
        //==> Run until a philo die
        //==> They all ate the number of meals they need to

        if (is_dead(shared) || is_all_full(shared))
            break;
    }

	//join
	i = 0;
	while (i < shared->n_philos)
	{
		pthread_join(shared->philos[i].thread, NULL);
		i++;
	}

	return (0);
}