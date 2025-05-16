/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:54:10 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/28 18:28:34 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

t_arguements	*tokenise_entry(char **split)
{
	int				i;
	t_arguements	*argst;

	split = split_tokens(split);
	i = 0;
	while (split[i])
		i++;
	argst = (t_arguements *)ft_calloc(i + 1, sizeof(t_arguements));
	if (!argst)
	{
		free(split);
		return (NULL);
	}
	i = 0;
	while (split[i])
	{
		argst[i].arg = split[i];
		i++;
	}
	findset_operators(argst);
	findset_files(argst);
	findset_commands(argst);
	findset_arguments(argst);
	free(split);
	return (argst);
}

void	findset_files(t_arguements *token_args)
{
	int	i;

	i = 0;
	while (token_args[i].arg && token_args[i + 1].arg)
	{
		if (token_args[i].type == TOKEN_REDIRECTION && !token_args[i + 1].type)
			token_args[i + 1].type = TOKEN_FILENAME;
		i++;
	}
}

void	findset_arguments(t_arguements *token_args)
{
	int	i;

	i = 0;
	while (token_args[i].arg)
	{
		if (ft_strchr(token_args[i].arg, '=')
			&& token_args[i].type == TOKEN_UNCLASSED)
			token_args[i].type = TOKEN_ASSIGNMENT;
		else if (token_args[i].type == TOKEN_UNCLASSED)
			token_args[i].type = TOKEN_ARGUEMENT;
		i++;
	}
}
