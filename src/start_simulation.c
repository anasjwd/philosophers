/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:41:11 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/31 02:21:07 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup(t_data *data)
{
	int	idx;

	free(data->sim_over_mutex);
	free(data->printing_mutex);
	idx = 0;
	while (data->philos[idx])
	{
		if (idx + 1 == data->numof_philos)
			free(data->philos[idx]->right_fork);
		else
			free(data->philos[idx]->left_fork);
		free(data->philos[idx]->stats_mutex);
		free(data->philos[idx]);
		idx++;
	}
	free(data->philos);
}

int	start_simulation(t_data *data)
{
	int	idx;

	idx = -1;
	data->start_time = get_curr_time();
	while (data->philos[++idx])
	{
		if (pthread_create(&data->philos[idx]->id, NULL,
				(void *)routine, (void *)data->philos[idx]))
		{
			ft_putstr_fd("Error: thread can't be created\n", 2);
			pthread_mutex_lock(data->sim_over_mutex);
			data->sim_over = 1;
			pthread_mutex_unlock(data->sim_over_mutex);
			break ;
		}
	}
	monitor(data);
	idx = 0;
	while (data->philos[idx])
	{
		if (pthread_join(data->philos[idx]->id, NULL))
			ft_putstr_fd("Error: thread can't be joined\n", 2);
		idx++;
	}
	return (cleanup(data), 0);
}
