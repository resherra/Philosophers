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

//  eat
static void    ft_eat(t_ph *philo)
{
    pthread_mutex_lock(&philo->right_fork->fork);
    print("has taken a fork", philo);
    pthread_mutex_lock(&philo->left_fork->fork);
    print("has taken a fork", philo);
    //check if philo is dead then print
    print("is eating", philo);
    ft_usleep(philo->shared->tte * 1000);
    philo->meals_count++;
    pthread_mutex_lock(&philo->shared->generic_mutex);
    philo->last_meal = get_curr_time();
    pthread_mutex_unlock(&philo->shared->generic_mutex);
    pthread_mutex_unlock(&philo->right_fork->fork);
    pthread_mutex_unlock(&philo->left_fork->fork);
}

//  sleep
static void    ft_sleep(t_ph *philo)
{
    print("is sleeping", philo);
    ft_usleep(philo->shared->tts * 1000);
}

//  think
static void ft_think(t_ph *philo)
{
    print("is thinking", philo);
}

void	*routine(void *arg)
{
    t_ph *philo = (t_ph *)arg;
    int is_dead;


//    if (philo->id % 2 == 0)
//        usleep(15000);
    while (1)
    {
        pthread_mutex_lock(&philo->shared->dead_mutex);
        is_dead = philo->shared->dead;
        pthread_mutex_unlock(&philo->shared->dead_mutex);
        if (is_dead)
            break;
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);

    }
    return (NULL);
}