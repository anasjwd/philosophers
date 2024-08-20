/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 03:29:22 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/19 19:43:13 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*initialize_mutex(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
	{
		ft_putstr_fd("Fatal: allocation failed\n", 2);
		return (NULL);
	}
	pthread_mutex_init(mutex, NULL);
	return (mutex);
}

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
		philos[idx]->fork = initialize_mutex();
		philos[idx]->state_mutex = initialize_mutex();
		if (!philos[idx]->fork || !philos[idx]->state_mutex)
		{
			ft_putstr_fd("Fatal: allocation failed\n", 2);
			return (philos[idx + 1] = NULL, 1);
		}
		idx++;
	}
	return (0);
}

int	create_philos(t_simulation_data *simulation_data)
{
	int	idx;

	idx = 0;
	simulation_data->start_time = get_curr_time_ms();
	while (simulation_data->philos[idx])
	{
		if (pthread_create(&simulation_data->philos[idx]->id, NULL,
				(void *)routine, (void *)simulation_data->philos[idx]))
		{
			ft_putstr_fd("Error: Thread creation failed\n", 2);
			pthread_mutex_lock(simulation_data->sim_over_mutex);
			simulation_data->sim_over = 1;
			pthread_mutex_unlock(simulation_data->sim_over_mutex);
			return (1);
		}
		idx++;
	}
	return (0);
}

void	join_philos(t_simulation_data *simulation_data)
{
	int	idx;

	idx = 0;
	while (simulation_data->philos[idx])
	{
		if (pthread_join(simulation_data->philos[idx]->id, NULL))
			ft_putstr_fd("Error: Thread can't be joined\n", 2);
		idx++;
	}
}

int	start_simulation(t_simulation_data *simulation_data)
{
	simulation_data->philos = malloc(sizeof(t_philo *)
			* (simulation_data->num_of_philos + 1));
	if (simulation_data->philos == NULL)
	{
		ft_putstr_fd("Fatal: allocation failed\n", 2);
		return (do_cleanup(simulation_data), 1);
	}
	simulation_data->philos[simulation_data->num_of_philos] = NULL;
	if (initialize_philos(simulation_data->philos,
			simulation_data->num_of_philos))
		return (do_cleanup(simulation_data), 1);
	simulation_data->sim_over = 0;
	simulation_data->sim_over_mutex = initialize_mutex();
	if (simulation_data->sim_over_mutex == NULL)
		return (do_cleanup(simulation_data), 1);
	if (create_philos(simulation_data))
		return (do_cleanup(simulation_data), 1);
	monitor();
	join_philos(simulation_data);
	do_cleanup(simulation_data);
	return (0);
}
