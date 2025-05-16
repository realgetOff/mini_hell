/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmilner- <pmilner-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:41:52 by mforest-          #+#    #+#             */
/*   Updated: 2025/04/28 03:41:11 by pmilner-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_hell.h"

void	lexer(char *line, t_data *data, t_read *entry)
{
	char	**split;

	split = split_line(line);
	entry->tokens = tokenise_entry(split);
	free_str_array(split);
	if (!check_tokens(entry->tokens))
	{
		free_tokens(entry->tokens);
		data->exit_code = 2;
		return ;
	}
	expand_all_args(entry->tokens, data);
	exec_cmds(data, entry);
}

void	print_art(void)
{
	printf("\n\e[1;91m");
	printf("\t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⠀⡠⢺⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢢⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⣰⠁⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⢳⠀⠀⠀\n");
	printf("\t\t⠀⢠⡇⠀⢸⠀⠀⠀⠀⢀⣀⣀⣀⣀⣀⣀⣀⠀⠀⠀⠀⠈⠀⠀⡇⠀⠀\n");
	printf("\t\t⠀⢸⡄⠀⠀⠢⣠⣴⡋⠉⠁⠀⠀⠀⠀⠀⠈⠻⣶⣄⡠⠃⠀⠀⡇⠀⠀\n");
	printf("\t\t⡀⠈⣧⠀⠀⠀⠈⡇⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡏⠀⠀⠀⢠⠇⠀⡀\n");
	printf("\t\t⣷⡀⠘⣆⠀⠀⠀⣿⠀⠀⠀⠀⠀⢀⣀⣠⡤⢾⣿⡁⠀⠀⢠⡟⠀⣴⡇\n");
	printf("\t\t⡏⢻⣦⡘⣷⣦⠼⠃⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⠻⢷⣤⣴⡏⣠⡾⠃⠃\n");
	printf("\t\t⢳⠀⠙⢿⣿⡏⠀⠀⠀⡰⠃⠀⠀⠀⠀⠀⠣⡀⠀⠀⠀⢹⣿⠟⠀⢰⠀\n");
	printf("\t\t⠈⢧⡀⢸⣿⣿⣀⡀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⣀⠀⠈⣿⠀⢀⠌⠀\n");
	printf("\t\t⠀⠀⠙⢾⣿⣿⣿⣿⡗⢄⡀⠀⡀⠀⡀⠀⡀⠔⡿⠀⠀⠀⣿⠔⠁⠀⠀\n");
	printf("\t\t⠀⠀⠀⠀⢿⣿⡋⠉⠙⠒⠉⠙⡇⢀⡟⠉⠑⠊⠁⠀⠀⢠⠇⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⠀⠀⠈⠻⡇⠀⠀⠀⢀⠀⠃⢸⣷⣀⠀⠀⠀⢀⡴⠃⠀⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⠀⠀⠀⠀⣿⣶⣶⣖⠛⠦⠀⠈⡿⠟⢑⣶⣶⣾⠇⠀⠀⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⠀⠀⠀⠀⢻⣯⠉⢩⠧⠄⠓⠒⠁⣔⢵⠈⣡⣿⠀⠀⠀⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⠀⠀⠀⠀⠈⢿⣧⠘⢜⣉⣁⣈⣉⣏⠄⢰⣿⠃⠀⠀⠀⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⠀⠀⠀⠀⠀⠈⢿⡀⠀⠐⠒⠒⠒⠀⠀⣼⠃⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠑⢤⣀⣀⣀⣀⣠⠜⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("\t\t⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⣉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("\e[0m\n");
}
