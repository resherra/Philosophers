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

int	ft_atoi(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-' || str[i + 1] == '+')
			return (-1);
		else if (str[i] == '+')
		{
			i++;
			break ;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	if (str[i])
		return (-1);
	return (result);
}

int	sanitize(int ac, char **av, t_shared *shared)
{
	if ((shared->n_philos = ft_atoi(av[1])) == -1)
    {
        printf("Invalid philos number\n");
        return (1);
    }
	else if ((shared->ttd = ft_atoi(av[2])) == -1)
    {
        printf("Invalid time to die\n");
		return (1);
    }
	else if ((shared->tte = ft_atoi(av[3])) == -1)
    {
        printf("Invalid time to eat\n");
		return (1);
    }
	else if ((shared->tts = ft_atoi(av[4])) == -1)
    {
        printf("Invalid time to sleep\n");
		return (1);
    }
	else if (ac == 6)
	{
        if ((shared->must_eat_times = ft_atoi(av[5])) == -1)
        {
            printf("Invalid must eat times\n");
            return (1);
        }
    }
	return (0);
}


void    ft_eat(t_ph *philo)
{
    pthread_mutex_lock(&philo->right_fork->fork);
    printf("%d  has taken a fork\n", philo->id);
    pthread_mutex_lock(&philo->left_fork->fork);
    printf("%d  has taken a fork\n", philo->id);
    printf("%d is eating\n", philo->id);
    philo->meals_count++;
    philo->eating = 1;
    usleep(philo->shared->tte * 1000);
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_unlock(&philo->left_fork->fork);
}

void    ft_sleep(t_ph *philo)
{
    printf("%d is sleeping\n", philo->id);
    usleep(philo->shared->tts * 1000);
}

void ft_think(t_ph *philo)
{
    printf("%d is thinking\n", philo->id);
}

void	*routine(void *arg)
{
    //    lock r_fork && l_fork
    t_ph *philo = (t_ph *)arg;

    while (1)
    {
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
    }
    return (NULL);
}

int	main(int ac, char **av)
{
	t_shared *shared;

	// parsing begin
	if (ac != 5 && ac != 6)
	{
		printf("You should provide more/less args!\n");
		return (1);
	}
	shared = malloc(sizeof(t_shared));
	if (sanitize(ac, av, shared))
	{
		printf("Args are not valid!\n");
		return (1);
	}


	//  parsing end

	//  init
	shared->dead = 0;

	//  allocate philos
	shared->philos = malloc(shared->n_philos * sizeof(t_ph));
	if (!shared->philos)
		return (1);

    //  allocate forks --> mutexes
	shared->forks = malloc(shared->n_philos * sizeof(t_fork));
	if (!shared->forks)
		return (1);

	//  initialize forks;
	int i = 0;
	while (i < shared->n_philos)
	{
		pthread_mutex_init(&shared->forks[i].fork, NULL);
		i++;
	}

    //  initialize philosopher
	i = 0;
	while (i < shared->n_philos)
	{
		shared->philos[i].id = i + 1; //id
		shared->philos[i].meals_count = 0; //meals counter
		shared->philos[i].shared = shared; //shared

		//  assign forks
        if ((shared->philos[i].id % 2) == 0)
        {
            shared->philos[i].right_fork = &shared->forks[shared->philos[i].id - 1];
            shared->philos[i].left_fork = &shared->forks[(i + 1) % shared->n_philos];
        }
        else
        {
            shared->philos[i].left_fork = &shared->forks[shared->philos[i].id - 1];
            shared->philos[i].right_fork = &shared->forks[(i + 1) % shared->n_philos];
        }
		i++;
	}

	//actual routine
    shared->must_eat_times = -1;

	if (shared->must_eat_times == 0)
	    return 0;
    else if (shared->n_philos == 1)
        return 0;
    else
    {
        int i = 0;
        while (i < shared->n_philos)
        {
            pthread_create(&shared->philos[i].thread, NULL, routine, &shared->philos[i]);
            i++;
        }

    }

    //  monitor
    while (1)
    {

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