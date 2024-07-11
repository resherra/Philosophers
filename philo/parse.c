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

int	args_error_handling(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	sanitize(int ac, char **av, t_shared *shared)
{
	shared->n_philos = ft_atoi(av[1]);
	if (shared->n_philos == -1)
		return (args_error_handling("Invalid philos number!"));
	shared->ttd = ft_atoi(av[2]);
	if (shared->ttd == -1)
		return (args_error_handling("Invalid time to die!"));
	shared->tte = ft_atoi(av[3]);
	if (shared->tte == -1)
		return (args_error_handling("Invalid time to eat!"));
	shared->tts = ft_atoi(av[4]);
	if (shared->tts == -1)
		return (args_error_handling("Invalid time to sleep!"));
	if (ac == 6)
	{
		shared->must_eat_times = ft_atoi(av[5]);
		if (shared->must_eat_times == -1 || !shared->must_eat_times)
			return (args_error_handling("Invalid must eat times!"));
	}
	else
		shared->must_eat_times = -1;
	return (0);
}
