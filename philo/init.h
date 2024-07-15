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

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_shared	t_shared;

typedef struct s_fork
{
	pthread_mutex_t		fork;
}						t_fork;

typedef struct s_ph
{
	int					id;
	long				last_meal;
	int					meals_count;
	bool				checked;
	pthread_t			thread;
	t_fork				*right_fork;
	t_fork				*left_fork;
	t_shared			*shared;
}						t_ph;

typedef struct s_shared
{
	int					n_philos;
	int					ttd;
	int					tte;
	int					tts;
	int					must_eat_times;
	int					phil_is_full;
	long				start_time;
	bool				dead;
	bool				all_full;
	t_ph				*philos;
	t_fork				*forks;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		full_mutex;
	pthread_mutex_t		generic_mutex;
	pthread_mutex_t		print_mutex;
}						t_shared;

int						args_error_handling(char *str);
int						sanitize(int ac, char **av, t_shared *shared);

long					get_curr_time(void);
int						ft_atoi(char *str);
void					ft_usleep(size_t milliseconds);
void					print(char *msg, t_ph *philo);

int						init_all(t_shared *shared);

void					eat__(t_ph *philo);
void					sleep__(t_ph *philo);
void					think__(t_ph *philo);

void					*routine(void *arg);

int						is_dead(t_shared *shared);
int						is_all_full(t_shared *shared);

#endif
