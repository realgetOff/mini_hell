/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 00:04:37 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/16 20:39:25 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	add_to_history_buffer(char *input, t_data *data)
{
	if (data->s_history->history_buffer[data->s_history->history_index])
		free(data->s_history->history_buffer[data->s_history->history_index]);
	data->s_history->history_buffer
	[data->s_history->history_index] = ft_strdup(input);
	data->s_history->history_index = (data->s_history->history_index + 1)
		% HISTORY_SIZE;
	if (data->s_history->history_count < HISTORY_SIZE)
		data->s_history->history_count++;
	add_history(input);
}

void	free_history_buffer(t_data *data)
{
	int	i;

	i = 0;
	while (i < HISTORY_SIZE)
		free(data->s_history->history_buffer[i++]);
}
