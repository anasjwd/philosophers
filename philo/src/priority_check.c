/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 21:59:53 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/19 00:53:43 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_longest_starvation_time(void)
{
	t_philo **philos;
	int		idx;
	int		longest_starvation_time;
	int		starvation_time;

	idx = 1;
	philos = (*simulation_data())->philos;
	pthread_mutex_lock(philos[0]->state_mutex);
	longest_starvation_time = get_time_from_start() - philos[0]->last_meal_time;
	pthread_mutex_unlock(philos[0]->state_mutex);
	while (philos[idx])
	{
		pthread_mutex_lock(philos[idx]->state_mutex);
		starvation_time = get_time_from_start() - philos[idx]->last_meal_time;
		if (starvation_time > longest_starvation_time)
			longest_starvation_time = starvation_time;
		pthread_mutex_unlock(philos[idx]->state_mutex);
		idx++;
	}
	return (longest_starvation_time);
}

int	get_least_numof_meals(void)
{
	int			idx;
	unsigned	least_numof_meals;
	t_philo **philos;

	idx = 1;
	philos = (*simulation_data())->philos;
	pthread_mutex_lock(philos[0]->state_mutex);
	least_numof_meals = philos[0]->num_of_meals;
	pthread_mutex_unlock(philos[0]->state_mutex);
	while (philos[idx])
	{
		pthread_mutex_lock(philos[idx]->state_mutex);
		if (philos[idx]->num_of_meals < least_numof_meals)
			least_numof_meals = philos[idx]->num_of_meals;
		pthread_mutex_unlock(philos[idx]->state_mutex);
		idx++;
	}
	return (least_numof_meals);
}

int	has_priority(t_philo *philo)
{
	unsigned	least_numof_meals;
	long		longest_starvation_time;

	least_numof_meals = get_least_numof_meals();
	longest_starvation_time = get_longest_starvation_time();
	pthread_mutex_lock(philo->state_mutex);
	if (philo->num_of_meals == least_numof_meals
		&& (get_time_from_start() - philo->last_meal_time) >= longest_starvation_time)
	{
		pthread_mutex_unlock(philo->state_mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->state_mutex);
	return (0);
}
