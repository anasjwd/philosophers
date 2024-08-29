/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajawad <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:01:11 by ajawad            #+#    #+#             */
/*   Updated: 2024/08/28 16:02:53 by ajawad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

int	print_curr_state(t_philo *philo, char *state)
{
	if (simulation_is_over(philo))
		return (1);
	pthread_mutex_lock(philo->data->printing_mutex);
	printf("%ld %d %s\n", get_curr_time() - philo->data->start_time,
			philo->number, state);
	pthread_mutex_unlock(philo->data->printing_mutex);
	return (0);
}

void	print_death_msg(t_philo *philo)
{
	pthread_mutex_lock(philo->data->printing_mutex);
	printf("%ld %d died\n", get_curr_time() - philo->data->start_time,
			philo->number);
	pthread_mutex_unlock(philo->data->printing_mutex);
}
