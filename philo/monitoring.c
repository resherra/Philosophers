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
    int i = 0;

    while (i < shared->n_philos)
    {
        pthread_mutex_lock(&shared->generic_mutex);
        long last_meal = shared->philos[i].last_meal;
        pthread_mutex_unlock(&shared->generic_mutex);

        if (get_curr_time() > last_meal)
        {
            pthread_mutex_lock(&shared->dead_mutex);
            printf("%d died\n", shared->philos[i].id);
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