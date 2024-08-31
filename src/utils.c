/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:04:49 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/29 14:30:25 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*alloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_putstr_fd("Fatal: allocation failed\n", 2);
		return (NULL);
	}
	return (ptr);
}

long	get_curr_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	msleep(size_t ms)
{
	size_t	start;

	start = get_curr_time();
	while ((get_curr_time() - start) < ms)
		usleep(500);
}

int	simulation_is_over(t_philo *philo)
{
	pthread_mutex_lock(philo->data->sim_over_mutex);
	if (philo->data->sim_over == 1)
	{
		pthread_mutex_unlock(philo->data->sim_over_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->data->sim_over_mutex);
	return (0);
}

void	destroy_philos(t_philo **philos)
{
	int	idx;

	idx = 0;
	while (philos[idx])
	{
		free(philos[idx]->left_fork);
		free(philos[idx]->stats_mutex);
		free(philos[idx]);
		idx++;
	}
	free(philos);
}
