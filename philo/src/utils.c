/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:41:25 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/19 17:52:59 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	simulation_is_over(void)
{
	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	if ((*simulation_data())->sim_over == 1)
	{
		pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
	return (0);
}

void	msleep(size_t ms)
{
	size_t	start;

	start = get_time_from_start();
	while (get_time_from_start() - start < ms)
		usleep(1);
}

long	get_time_in_milliseconds(struct timeval *tv)
{
	return ((tv->tv_sec * 1000) + (tv->tv_usec / 1000));
}

int	get_curr_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (get_time_in_milliseconds(&current_time));
}

long	get_time_from_start(void)
{
	return (get_curr_time_ms() - (*simulation_data())->start_time);
}
