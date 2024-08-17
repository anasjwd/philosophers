/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 03:29:06 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/15 03:00:12 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_simulation_data	**simulation_data(void)
{
	static t_simulation_data	*simulation_data;

	return (&simulation_data);
}

int	main(int ac, char **av)
{
	if (check_num_of_arguments(ac))
		return (1);
	*simulation_data() = malloc(sizeof(t_simulation_data));
	if (*simulation_data() == NULL)
	{
		ft_putstr_fd("Error: out of memory\n", 2);
		return (1);
	}
	if (parsing(*simulation_data(), av, ac))
		return (1);
	if (start_simulation(*simulation_data()))
		return (1);
	return (0);
}
