/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:49:40 by recherra          #+#    #+#             */
/*   Updated: 2024/05/24 17:49:45 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int ft_atoi(char *str) {
    int result = 0;
    int i = 0;

    while (str[i] == ' ')
        i++;
    while (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-' || str[i + 1] == '+')
            return -1;
        else if (str[i] == '+')
        {
            i++;
            break;
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
        return -1;
    return result;
}

int sanitize(int ac, char **av, t_shared *shared)
{
    if ((shared->n_philos = ft_atoi(av[1])) == -1)
        return 1;
    else if ((shared->ttd = ft_atoi(av[2])) == -1)
        return 1;
    else if ((shared->tte = ft_atoi(av[3])) == -1)
        return 1;
    else if ((shared->tts = ft_atoi(av[4])) == -1)
        return 1;
    else if (ac == 6)
    {
        if ((shared->must_eat_times = ft_atoi(av[5])) == -1)
            return 1;
    }
    return 0;
}

int main (int ac, char **av)
{
    t_shared *shared;

    if (ac != 5 && ac != 6)
    {
        printf("You should provide more/less args!\n");
        return 1;
    }
    shared = malloc(sizeof(t_shared));
    if (sanitize(ac, av, shared))
    {
        printf("Args are not valid!\n");
        return 1;
    }

    return 0;
}