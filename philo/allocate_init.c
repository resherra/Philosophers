/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 04:51:02 by recherra          #+#    #+#             */
/*   Updated: 2024/07/07 04:51:07 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static int	allocate(t_shared *shared)
{
	shared->philos = malloc(shared->n_philos * sizeof(t_ph));
	if (!shared->philos)
		return (1);
	shared->forks = malloc(shared->n_philos * sizeof(t_fork));
	if (!shared->forks)
		return (1);
	return (0);
}

static void	init_data(t_shared *shared)
{
	shared->dead = false;
	shared->all_full = false;
	shared->phil_is_full = 0;
	shared->start_time = get_curr_time();
	pthread_mutex_init(&shared->dead_mutex, NULL);
	pthread_mutex_init(&shared->full_mutex, NULL);
	pthread_mutex_init(&shared->generic_mutex, NULL);
	pthread_mutex_init(&shared->print_mutex, NULL);
}

static void	init_forks(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philos)
		pthread_mutex_init(&shared->forks[i++].fork, NULL);
}

static void	init_philos(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philos)
	{
		shared->philos[i].id = i + 1;
		shared->philos[i].meals_count = 0;
		shared->philos[i].shared = shared;
		shared->philos[i].last_meal = get_curr_time();
		shared->philos[i].checked = false;
		shared->philos[i].right_fork = &shared->forks[shared->philos[i].id - 1];
		if (shared->philos[i].id == shared->n_philos)
			shared->philos[i].left_fork = &shared->forks[0];
		else
			shared->philos[i].left_fork = &shared->forks[shared->philos[i].id];
		i++;
	}
}

int	init_all(t_shared *shared)
{
	if (allocate(shared))
		return (1);
	init_forks(shared);
	init_philos(shared);
	init_data(shared);
	return (0);
}
