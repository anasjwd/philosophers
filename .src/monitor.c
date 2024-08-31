/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 06:45:05 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/31 02:22:35 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philos_done_eating(t_data *data)
{
	int	idx;

	idx = 0;
	if (data->numof_meals == UNAVAILABLE)
		return (0);
	while (data->philos[idx])
	{
		pthread_mutex_lock(data->philos[idx]->stats_mutex);
		if (data->philos[idx]->numof_meals < data->numof_meals)
		{
			pthread_mutex_unlock(data->philos[idx]->stats_mutex);
			return (0);
		}
		pthread_mutex_unlock(data->philos[idx]->stats_mutex);
		idx++;
	}
	pthread_mutex_lock(data->sim_over_mutex);
	data->sim_over = 1;
	pthread_mutex_unlock(data->sim_over_mutex);
	return (1);
}

int	any_philos_starved(t_data *data)
{
	int	idx;

	idx = 0;
	while (data->philos[idx])
	{
		pthread_mutex_lock(data->philos[idx]->stats_mutex);
		if (get_curr_time() - data->philos[idx]->last_meal_time
			> data->time_to_die)
		{
			pthread_mutex_lock(data->sim_over_mutex);
			data->sim_over = 1;
			pthread_mutex_unlock(data->sim_over_mutex);
			pthread_mutex_unlock(data->philos[idx]->stats_mutex);
			print_death_msg(data->philos[idx]);
			return (1);
		}
		pthread_mutex_unlock(data->philos[idx]->stats_mutex);
		idx++;
	}
	return (0);
}

void	monitor(t_data *data)
{
	if (data->numof_philos == 0)
		return ;
	while (TRUE)
	{
		if (philos_done_eating(data))
			return ;
		if (any_philos_starved(data))
			return ;
	}
}
