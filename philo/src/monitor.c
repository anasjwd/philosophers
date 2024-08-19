/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 02:22:50 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/19 03:41:32 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philosophers_done_eating(t_philo **philos)
{
	int	idx;

	idx = 0;
	while (philos[idx])
	{
		if (philos[idx]->num_of_meals != (*simulation_data())->num_of_meals)
			return (0);
		idx++;
	}
	return (1);
}

int	any_philosopher_starved(t_philo **philos)
{
	int	idx;

	idx = 0;
	while (philos[idx])
	{
		if (get_time_from_start() - philos[idx]->last_meal_time
				> (*simulation_data())->time_to_die)
			return (1);
		idx++;
	}
	return (0);
}

int	monitor(t_simulation_data *simulation_data)
{
	t_philo	**philos;
	int		idx;

	philos = simulation_data->philos;
	while (TRUE)
	{
		idx = 0;
		while (philos[idx])
		{
			pthread_mutex_lock(philos[idx]->state_mutex);
			pthread_mutex_lock(simulation_data->sim_over_mutex);
			if (philos[idx]->num_of_meals == simulation_data->num_of_meals)
			{
				put_curr_state(idx + 1, "died1");
				simulation_data->sim_over = 1;
				pthread_mutex_unlock(philos[idx]->state_mutex);
				pthread_mutex_unlock(simulation_data->sim_over_mutex);
				return (1);
			}
			else if (get_time_from_start() - philos[idx]->last_meal_time > simulation_data->time_to_die)
			{
				put_curr_state(idx + 1, "died2");
				simulation_data->sim_over = 1;
				pthread_mutex_unlock(philos[idx]->state_mutex);
				pthread_mutex_unlock(simulation_data->sim_over_mutex);
				return (1);
			}
			pthread_mutex_unlock(simulation_data->sim_over_mutex);
			pthread_mutex_unlock(philos[idx]->state_mutex);
			idx++;
		}
	}
	return (0);
}
