/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:47:51 by recherra          #+#    #+#             */
/*   Updated: 2024/07/08 02:47:52 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int	is_dead(t_shared *shared)
{
	int		i;
	long	last_meal;

	i = 0;
	while (i < shared->n_philos)
	{
		pthread_mutex_lock(&shared->generic_mutex);
		last_meal = shared->philos[i].last_meal;
		pthread_mutex_unlock(&shared->generic_mutex);
		if (get_curr_time() - last_meal >= shared->ttd)
		{
			pthread_mutex_unlock(&shared->philos[i].right_fork->fork);
			print("died", &shared->philos[i]);
			pthread_mutex_lock(&shared->dead_mutex);
			shared->dead = true;
			pthread_mutex_unlock(&shared->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_is_all_full(t_shared *shared)
{
	if (shared->phil_is_full == shared->n_philos)
	{
		pthread_mutex_lock(&shared->full_mutex);
		shared->all_full = true;
		pthread_mutex_unlock(&shared->full_mutex);
		return (1);
	}
	return (0);
}

int	is_all_full(t_shared *shared)
{
	int	i;
	int	meals_count;

	i = 0;
	if (shared->must_eat_times == -1)
		return (0);
	while (i < shared->n_philos)
	{
		pthread_mutex_lock(&shared->generic_mutex);
		meals_count = shared->philos[i].meals_count;
		pthread_mutex_unlock(&shared->generic_mutex);
		if (meals_count == shared->must_eat_times
			&& shared->philos[i].checked == false)
		{
			shared->phil_is_full++;
			shared->philos[i].checked = true;
		}
		i++;
	}
	if (check_is_all_full(shared))
		return (1);
	return (0);
}
