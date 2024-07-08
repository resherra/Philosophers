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

static int allocate(t_shared *shared)
{
    shared->philos = malloc(shared->n_philos * sizeof(t_ph));
    if (!shared->philos)
        return 1;
    shared->forks = malloc(shared->n_philos * sizeof(t_fork));
    if (!shared->forks)
        return (1);
    return 0;
}

static void    init_forks(t_shared *shared)
{
    int i = 0;
    while (i < shared->n_philos)
        pthread_mutex_init(&shared->forks[i++].fork, NULL);
}

static void init_philos(t_shared *shared)
{
    int i = 0;
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
}

int init_all(t_shared *shared)
{
    shared->dead = 0;
    shared->all_full = 0;
    shared->phil_is_full = 0;
    shared->start_time = get_curr_time();
    pthread_mutex_init(&shared->dead_mutex, NULL);
    pthread_mutex_init(&shared->full_mutex, NULL);
    pthread_mutex_init(&shared->eat_mutex, NULL);
    pthread_mutex_init(&shared->generic_mutex, NULL);



    if (allocate(shared))
        return 1;
    init_forks(shared);
    init_philos(shared);
    return 0;
}