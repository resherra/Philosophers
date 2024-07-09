/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 02:02:31 by recherra          #+#    #+#             */
/*   Updated: 2024/07/09 02:02:32 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	*philo_routine(void *arg)
{
    t_ph *philo = (t_ph *)arg;


    if (!(philo->id % 2))
        sleep__(philo);
    while (1)
    {
        pthread_mutex_lock(&philo->shared->dead_mutex);
        if (philo->shared->dead)
        {
            pthread_mutex_unlock(&philo->shared->dead_mutex);
            break;
        }
        pthread_mutex_unlock(&philo->shared->dead_mutex);
        think__(philo);
        eat__(philo);
        sleep__(philo);
    }
    return (NULL);
}

