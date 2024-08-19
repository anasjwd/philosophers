/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 03:29:11 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/19 17:20:16 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_curr_state(int philo_number, char *msg)
{
	int	curr_time;

	curr_time = get_time_from_start();
	printf("%d %d %s\n", curr_time, philo_number, msg);
}
