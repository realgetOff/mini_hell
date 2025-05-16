/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 22:15:34 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/26 18:28:48 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	free_mallocs(t_data *data)
{
	free_str_array(data->s_read->envp);
	if (data->s_read->line)
		free_str_array(data->s_read->line);
	if (data->s_read->exports)
		free_str_array(data->s_read->exports);
	free(data->s_read);
	free(data->s_history);
}

void	free_tokens(t_arguements *token_array)
{
	int	i;

	i = 0;
	while (token_array[i].arg)
	{
		free(token_array[i].arg);
		i++;
	}
	free(token_array);
}

void	ft_free(t_data *data)
{
	free_history_buffer(data);
	rl_clear_history();
	free_mallocs(data);
}
