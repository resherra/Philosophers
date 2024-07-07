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