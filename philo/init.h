/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:49:49 by recherra          #+#    #+#             */
/*   Updated: 2024/05/24 17:49:51 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
#define INIT_H

#include <stdio.h> //printf
#include <string.h> //memset
#include <stdlib.h> // malloc, free
#include <unistd.h> //usleep
#include <sys/time.h> //gettimeofday
#include <pthread.h> //pthread: create, detach, join | mutex: init, lock, unlock, destroy

typedef struct s_shared t_shared;

typedef struct s_fork
{
    pthread_mutex_t fork;
    int id;
} t_fork;

typedef struct s_ph
{
    int id;
    int meals;
    pthread_t thread;
    t_fork *right_fork;
    t_fork *left_fork;
    t_shared *shared;
} t_ph;


typedef struct s_shared
{
    int n_philos;
    int ttd;
    int tte;
    int tts;
    int must_eat_times;
    int start_time;
    t_ph *philos;
    t_fork *forks;
} t_shared;


#endif