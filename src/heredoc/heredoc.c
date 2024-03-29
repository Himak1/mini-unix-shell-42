/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/17 17:05:29 by jhille        #+#    #+#                 */
/*   Updated: 2022/09/21 17:00:21 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include "parser.h"
#include "heredoc.h"

static t_ast	*next_exec_block(t_ast *exec_block)
{
	exec_block = exec_block->next_sib_node;
	if (exec_block)
		exec_block = exec_block->next_sib_node;
	return (exec_block);
}

int	single_heredoc(char *tmp_filepath, t_ast *rd, char *envv[], int i)
{
	char	*tmp_file;
	int		file_fd;
	int		status;
	int		pid;

	if (rd->type != RD_DE)
		return (i);
	tmp_file = create_tmp_filename(tmp_filepath, i);
	file_fd = open(tmp_file, O_CREAT | O_WRONLY, 0666);
	if (file_fd == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
		read_write_to_tmp(rd->child_node->next_sib_node->value, file_fd, envv);
	close(file_fd);
	waitpid(pid, &status, 0);
	free(rd->child_node->next_sib_node->value);
	rd->child_node->next_sib_node->value = tmp_file;
	if (WEXITSTATUS(status) == EXIT_FAILURE)
		return (-1);
	return (i + 1);
}

int	handle_all_heredocs(t_data *data)
{
	t_ast	*exec_block;
	char	*tmp_filepath;
	t_ast	*rd_iter;
	int		i;

	i = 0;
	exec_block = data->tree->child_node;
	signal(SIGINT, SIG_IGN);
	tmp_filepath = find_tmp_filepath();
	while (exec_block)
	{
		rd_iter = get_rd(exec_block);
		while (rd_iter)
		{
			i = single_heredoc(tmp_filepath, rd_iter, data->envv, i);
			if (i == -1)
				break ;
			rd_iter = rd_iter->next_sib_node;
		}
		exec_block = next_exec_block(exec_block);
	}
	free(tmp_filepath);
	sigaction(SIGINT, &data->sigint_h, NULL);
	return (i);
}
