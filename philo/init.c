/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:49:40 by recherra          #+#    #+#             */
/*   Updated: 2024/07/16 00:55:16 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

static int	pre_check(int ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("You should provide more/less args!\n");
		return (1);
	}
	return (0);
}

static int	create_threads(t_shared *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philos)
	{
		if (pthread_create(&shared->philos[i].thread, NULL, routine,
				&shared->philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	destroy_all(t_shared *shared)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&shared->dead_mutex);
	pthread_mutex_destroy(&shared->full_mutex);
	pthread_mutex_destroy(&shared->generic_mutex);
	while (i < shared->n_philos)
		pthread_mutex_destroy(&shared->forks[i++].fork);
}

int	main(int ac, char **av)
{
	t_shared	*shared;
	int			i;

	if (pre_check(ac))
		return (1);
	shared = malloc(sizeof(t_shared));
	if (!shared)
		return (1);
	if (sanitize(ac, av, shared))
		return (1);
	if (init_all(shared))
		return (1);
	if (create_threads(shared))
		return (1);
	while (1)
	{
		if (is_dead(shared) || is_all_full(shared))
			break ;
	}
	i = 0;
	while (i < shared->n_philos)
		pthread_join(shared->philos[i++].thread, NULL);
	destroy_all(shared);
	return (0);
}
