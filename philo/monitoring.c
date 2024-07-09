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

int is_dead(t_shared *shared)
{
    int i;

    i = 0;
    while (i < shared->n_philos)
    {
        pthread_mutex_lock(&shared->generic_mutex);
        long last_meal = shared->philos[i].last_meal;
        pthread_mutex_unlock(&shared->generic_mutex);
        if (get_curr_time() - last_meal >= shared->ttd)
        {
            pthread_mutex_lock(&shared->dead_mutex);
            shared->dead = true;
            pthread_mutex_unlock(&shared->dead_mutex);
            print("died", &shared->philos[i]);
            return 1;
        }
        i++;
    }
    return 0;
}

int is_all_full(t_shared *shared)
{
    int i = 0;

    if (shared->must_eat_times == -1)
        return 0;
    while (i < shared->n_philos)
    {
        if (shared->philos[i].meals_count >= shared->must_eat_times)
        {
            shared->phil_is_full++;
        }
        i++;
    }

//    check how many number of philos are full
    if (shared->phil_is_full == shared->n_philos)
    {
        shared->all_full = 1;
        return 1;
    }
    return 0;
}