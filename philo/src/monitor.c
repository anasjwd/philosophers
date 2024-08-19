/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 02:22:50 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/19 17:53:31 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_philosophers_done_eating(void)
{
	t_philo	**philos;
	int		idx;

	philos = (*simulation_data())->philos;
	idx = 0;
	while (philos[idx])
	{
		pthread_mutex_lock(philos[idx]->state_mutex);
		if (philos[idx]->num_of_meals != (*simulation_data())->num_of_meals)
		{
			pthread_mutex_unlock(philos[idx]->state_mutex);
			return (0);
		}
		pthread_mutex_unlock(philos[idx]->state_mutex);
		idx++;
	}
	pthread_mutex_lock((*simulation_data())->sim_over_mutex);
	(*simulation_data())->sim_over = 1;
	pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
	return (1);
}

int	any_philosopher_starved(void)
{
	t_philo	**philos;
	int		idx;

	philos = (*simulation_data())->philos;
	idx = 0;
	while (philos[idx])
	{
		pthread_mutex_lock(philos[idx]->state_mutex);
		if (get_time_from_start() - philos[idx]->last_meal_time
			> (*simulation_data())->time_to_die)
		{
			pthread_mutex_lock((*simulation_data())->sim_over_mutex);
			(*simulation_data())->sim_over = 1;
			pthread_mutex_unlock((*simulation_data())->sim_over_mutex);
			put_curr_state(philos[idx]->number, "died");
			pthread_mutex_unlock(philos[idx]->state_mutex);
			return (1);
		}
		pthread_mutex_unlock(philos[idx]->state_mutex);
		idx++;
	}
	return (0);
}

int	monitor(void)
{
	while (TRUE)
	{
		if (all_philosophers_done_eating())
			return (1);
		else if (any_philosopher_starved())
			return (1);
	}
	return (0);
}
