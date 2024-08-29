/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:41:11 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/29 09:14:56 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_simulation(t_data *data)
{
	int	idx;

	idx = -1;
	data->start_time = get_curr_time();
	while (data->philos[++idx])
	{
		pthread_create(&data->philos[idx]->id, NULL,
				(void *)routine, (void *)data->philos[idx]);
			//TODO: check if this fails
	}
	monitor(data);
	idx = 0;
	while (data->philos[idx])
	{
		pthread_join(data->philos[idx]->id, NULL);
			//TODO: check if this fails
		idx++;
	}
	return (0);
}
