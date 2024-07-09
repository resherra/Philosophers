/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:31:20 by recherra          #+#    #+#             */
/*   Updated: 2024/07/08 02:31:22 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void print(char *msg, t_ph *philo)
{
    printf("%ld %d %s\n", get_curr_time() - philo->shared->start_time, philo->id, msg);
}

void    eat__(t_ph *philo)
{
    pthread_mutex_lock(&philo->left_fork->fork);
    print("has taken a fork", philo);
    pthread_mutex_lock(&philo->right_fork->fork);
    print("has taken a fork", philo);
    print("is eating", philo);
    ft_usleep(philo->shared->tte);
    philo->meals_count++;
    pthread_mutex_lock(&philo->shared->generic_mutex);
    philo->last_meal = get_curr_time();
    pthread_mutex_unlock(&philo->shared->generic_mutex);
    pthread_mutex_unlock(&philo->left_fork->fork);
    pthread_mutex_unlock(&philo->right_fork->fork);
}

void    sleep__(t_ph *philo)
{
    print("is sleeping", philo);
    ft_usleep(philo->shared->tts);
}

void think__(t_ph *philo)
{
    print("is thinking", philo);
}