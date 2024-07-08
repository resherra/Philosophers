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