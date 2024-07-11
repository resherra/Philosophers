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

static int	pre_check(int ac)
{
	if (ac != 5 && ac != 6)
	{
		printf("You should provide more/less args!\n");
		return (1);
	}
	return (0);
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
	i = 0;
	while (i < shared->n_philos)
	{
		pthread_create(&shared->philos[i].thread, NULL, routine,
				&shared->philos[i]);
		i++;
	}
	while (1)
	{
		if (is_dead(shared) || is_all_full(shared))
			break ;
	}
	i = 0;
	while (i < shared->n_philos)
		pthread_join(shared->philos[i++].thread, NULL);
	return (0);
}
