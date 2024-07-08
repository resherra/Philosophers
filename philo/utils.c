/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 04:09:06 by recherra          #+#    #+#             */
/*   Updated: 2024/07/07 04:09:08 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int	ft_atoi(char *str)
{
    int	result;
    int	i;

    result = 0;
    i = 0;
    while (str[i] == ' ')
        i++;
    while (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-' || str[i + 1] == '+')
            return (-1);
        else if (str[i] == '+')
        {
            i++;
            break ;
        }
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result *= 10;
        result += str[i] - '0';
        i++;
    }
    if (str[i])
        return (-1);
    return (result);
}

long get_curr_time()
{
    struct timeval	time;

    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}


static long get_elapsed(struct timeval start, struct timeval end)
{
    return (end.tv_sec - start.tv_sec) * 1000000L + (end.tv_usec - start.tv_usec);
}

void ft_usleep(long dur)
{
    struct timeval start;
    struct timeval curr;
    long elapsed;
    long rem;

    gettimeofday(&start, NULL);
    elapsed = 0;
    while (elapsed < dur)
    {
        gettimeofday(&curr, NULL);
        elapsed = get_elapsed(start, curr);
        rem = dur - elapsed;

        if (rem > 1000)
            usleep(rem / 2);
    }
}