/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:46:50 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/29 09:19:29 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*initialize_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = alloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
		return (NULL);
	pthread_mutex_init(mutex, NULL);
	return (mutex);
}

int	initialize_right_forks(t_philo **philos, int numof_philos)
{
	int				idx;
	pthread_mutex_t	*holder;

	idx = 0;
	while (philos[idx])
	{
		philos[idx]->right_fork = philos[(idx + 1) % numof_philos]->left_fork;
		if (idx + 1 == numof_philos)
		{
			holder = philos[idx]->left_fork;
			philos[idx]->left_fork = philos[idx]->right_fork;
			philos[idx]->right_fork = holder;
		}
		idx++;
	}
	return (0);
}

int	initialize_philos(t_data *data)
{
	int	idx;

	idx = 0;
	data->philos = alloc(sizeof(t_philo *) * (data->numof_philos + 1));
	if (data->philos == NULL)
		return (1);
	while (idx < data->numof_philos)
	{
		data->philos[idx] = alloc(sizeof(t_philo));
		if (data->philos[idx] == NULL)
			return (1);
		data->philos[idx]->number = idx + 1;
		data->philos[idx]->numof_meals = 0;
		data->philos[idx]->last_meal_time = get_curr_time();
		data->philos[idx]->left_fork = initialize_mutex();
			// TODO:check for return value
		data->philos[idx]->stats_mutex = initialize_mutex();
			// TODO:check for return value
		data->philos[idx]->data = data;
		idx++;
	}
	data->philos[idx] = NULL;
	return (0);
}

int	initializing(t_data *data)
{
	data->sim_over = 0;
	data->sim_over_mutex = initialize_mutex();
		// TODO:check for return value
	data->printing_mutex = initialize_mutex();
		// TODO:check for return value
	initialize_philos(data);
		// TODO:check for return value
	initialize_right_forks(data->philos, data->numof_philos);
		// TODO:check for return value
	return (0);
}
