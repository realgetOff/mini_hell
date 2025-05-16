/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:24:42 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 18:05:20 by mforest-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	findset_operators(t_arguements *token_args)
{
	int	i;

	i = 0;
	while (token_args[i].arg)
	{
		if (!ft_strncmp(token_args[i].arg, "|", 1))
			token_args[i].type = TOKEN_OPERATOR;
		else if (!ft_strncmp(token_args[i].arg, "<<", 2))
		{
			token_args[i].type = TOKEN_REDIRECTION;
			if (token_args[i + 1].arg)
				token_args[i + 1].type = TOKEN_DELIMITER;
		}
		else if (!ft_strncmp(token_args[i].arg, "<", 1))
			token_args[i].type = TOKEN_REDIRECTION;
		else if (!ft_strncmp(token_args[i].arg, ">", 1))
			token_args[i].type = TOKEN_REDIRECTION;
		i++;
	}
}

int	other_cmd(t_arguements *token_args, int i)
{
	int	j;

	if (!i)
		return (0);
	j = i - 1;
	i++;
	if (token_args[j].type == TOKEN_REDIRECTION)
		return (0);
	while (j > 0 && token_args[j].type != TOKEN_OPERATOR)
	{
		if (token_args[j].type == TOKEN_COMMAND)
			return (1);
		j--;
	}
	while (token_args[i].arg && token_args[i].type != TOKEN_OPERATOR)
	{
		if (token_args[i].type == TOKEN_COMMAND)
			return (1);
		i++;
	}
	return (0);
}

static void	handle_operator_commands(t_arguements *token_args, int i)
{
	if (token_args[i].type == TOKEN_OPERATOR && token_args[i + 1].arg)
	{
		if (token_args[i + 1].type == TOKEN_UNCLASSED)
			token_args[i + 1].type = TOKEN_COMMAND;
	}
}

static void	handle_file_delimiter_commands(t_arguements *token_args, int i)
{
	if (token_args[i].type == TOKEN_FILENAME && token_args[i + 1].arg)
	{
		if (token_args[i + 1].type == TOKEN_UNCLASSED && !other_cmd(token_args,
				i))
			token_args[i + 1].type = TOKEN_COMMAND;
	}
	if (token_args[i].type == TOKEN_DELIMITER && token_args[i + 1].arg)
	{
		if (token_args[i + 1].type == TOKEN_UNCLASSED && !other_cmd(token_args,
				i))
			token_args[i + 1].type = TOKEN_COMMAND;
	}
}

void	findset_commands(t_arguements *token_args)
{
	int	i;

	i = 0;
	if (token_args[0].type == TOKEN_UNCLASSED)
		token_args[0].type = TOKEN_COMMAND;
	while (token_args[i].arg)
	{
		handle_file_delimiter_commands(token_args, i);
		handle_operator_commands(token_args, i);
		i++;
	}
}
