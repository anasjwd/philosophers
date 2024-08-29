/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:15:49 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/28 20:04:59 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (check_numof_args(ac))
		return (1);
	if (parsing(ac, av, &data))
		return (1);
	if (initializing(&data))
		return (1);
	if (start_simulation(&data))
		return (1);
	return (0);
}
