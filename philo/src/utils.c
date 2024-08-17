/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 21:41:25 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/15 02:34:20 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_milliseconds(struct timeval *tv)
{
	return (tv->tv_sec * 1000) + (tv->tv_usec / 1000);
}

int	get_curr_time_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (get_time_in_milliseconds(&current_time));
}

long	get_time_from_start(void)
{
	return (get_curr_time_ms() - (*simulation_data())->start_time);
}
