/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:17:35 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/31 02:42:19 by ajawad           ###   ########.fr       */
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

long	ft_atoi(const char *nptr)
{
	int				i;
	unsigned long	result;

	if (nptr == NULL)
		return (INVALID);
	i = 0;
	result = 0;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
		return (INVALID);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result *= 10;
		result += nptr[i] - '0';
		i++;
	}
	if (nptr[i] != '\0')
		return (INVALID);
	return (result);
}

int	handle_invalid_input(char *arg, char *msg)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": invalid ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (1);
}

int	parsing(int ac, char **av, t_data *data)
{
	data->numof_philos = ft_atoi(av[1]);
	if (data->numof_philos == INVALID)
		return (handle_invalid_input(av[1], "number_of_philosophers"));
	data->time_to_die = ft_atoi(av[2]);
	if (data->time_to_die == INVALID)
		return (handle_invalid_input(av[2], "time_to_die"));
	data->time_to_eat = ft_atoi(av[3]);
	if (data->time_to_eat == INVALID)
		return (handle_invalid_input(av[3], "time_to_eat"));
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_sleep == INVALID)
		return (handle_invalid_input(av[4], "time_to_sleep"));
	if (ac == 6)
	{
		data->numof_meals = ft_atoi(av[5]);
		if (data->numof_meals == INVALID)
			return (handle_invalid_input(av[5],
					"number_of_times_each_philosopher_must_eat"));
	}
	else
		data->numof_meals = UNAVAILABLE;
	return (0);
}

int	check_numof_args(int ac)
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
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (0);
}
