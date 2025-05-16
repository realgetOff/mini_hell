/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 00:47:12 by pmilner-          #+#    #+#             */
/*   Updated: 2025/04/27 18:33:53 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

// ` | ` is invalid, so is `| cmd` and `|` and `cmd |`
// exit code is 2
// wonder if i should do this in the node stage, or in the token stage?
// i think the node stage would be the easiet
// NOPE, token stage, cause of stupid fucking issues everywhere!!
// >>> is invalid, so is <<<
// `>>` is invalid, etc (a delimiter followed by fuck all)

int	check_redirections(t_arguements *token_args)
{
	if (!token_args[1].arg)
	{
		ft_printf_err("mini_hell: ");
		ft_printf_err("syntax error near unexpected token `newline'\n");
		return (0);
	}
	if (ft_strlen(token_args[0].arg) > 2)
	{
		ft_printf_err("mini_hell: ");
		ft_printf_err("syntax error near unexpected token `%s'\n",
			token_args[0].arg);
		return (0);
	}
	return (1);
}

int	check_operators(t_arguements *token_args, int i)
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
		if (token_args[j].type == TOKEN_OPERATOR)
			return (0);
		j--;
	}
	while (token_args[i].arg && token_args[i].type != TOKEN_OPERATOR)
	{
		if (token_args[i].type != TOKEN_OPERATOR)
			return (1);
		i++;
	}
	return (0);
}

int	check_tokens(t_arguements *argst)
{
	int	i;
	int	valid;

	i = 0;
	valid = 1;
	while (argst[i].arg && valid)
	{
		if (argst[i].type == TOKEN_OPERATOR)
		{
			valid = check_operators(argst, i);
			if (!valid)
				ft_printf_err("mini_hell: syntax error near unexpected token "
					"`|'\n");
		}
		else if (argst[i].type == TOKEN_REDIRECTION)
			valid = check_redirections(&argst[i]);
		i++;
	}
	return (valid);
}
