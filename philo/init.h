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
# define INIT_H


# include <pthread.h>  //pthread: create, detach, join | mutex: init, lock,	unlock, destroy
# include <stdio.h>    //printf
# include <stdlib.h>   // malloc, free
# include <string.h>   //memset
# include <sys/time.h> //gettimeofday
# include <unistd.h>   //usleep

typedef struct s_shared	t_shared;

typedef struct s_fork
{
	pthread_mutex_t		fork; //fork || mutex
}						t_fork;

typedef struct s_ph
{
    int					id; //philosopher id
	int					meals_count; //meals count;
    int                 eating; //is currently eating flag | 0 or 1
    int                 last_meal; //last meal
    pthread_t			thread; //thread
	t_fork				*right_fork; //rf
	t_fork				*left_fork; //lf
	t_shared			*shared; //pointer to global data
}						t_ph;

typedef struct s_shared
{
	int					n_philos; //number of philos
	int					ttd; //time to die
	int					tte; //time to eat
	int					tts; //time to sleep
	int					must_eat_times; //optional
	int                 dead; //dead flag | 0 or 1
	int                 all_full; //all full flag | 0 or 1
	t_ph				*philos; //philosophers
	t_fork				*forks; //forks
}						t_shared;

#endif