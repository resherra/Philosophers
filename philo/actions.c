/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:31:20 by recherra          #+#    #+#             */
/*   Updated: 2024/07/16 00:54:27 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

void	print(char *msg, t_ph *philo)
{
	pthread_mutex_lock(&philo->shared->dead_mutex);
	if (!philo->shared->dead)
		printf("%ld %d %s\n", get_curr_time() - philo->shared->start_time,
			philo->id, msg);
	pthread_mutex_unlock(&philo->shared->dead_mutex);
}

void	eat__(t_ph *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork);
	print("has taken a fork", philo);
	pthread_mutex_lock(&philo->left_fork->fork);
	print("has taken a fork", philo);
	print("is eating", philo);
	pthread_mutex_lock(&philo->shared->generic_mutex);
	philo->last_meal = get_curr_time();
	philo->meals_count++;
	pthread_mutex_unlock(&philo->shared->generic_mutex);
	ft_usleep(philo->shared->tte);
	pthread_mutex_unlock(&philo->right_fork->fork);
	pthread_mutex_unlock(&philo->left_fork->fork);
}

void	sleep__(t_ph *philo)
{
	print("is sleeping", philo);
	ft_usleep(philo->shared->tts);
}

void	think__(t_ph *philo)
{
	print("is thinking", philo);
}

void	*routine(void *arg)
{
	t_ph	*philo;

	philo = (t_ph *)arg;
	if (!(philo->id % 2))
		ft_usleep(20);
	while (1)
	{
		pthread_mutex_lock(&philo->shared->dead_mutex);
		pthread_mutex_lock(&philo->shared->full_mutex);
		if (philo->shared->dead || philo->shared->all_full)
		{
			pthread_mutex_unlock(&philo->shared->dead_mutex);
			pthread_mutex_unlock(&philo->shared->full_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->shared->dead_mutex);
		pthread_mutex_unlock(&philo->shared->full_mutex);
		eat__(philo);
		sleep__(philo);
		think__(philo);
	}
	return (NULL);
}
