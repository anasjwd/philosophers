/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 03:29:22 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/16 03:06:24 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_philos(t_philo **philos, int num_of_philos)
{
	int	idx;

	idx = 0;
	while (idx < num_of_philos)
	{
		philos[idx] = malloc(sizeof(t_philo));
		if (philos[idx] == NULL)
		{
			ft_putstr_fd("Fatal: allocation failed\n", 2);
			return (1);
		}
		philos[idx]->number = idx + 1;
		philos[idx]->num_of_meals = 0;
		philos[idx]->last_meal_time = 0;
		philos[idx]->fork = malloc(sizeof(pthread_mutex_t));
		philos[idx]->state_mutex = malloc(sizeof(pthread_mutex_t));
		if (!philos[idx]->fork || !philos[idx]->state_mutex)
		{
			ft_putstr_fd("Fatal: allocation failed\n", 2);
			return (1);
		}
		pthread_mutex_init(philos[idx]->fork, NULL);
		pthread_mutex_init(philos[idx]->state_mutex, NULL);
		idx++;
	}
	return (0);
}

int	start_simulation(t_simulation_data *simulation_data)
{
	unsigned int	idx;

	simulation_data->philos = malloc(sizeof(t_philo *)
			* (simulation_data->num_of_philos + 1));
	if (simulation_data->philos == NULL)
	{
		ft_putstr_fd("Fatal: allocation failed\n", 2);
		return (1);
	}
	simulation_data->philos[simulation_data->num_of_philos] = NULL;
	if (initialize_philos(simulation_data->philos,
			simulation_data->num_of_philos))
		return (1);
	idx = 0;
	simulation_data->sim_over = 0;
	simulation_data->sim_over_mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(simulation_data->sim_over_mutex, NULL);
	simulation_data->start_time = get_curr_time_ms();
	while (simulation_data->philos[idx])
	{
		pthread_create(&simulation_data->philos[idx]->id, NULL, 
				(void *)routine, (void *)simulation_data->philos[idx]);
		idx++;
	}
	monitor(simulation_data);
	idx = 0;
	while (simulation_data->philos[idx])
		pthread_join(simulation_data->philos[idx++]->id, NULL);
	return (0);
}
