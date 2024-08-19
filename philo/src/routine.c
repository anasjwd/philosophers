/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 22:48:10 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/18 22:19:01 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *holder)
{
	t_philo	*philo;

	philo = (t_philo *)holder;
	if (philo->number % 2 == 0)
		msleep(1);
	while (TRUE)
	{
		if (ft_eat(philo))
			return (NULL);
		if (ft_sleep(philo))
			return (NULL);
		if (ft_think(philo))
			return (NULL);
	}
	return (NULL);
}
