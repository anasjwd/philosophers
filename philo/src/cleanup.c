/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:35:13 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/19 19:46:40 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	do_cleanup(t_simulation_data *simulation_data)
{
	int	idx;

	idx = 0;
	while (simulation_data->philos && simulation_data->philos[idx])
	{
		free(simulation_data->philos[idx]->state_mutex);
		free(simulation_data->philos[idx]->fork);
		free(simulation_data->philos[idx]);
		idx++;
	}
	free(simulation_data->philos);
	free(simulation_data->sim_over_mutex);
	free(simulation_data);
}
