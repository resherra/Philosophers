/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: recherra <recherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:44:07 by recherra          #+#    #+#             */
/*   Updated: 2024/07/08 02:44:09 by recherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

int args_error_handling(char *str)
{
    printf("%s\n", str);
    return 1;
}

//sanitize the input
int	sanitize(int ac, char **av, t_shared *shared)
{
    if ((shared->n_philos = ft_atoi(av[1])) == -1)
        return args_error_handling("Invalid philos number!");
    else if ((shared->ttd = ft_atoi(av[2])) == -1)
        return args_error_handling("Invalid time to die!");
    else if ((shared->tte = ft_atoi(av[3])) == -1)
        return args_error_handling("Invalid time to eat!");
    else if ((shared->tts = ft_atoi(av[4])) == -1)
        return args_error_handling("Invalid time to sleep!");
    else if (ac == 6)
    {
        if ((shared->must_eat_times = ft_atoi(av[5])) == -1)
            return args_error_handling("Invalid must eat times!");
    }
    return (0);
}