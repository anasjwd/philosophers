/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 03:29:16 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/16 03:11:40 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*ft_strcpy(char *dst, char *src)
{
	int	idx;

	idx = -1;
	while (src[++idx])
		dst[idx] = src[idx];
	dst[idx] = '\0';
	return (dst);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	result;
	int		fresult;

	if (nptr == NULL)
		return (0);
	i = 0;
	sign = 1;
	result = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	if (nptr[i] != '\0')
		return (INVALID);
	return (fresult = result * sign, fresult);
}

int	handle_invalid_input(char *arg, char *msg)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": invalid ", 2);
	ft_putstr_fd(msg, 2);
	return (1);
}

int	parsing(t_simulation_data *simulation_data, char **av, int ac)
{
	simulation_data->num_of_philos = ft_atoi(av[1]);
	if (simulation_data->num_of_philos == (unsigned)INVALID)
		return (handle_invalid_input(av[1], "number_of_philosophers\n"));
	simulation_data->time_to_die = ft_atoi(av[2]);
	if (simulation_data->time_to_die == (unsigned)INVALID)
		return (handle_invalid_input(av[2], "time_to_die\n"));
	simulation_data->time_to_eat = ft_atoi(av[3]);
	if (simulation_data->time_to_eat == (unsigned)INVALID)
		return (handle_invalid_input(av[3], "time_to_eat\n"));
	simulation_data->time_to_sleep = ft_atoi(av[4]);
	if (simulation_data->time_to_sleep == (unsigned)INVALID)
		return (handle_invalid_input(av[4], "time_to_sleep\n"));
	if (ac == 6)
		simulation_data->num_of_meals = ft_atoi(av[5]);
	else
		simulation_data->num_of_meals = -1;
	if (simulation_data->num_of_meals == (unsigned)INVALID)
		return (handle_invalid_input(av[5],
				"number_of_times_each_philosopher_must_eat\n"));
	return (0);
}

int	check_num_of_arguments(int ac)
{
	char	args[5][23];

	if (ac > 6)
	{
		ft_putstr_fd("Error: too many arguments\n", 2);
		return (1);
	}
	ft_strcpy(args[0], "number_of_philosophers");
	ft_strcpy(args[1], "time_to_die");
	ft_strcpy(args[2], "time_to_eat");
	ft_strcpy(args[3], "time_to_sleep");
	if (ac < 5)
	{
		ft_putstr_fd("Error: Missing argument: ", 2);
		ft_putstr_fd(args[ac - 1], 2);
		ft_putchar_fd('\n', 2);
		return (1);
	}
	return (0);
}
