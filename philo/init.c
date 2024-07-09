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

	// parsing
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

	//data look-up
    //	printf("philos number: %d\ntime to die: %d\ntime to eat: %d\ntime to sleep: %d\nmust eat times: %d\n",
    //	        shared->n_philos, shared->ttd, shared->tte, shared->tts, shared->must_eat_times);

	//  allocate && init
    if (init_all(shared))
	    return 1;

	//monitor

	//philos
	int i = 0;
	while (i < shared->n_philos)
	{
	    pthread_create(&shared->philos[i].thread, NULL, philo_routine, &shared->philos[i]);
	    i++;
	}

	while (1)
	{
	    if (is_dead(shared) || is_all_full(shared))
	        break;
	}

	i = 0;
	while (i < shared->n_philos)
	{
		pthread_join(shared->philos[i].thread, NULL);
        i++;
	}
    return (0);
}