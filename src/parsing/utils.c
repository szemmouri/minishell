/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szemmour <szemmour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:49:30 by mel-adna          #+#    #+#             */
/*   Updated: 2025/04/14 14:47:40 by szemmour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*add_result(char *result, char *tmp)
{
	char	*new_result;

	if (!tmp)
		tmp = ft_strdup("");
	if (!result)
		return (tmp);
	new_result = ft_strjoin(result, tmp);
	free(result);
	free(tmp);
	return (new_result);
}

t_command	*tokenize_line(char *line, t_env **env)
{
	t_token		*token_list;
	t_command	*cmds;
	int			i;

	token_list = NULL;
	cmds = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\r')
			i++;
		else
			process_and_add_token(&token_list, line, &i, env);
	}
	parse_tokens(token_list, &cmds);
	free_token_list(&token_list);
	return (cmds);
}

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	cmd->append = 0;
	cmd->heredoc = NULL;
	cmd->pipe = 0;
	cmd->next = NULL;
	cmd->pid = -1;
	cmd->cmd_path = NULL;
	return (cmd);
}
