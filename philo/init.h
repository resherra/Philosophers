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
    long                last_meal; //last meal
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
	int                 phil_is_full; //increment the full philos
	long                start_time;
	t_ph				*philos; //philosophers
	t_fork				*forks; //forks
    pthread_mutex_t     dead_mutex;
    pthread_mutex_t     full_mutex;
    pthread_mutex_t     eat_mutex;
    pthread_mutex_t     generic_mutex;


}						t_shared;



//parsing
int	sanitize(int ac, char **av, t_shared *shared);
int args_error_handling(char *str);

//utils
int	ft_atoi(char *str);
long get_curr_time();
void ft_usleep(long dur);

//allocate & init
int init_all(t_shared *shared);

//ACTIONS
void	*routine(void *arg);

//monitoring
int is_dead(t_shared *shared);
int is_all_full(t_shared *shared);


#endif